#pragma once
#ifndef __ConnectProxy_H__
#define __ConnectProxy_H__

#include "..\\owsock\\BaseService.h"

//接收客户端
class ConnectProxy : public BaseService
{
public:
	ConnectProxy();
	virtual ~ConnectProxy();
public:
	//接收锁
	CLock m_revLock;
	//待处理消息
	vector<CMessage*> m_revMsg;
	//发送锁
	CLock m_sendLock;
	//待发送消息
	vector<CMessage*> m_sendMsg;
public:
	//接收消息
	virtual void OnReceive(CMessage *message);
	//发送消息
	static DWORD WINAPI SendThread(LPVOID lpParam);
	//请求发送消息
	int SendMsg(CMessage *message);
	void StartSendMsg();
};
#endif