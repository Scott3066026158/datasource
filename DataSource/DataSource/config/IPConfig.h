#pragma once
#ifndef __IPCONFIG_H__
#define __IPCONFIG_H__

#include "..\\stdafx.h"

//IP结构
struct IPStruct
{
	//名称
	String m_name;
	//IP
	String m_ip;
	//端口
	int m_port;
};

//IP配置
class IPConfig
{
public:
	//构造函数
	IPConfig();
	//析构函数
	virtual ~IPConfig();
private:
	//所有的端口
	vector<IPStruct> m_allIPs;
public:
	//获取IP和端口
	bool GetIPPort(const String &wName, IPStruct *ip);
	string GetPrintString()
	{
		string str;
		vector<IPStruct>::iterator sIter = m_allIPs.begin();
		for(; sIter != m_allIPs.end(); ++sIter)
		{
			IPStruct ipStruct = *sIter;
			char sz[1024] = {0};
			sprintf_s(sz, 1023, "%s,%s:%d\r\n",  ipStruct.m_name.c_str(), ipStruct.m_ip.c_str(), ipStruct.m_port);
			str += sz;
		}
		return str;
	}
};
#endif
