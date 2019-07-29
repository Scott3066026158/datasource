#pragma once
#ifndef __BINARY_H__
#define __BINARY_H__
#include "..\\api\\CStr.h"

#define	DATA_LACK -1
#define PAGE_SIZE 1024 * 8
typedef unsigned char BYTE;
typedef BYTE *PBYTE;

class Binary
{
protected:
	PBYTE m_pBase;
	unsigned int m_nDataSize;
	unsigned int m_nSize;
	unsigned int m_nInitSize;
	bool m_bSustainSize;
	static unsigned int m_dwPageSize;
	unsigned int DeAllocateBuffer(unsigned int nRequestedSize);
	unsigned int GetMemSize();
public:
	Binary();
	virtual ~Binary();
	const Binary& operator+(Binary& buff);
	bool m_bSingleRead;
	unsigned int m_nReadPos;
public:
	void ClearBytes();
	void Copy(Binary *buffer);	
	unsigned int Delete(unsigned int nSize);
	unsigned int DeleteEnd(unsigned int nSize);
	void FileRead(const String& strFileName);
	void FileWrite(const String& strFileName);
	PBYTE GetBytes(unsigned int nPos = 0);
	unsigned int GetBytesLen();
	void Initialize(unsigned int nInitsize, bool bSustain);
	unsigned int Insert(const void *pData, unsigned int nSize);
	unsigned int Insert(String& strData);
	unsigned int Read(void *pData, unsigned int nSize);
	char ReadChar();
	double ReadDouble();
	float ReadFloat();
	int ReadInt();
	INT64 ReadLong();
	short ReadShort();
	unsigned int ReadString(String&);
	unsigned int ReadString(string& strData);
	unsigned int ReAllocateBuffer(unsigned int nRequestedSize);
	unsigned int SkipData(int nSize);
	unsigned int Write(const void *pData, unsigned int nSize);
	unsigned int Write(const String& strData);
	void WriteChar(char cValue);
	void WriteDouble(double dValue);
	void WriteFloat(float fValue);
	void WriteInt(int nValue);
	void WriteLong(INT64 hValue);
	void WriteShort(short sValue);
	unsigned int WriteString(const String& strData);
	unsigned int WriteString(const string& strData);
};


#endif