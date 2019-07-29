#include "..\\stdafx.h"
#include "Dump.h"
#include <time.h>


//LONG __stdcall Dump::CreateDump(PEXCEPTION_POINTERS pExceptionInfo)
//{
//	time_t t;
//	time(&t);
//	wchar_t buff[256] = {0};
//	swprintf_s(buff, L"%ld.dmp", t);
//	CreateMiniDump(pExceptionInfo, buff);  
//
//	return EXCEPTION_EXECUTE_HANDLER;
//}

int Dump::GenerateMiniDump(HANDLE hFile, PEXCEPTION_POINTERS pExceptionPointers, PWCHAR pwAppName)
{
	BOOL bOwnDumpFile = FALSE;  
	HANDLE hDumpFile = hFile;  
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;  

	typedef BOOL(WINAPI * MiniDumpWriteDumpT)( 
		HANDLE,  
		DWORD,  
		HANDLE,  
		MINIDUMP_TYPE,  
		PMINIDUMP_EXCEPTION_INFORMATION,  
		PMINIDUMP_USER_STREAM_INFORMATION,  
		PMINIDUMP_CALLBACK_INFORMATION  
		);  

	MiniDumpWriteDumpT pfnMiniDumpWriteDump = 0;  
	HMODULE hDbgHelp = LoadLibrary(L"DbgHelp.dll");  
	if (hDbgHelp)  
		pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");  

	if (pfnMiniDumpWriteDump)  
	{  
		if (hDumpFile == 0 || hDumpFile == INVALID_HANDLE_VALUE)  
		{  
			TCHAR szPath[MAX_PATH] = { 0 };  
			TCHAR szFileName[MAX_PATH] = { 0 };  
			TCHAR* szAppName = pwAppName;  
			TCHAR* szVersion = L"v1.0";  
			TCHAR dwBufferSize = MAX_PATH;  
			SYSTEMTIME stLocalTime;  

			GetLocalTime(&stLocalTime);  
			GetTempPath(dwBufferSize, szPath);  

			//StringCchPrintf(szFileName, MAX_PATH, L"%s%s", szPath, szAppName);  
			//CreateDirectory(szFileName, NULL);  

			//StringCchPrintf(szFileName, MAX_PATH, L"%s%s//%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",  
			//	szPath, szAppName, szVersion,  
			//	stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,  
			//	stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,  
			//	GetCurrentProcessId(), GetCurrentThreadId());  

			time_t t;
			time(&t);
			//wchar_t buff[256] = {0};
			swprintf_s(szFileName, L"%ld.dmp", t);
			hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,  
				FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);  



			bOwnDumpFile = TRUE;  
			OutputDebugString(szFileName);  
		}  

		if (hDumpFile != INVALID_HANDLE_VALUE)  
		{  
			ExpParam.ThreadId = GetCurrentThreadId();  
			ExpParam.ExceptionPointers = pExceptionPointers;  
			ExpParam.ClientPointers = FALSE;  

			pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),  
				hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &ExpParam : 0), 0, 0);  

			if (bOwnDumpFile)  
				CloseHandle(hDumpFile);  
		}  
	}  

	if (hDbgHelp != 0)  
		FreeLibrary(hDbgHelp);  

	return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI Dump::CreateDump(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	if (IsDebuggerPresent())  
	{  
		return EXCEPTION_CONTINUE_SEARCH;  
	}  

	return GenerateMiniDump(0, lpExceptionInfo, L"test");
}
