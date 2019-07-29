#pragma once
#ifndef __NODESERVICE_H__
#define __NODESERVICE_H__
#include "..\\stdafx.h"
#include "..\\api\\CLock.h"
#include "Binary.h"
#include <string>
#include <map>
using namespace std;


class HttpData
{
public:
	HttpData();
	~HttpData();
	SOCKADDR_IN m_addr;
	char *m_body;
    bool m_close;
	int m_contentLength;
    String m_contentType;
    String m_method;
	map<String, String> m_parameters;
	String m_remoteIP;
    int m_remotePort;
	char* m_resBytes;
	int m_resBytesLength;
	String m_resStr;
	SOCKET m_socket;
	int m_statusCode;	
    String m_url;
};

class NodeService
{
public:
	SOCKADDR_IN m_addr;
	SOCKET m_hSocket;
	CLock m_lock;
	CLock m_lockHttpData;
	int m_port;
public:
	NodeService();
	virtual ~NodeService();
	int GetPort();
	void SetPort(int port);
	SOCKET GetSocket();
public:
	int Close(int socketID);		
	int Start();
};
#endif