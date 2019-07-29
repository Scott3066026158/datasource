#pragma once
#ifndef __ConnectProxy_H__
#define __ConnectProxy_H__

#include "..\\owsock\\BaseService.h"

//���տͻ���
class ConnectProxy : public BaseService
{
public:
	ConnectProxy();
	virtual ~ConnectProxy();
public:
	//������
	CLock m_revLock;
	//��������Ϣ
	vector<CMessage*> m_revMsg;
	//������
	CLock m_sendLock;
	//��������Ϣ
	vector<CMessage*> m_sendMsg;
public:
	//������Ϣ
	virtual void OnReceive(CMessage *message);
	//������Ϣ
	static DWORD WINAPI SendThread(LPVOID lpParam);
	//��������Ϣ
	int SendMsg(CMessage *message);
	void StartSendMsg();
};
#endif