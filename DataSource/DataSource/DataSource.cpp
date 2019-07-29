// DataSource.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "global\\DataCenter.h"
int _tmain(int argc, _TCHAR* argv[])
{
	DataCenter::StartServiceW();
	while(1)
	{
		char *input = new char[1024];
		cin >> input;
		if(strcmp(input, "exit") == 0)
		{
			break;
		}
	}
	return 0;
}
