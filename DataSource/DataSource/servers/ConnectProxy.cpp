#include "..\\stdafx.h"
#include "..\\owsock\\CMessage.h"
#include "..\\global\\DataCenter.h"
#include "..\\global\\BusinessIDs.h"
#include "ConnectProxy.h"

ConnectProxy::ConnectProxy()
{
	m_compressType = COMPRESSTYPE_NONE;
	m_groupID = 0;
	m_serviceID = DATASOURCE_SERVICE_ID;
	m_socketID = 0;
	m_sessionID = 0;
}

ConnectProxy::~ConnectProxy()
{
	m_compressType = COMPRESSTYPE_NONE;
	m_groupID = 0;
	m_serviceID = 0;
	m_socketID = 0;
	m_sessionID = 0;
}

void ConnectProxy::OnReceive(CMessage *message)
{
	m_revLock.Lock();
	m_revMsg.push_back(message);
	m_revLock.UnLock();
}

DWORD WINAPI ConnectProxy::SendThread(LPVOID lpParam)
{
	ConnectProxy* cs = DataCenter::GetConnectProxy();
	while(true)
	{
		::Sleep(10);
		if(cs->m_sendMsg.size() == 0)
		{
			continue;
		}
		cs->m_sendLock.Lock();
		vector<CMessage*> msg(cs->m_sendMsg);
		cs->m_sendMsg.clear();
		cs->m_sendLock.UnLock();
		for(vector<CMessage*>::iterator msgIter = msg.begin(); msgIter != msg.end(); msgIter++)
		{
			cs->Send(*msgIter);
			delete *msgIter;
		}
	}
}

int ConnectProxy::SendMsg(CMessage *message)
{
	m_sendLock.Lock();
	m_sendMsg.push_back(message);
	m_sendLock.UnLock();
	return 1;
}

void ConnectProxy::StartSendMsg()
{
	//启动发送消息线程
	::CreateThread(0, 0, SendThread, (LPVOID)this, 0, 0);
}