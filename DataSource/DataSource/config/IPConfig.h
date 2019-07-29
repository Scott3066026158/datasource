#pragma once
#ifndef __IPCONFIG_H__
#define __IPCONFIG_H__

#include "..\\stdafx.h"

//IP�ṹ
struct IPStruct
{
	//����
	String m_name;
	//IP
	String m_ip;
	//�˿�
	int m_port;
};

//IP����
class IPConfig
{
public:
	//���캯��
	IPConfig();
	//��������
	virtual ~IPConfig();
private:
	//���еĶ˿�
	vector<IPStruct> m_allIPs;
public:
	//��ȡIP�Ͷ˿�
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
