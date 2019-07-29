#ifndef __DUMP_H__
#define __DUMP_H__
#pragma once

#include <DbgHelp.h>  
#pragma comment(lib, "dbghelp.lib") 

class Dump
{
public:
	static LONG WINAPI CreateDump(LPEXCEPTION_POINTERS lpExceptionInfo);
private:
	static int GenerateMiniDump(HANDLE hFile, PEXCEPTION_POINTERS pExceptionPointers, PWCHAR pwAppName);  
};
#endif
