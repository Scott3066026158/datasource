#include "..\\stdafx.h"
#include "Binary.h"


unsigned int Binary::m_dwPageSize = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Binary::DeAllocateBuffer(unsigned int nRequestedSize)
{
	if(nRequestedSize == 0)
	{
		return 0;
	}
	if(m_bSustainSize)
	{
		return 0;
	}
	if(m_nSize <= m_nInitSize)
	{
		return 0;
	}
	if(nRequestedSize < m_nDataSize)
	{
		return 0;
	}
	if(nRequestedSize < m_nInitSize)
	{
		nRequestedSize = m_nInitSize;
	}
	unsigned int nNewSize = m_nSize;
	while(nNewSize >= nRequestedSize * 2)
	{
		nNewSize /= 2;
	}
	if(nNewSize == m_nSize)
	{
		return 0;
	}
	PBYTE pNewBuffer = (PBYTE) VirtualAlloc(0, nNewSize, MEM_COMMIT, PAGE_READWRITE);
	if(!pNewBuffer)
	{
		pNewBuffer = new unsigned char[nNewSize];
	}
	if (m_pBase)
	{
		if(m_nDataSize)
		{
			CopyMemory(pNewBuffer, m_pBase, m_nDataSize);
		}
		VirtualFree(m_pBase, 0, MEM_RELEASE);
	}
	m_pBase = pNewBuffer;
	m_nSize = nNewSize;
	return m_nSize;
}

unsigned int Binary::GetMemSize()
{
	return m_nSize;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Binary::Binary()
{
	m_bSingleRead = true;
	m_bSustainSize = false;
	m_nDataSize = 0;
	m_nInitSize = 0;
	m_nReadPos = 0;
	m_nSize = 0;
	m_pBase =  0;
	if(m_dwPageSize == 0)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		m_dwPageSize = si.dwPageSize;
		while(m_dwPageSize < 8192)
		{
			m_dwPageSize += si.dwPageSize;
		}
	}
}

Binary::~Binary()
{
	if(m_pBase)
	{
		VirtualFree(m_pBase, 0, MEM_RELEASE);
	}
}

const Binary& Binary::operator+(Binary& buff)
{
	this->Write(buff.GetBytes(), buff.GetBytesLen());
	return* this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Binary::ClearBytes()
{
	m_nDataSize = 0;
	m_nReadPos = 0;
	DeAllocateBuffer(0);
}

void Binary::Copy(Binary* buffer)
{
	unsigned int nReSize = buffer->GetMemSize();
	if(nReSize != m_nSize)
	{
		if (m_pBase)
		{
			VirtualFree(m_pBase, 0, MEM_RELEASE);
		}
		m_pBase = (PBYTE) VirtualAlloc(0, nReSize, MEM_COMMIT, PAGE_READWRITE);
		m_nSize = nReSize;
	}
	m_nDataSize = buffer->GetBytesLen();
	if(m_nDataSize > 0)
	{
		CopyMemory(m_pBase, buffer->GetBytes(), m_nDataSize);
	}
}

unsigned int Binary::Delete(unsigned int nSize)
{
	if(nSize == 0)
	{
		return nSize;
	}
	if (nSize > m_nDataSize)
	{
		nSize = m_nDataSize;
	}
	m_nDataSize -= nSize;
	if(m_nDataSize > 0)
	{
		MoveMemory(m_pBase, m_pBase+nSize, m_nDataSize);
	}
	DeAllocateBuffer(m_nDataSize);
	return nSize;
}

unsigned int Binary::DeleteEnd(unsigned int nSize)
{
	if(nSize > m_nDataSize)
		nSize = m_nDataSize;
	if(nSize)
	{
		m_nDataSize -= nSize;
		DeAllocateBuffer(m_nDataSize);
	}
	return nSize;
}

void Binary::FileRead(const String& strFileName)
{
}

void Binary::FileWrite(const String& strFileName)
{
}

PBYTE Binary::GetBytes(unsigned int nPos)
{
	if(!m_pBase)
	{
		return 0;
	}
	return m_pBase + nPos;
}

unsigned int Binary::GetBytesLen()
{
	if(!m_pBase)
	{
		return 0;
	}
	if (m_bSingleRead)
	{
		return m_nDataSize - m_nReadPos;
	}
	else
	{
		return m_nDataSize;
	}
}

void Binary::Initialize(unsigned int nInitsize, bool bSustain)
{
	m_bSustainSize = bSustain;
	ReAllocateBuffer(nInitsize);
	m_nInitSize = m_nSize;
}

unsigned int Binary::Insert(const void *pData, unsigned int nSize)
{
	ReAllocateBuffer(nSize + m_nDataSize);
	MoveMemory(m_pBase+nSize, m_pBase, m_nDataSize);
	CopyMemory(m_pBase, pData, nSize);
	m_nDataSize += nSize;
	return nSize;
}

unsigned int Binary::Insert(String& strData)
{
	int nSize = (int)strData.size();
	return Insert((const void*)strData.c_str(), nSize);
}

unsigned int Binary::Read(void *pData, unsigned int nSize)
{
	if (nSize)
	{
		if (m_bSingleRead)
		{
			if (nSize+m_nReadPos > m_nDataSize)
			{
				FILE *file = fopen("c:\\dump.binary", "wb");
				fwrite(m_pBase, sizeof(char), m_nDataSize, file);
				fclose(file);
				abort();
				assert(1 != 1);
				throw DATA_LACK;
				return 0;
			}
			CopyMemory(pData, m_pBase + m_nReadPos, nSize);
			m_nReadPos += nSize;
		}
		else
		{
			if (nSize > m_nDataSize)
			{
				throw DATA_LACK;
				return 0;
			}
			m_nDataSize -= nSize;
			CopyMemory(pData, m_pBase, nSize);		
			if (m_nDataSize > 0)
			{
				MoveMemory(m_pBase, m_pBase + nSize, m_nDataSize);
			}
		}
	}	
	DeAllocateBuffer(m_nDataSize);
	return nSize;
}

char Binary::ReadChar()
{
	char cValue;
	Read(&cValue, sizeof(char));
	return cValue;
}

double Binary::ReadDouble()
{
	double dValue;
	Read(&dValue, sizeof(double));
	return dValue;
}

float Binary::ReadFloat()
{
	float fValue;
	Read(&fValue, sizeof(float));
	return fValue;
}

int Binary::ReadInt()
{
	int nValue;
	Read(&nValue, sizeof(int));
	return nValue;
}

INT64 Binary::ReadLong()
{
	LARGE_INTEGER li;
	li.HighPart = ReadInt();
	li.LowPart = ReadInt();
	return li.QuadPart;
}

short Binary::ReadShort()
{
	short sValue;
	Read(&sValue, sizeof(short));
	return sValue;
}

unsigned int Binary::ReadString(String& strData)
{
	strData.clear();
	unsigned int dwSize = 0;
	Read(&dwSize, sizeof(unsigned int));
	if(dwSize == 0)
	{
		return 2;
	}
	if (m_bSingleRead)
	{
		if (dwSize + m_nReadPos > m_nDataSize)
		{
			assert(1 != 1);
			throw DATA_LACK;
			return 0;
		}
		string str((const char*)m_pBase + m_nReadPos, dwSize);
		CStrA::ANSCToUnicode(str, str.c_str());
		CStrA::stringTowstring(strData, str);
		m_nReadPos += dwSize;
	}
	else
	{
		if (dwSize > m_nDataSize)
		{
			assert(1 != 1);
			throw DATA_LACK;
			return 0;
		}
		string str((const char*)m_pBase,dwSize);
		CStrA::ANSCToUnicode(str, str.c_str());
		CStrA::stringTowstring(strData, str.c_str());
		Delete(dwSize);
	}
	return (dwSize+sizeof(unsigned int));
}

unsigned int Binary::ReadString(string& strData)
{
	strData.clear();
	unsigned int dwSize;
	Read(&dwSize, sizeof(unsigned int));
	if(dwSize == 0)
	{
		return 2;
	}
	if (m_bSingleRead)
	{
		if (dwSize+m_nReadPos > m_nDataSize)
		{
			throw DATA_LACK;
			return 0;
		}
		string str((const char*)m_pBase+m_nReadPos,dwSize);
		strData = str; 
		m_nReadPos += dwSize;
	}
	else
	{
		if (dwSize > m_nDataSize)
		{
			throw DATA_LACK;
			return 0;
		}
		string str((const char*)m_pBase,dwSize);
		strData = str;
		Delete(dwSize);
	}
	return (dwSize + sizeof(unsigned int));
}

unsigned int Binary::ReAllocateBuffer(unsigned int nRequestedSize)
{
	if(nRequestedSize <= m_nSize)
	{
		return 0;
	}
	unsigned int nNewSize = m_nSize;
	if(nNewSize < m_dwPageSize)
	{
		nNewSize = m_dwPageSize;
	}
	while(nRequestedSize > nNewSize)
	{
		nNewSize *= 2;
	}
	PBYTE pNewBuffer = (PBYTE) VirtualAlloc(0, nNewSize, MEM_COMMIT, PAGE_READWRITE);
	if(!pNewBuffer)
	{
		pNewBuffer = new unsigned char[nNewSize];
	}
	if (m_pBase)
	{
		if(m_nDataSize)
		{
			CopyMemory(pNewBuffer, m_pBase, m_nDataSize);
		}
		VirtualFree(m_pBase, 0, MEM_RELEASE);
	}
	m_pBase = pNewBuffer;
	m_nSize = nNewSize;
	return m_nSize;
}

unsigned int Binary::SkipData(int nSize)
{
	if(m_bSingleRead)
	{
		if (nSize+m_nReadPos > m_nDataSize)
		{
			throw DATA_LACK;
			return 0;
		}
		m_nReadPos += nSize;
		return nSize;
	}
	else
	{
		m_nDataSize -= nSize;
		if (m_nDataSize > 0)
		{
			MoveMemory(m_pBase, m_pBase+nSize, m_nDataSize);
		}
		DeAllocateBuffer(m_nDataSize);
	}
	return 0;
}

unsigned int Binary::Write(const void *pData, unsigned int nSize)
{
	if(nSize)
	{
		ReAllocateBuffer(nSize + m_nDataSize);
		CopyMemory(m_pBase+m_nDataSize, pData, nSize);
		m_nDataSize += nSize;
	}
	return nSize;
}

unsigned int Binary::Write(const String& strData)
{
	int nSize = (int)strData.size();
	return Write((const void*)strData.c_str(), nSize);
}

void Binary::WriteChar(char cValue)
{
	Write(&cValue, sizeof(char));
}

void Binary::WriteDouble(double dValue)
{
	Write(&dValue, sizeof(double));
}

void Binary::WriteFloat(float fValue)
{
	Write(&fValue, sizeof(float));
}

void Binary::WriteInt(int nValue)
{
	Write(&nValue, sizeof(int));
}

void Binary::WriteLong(INT64 hValue)
{
	LARGE_INTEGER li;
	li.QuadPart = hValue;
	WriteInt(li.HighPart);
	WriteInt(li.LowPart);
}

void Binary::WriteShort(short sValue)
{
	Write(&sValue, sizeof(short));
}

unsigned int Binary::WriteString(const String& strData)
{
	string str;
	CStrA::wstringTostring(str, strData);
	CStrA::UnicodeToANSC(str, str.c_str());
	unsigned int dwSize = (int)str.size();
	Write(&dwSize, sizeof(unsigned int));
	if(dwSize)
	{
		Write((const void*) str.c_str(), dwSize);
	}
	return (unsigned int)(dwSize + sizeof(unsigned int));
}

unsigned int Binary::WriteString(const string& strData)
{
	unsigned int wSize = (int)strData.size();
	Write(&wSize, sizeof(unsigned int));
	if(wSize)
	{
		Write((const void*)strData.c_str(), wSize);
	}
	return (unsigned int)(wSize + sizeof(unsigned int));
}