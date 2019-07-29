#include "..\\stdafx.h"
#include "IPConfig.h"
#include "..\\api\\CFile.h"
#include "..\\api\\CStr.h"
#include "..\\global\\DataCenter.h"

IPConfig::IPConfig()
{
	String txtFile = DataCenter::GetAppPathW() + L"\\IPConfig.txt";
	if(CFileA::IsFileExist(txtFile.c_str()))
	{
		String content;
		CFileA::Read(txtFile.c_str(), &content);
		vector<String> strs = CStrA::Split(content, L"\n");
		int strsSize = (int)strs.size();
		for(int i = 0; i < strsSize; i++)
		{
			String str = strs[i];
			vector<String> subStrs = CStrA::Split(str, L",");
			int subStrsSize = (int)subStrs.size();
			if(subStrsSize >= 3)
			{
				string portStr;
				CStrA::wstringTostring(portStr, subStrs[2]);
				IPStruct ipStruct;
				ipStruct.m_name = subStrs[0];
				ipStruct.m_ip = subStrs[1];
				ipStruct.m_port = atoi(portStr.c_str());
				m_allIPs.push_back(ipStruct);
			}
			subStrs.clear();
		}
		strs.clear();
	}
}

IPConfig::~IPConfig()
{

}

bool IPConfig::GetIPPort(const String &name, IPStruct *ipStruct)
{
	for (vector<IPStruct>::iterator sIter = m_allIPs.begin(); sIter != m_allIPs.end(); ++sIter)
	{
		if ((*sIter).m_name == name)
		{
			ipStruct->m_name = (*sIter).m_name;
			ipStruct->m_ip = (*sIter).m_ip;
			ipStruct->m_port = (*sIter).m_port;
			return true;
		}
	}
	return false;
}