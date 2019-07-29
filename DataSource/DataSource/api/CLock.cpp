#include "..\\stdafx.h"
#include "CLock.h"
#include "..\\global\\DataCenter.h"
#include "CFile.h"
#include "CStr.h"

static int writeFile = 0;

CLock::CLock()
{
	memset(m_name, 0, 100);
	::InitializeCriticalSection(&m_cs);
}

CLock::CLock(const char *name)
{
	strcpy_s(m_name, name);
	::InitializeCriticalSection(&m_cs);
}

CLock::~CLock()
{
	::DeleteCriticalSection(&m_cs);
}

void CLock::Lock()
{
	::EnterCriticalSection(&m_cs);
	if(writeFile == 1 && (int)strlen(m_name) > 0)
	{
		string filePath = DataCenter::GetAppPath() + (string)"\\" + (string)m_name + (string)".txt";
		time_t nowtime;  
		nowtime = time(0);   
		struct tm *local; 
		local = localtime(&nowtime);
		char sz[100] = {0};
		sprintf_s(sz, 99, "lock %02d:%02d:%02d\r\n", local->tm_hour, local->tm_min, local->tm_sec);
		CFileA::Append(filePath.c_str(), sz);
	}
}

void CLock::Lock(const char *funcName)
{
	::EnterCriticalSection(&m_cs);
	if(writeFile == 1 && (int)strlen(m_name) > 0)
	{
		string filePath = DataCenter::GetAppPath() + (string)"\\" + (string)m_name + (string)".txt";
		time_t nowtime;  
		nowtime = time(0);   
		struct tm *local;  
		local = localtime(&nowtime);
		char sz[100] = {0};
		sprintf_s(sz, 99, "lock %s %02d:%02d:%02d\r\n", funcName, local->tm_hour, local->tm_min, local->tm_sec);
		CFileA::Append(filePath.c_str(), sz);
	}
}

void CLock::SetName(const char *name)
{
	strcpy_s(m_name, name);
}

void CLock::UnLock()
{
	::LeaveCriticalSection(&m_cs);
	if(writeFile == 1 && (int)strlen(m_name) > 0)
	{
		string filePath = DataCenter::GetAppPath() + (string)"\\" + (string)m_name + (string)".txt";
		time_t nowtime;  
		nowtime = time(0);   
		struct tm *local;  
		local = localtime(&nowtime);
		char sz[100] = {0};
		sprintf_s(sz, 99, "unlock %02d:%02d:%02d\r\n", local->tm_hour, local->tm_min, local->tm_sec);
		CFileA::Append(filePath.c_str(), sz);
	}
}

void CLock::UnLock(const char *funcName)
{
	::LeaveCriticalSection(&m_cs);
	if(writeFile == 1 && (int)strlen(m_name) > 0)
	{
		string filePath = DataCenter::GetAppPath() + (string)"\\" + (string)m_name + (string)".txt";
		time_t nowtime;  
		nowtime = time(0);   
		struct tm *local;  
		local = localtime(&nowtime);
		char sz[100] = {0};
		sprintf_s(sz, 99, "unlock %s %02d:%02d:%02d\r\n", funcName, local->tm_hour, local->tm_min, local->tm_sec);
		CFileA::Append(filePath.c_str(), sz);
	}
}
