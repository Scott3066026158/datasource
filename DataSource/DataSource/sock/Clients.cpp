#include "..\\stdafx.h"
#include "Client.h"
#include "Clients.h"

namespace OwLibSock
{
	map<int, Client*> m_clients;

	RecvMsg m_recvServerMsgCallBack = 0;

	WriteClientLog m_writeClientLogCallBack = 0;
	
	void Clients::RecvServerMsg(int socketID, int localSID, const char *str, int len)
	{
		if(m_recvServerMsgCallBack)
		{
			m_recvServerMsgCallBack(socketID, localSID, str, len);
		}
	}

	void Clients::WriteLog(int socketID, int localSID, int state, const char *log)
	{
		if(m_writeClientLogCallBack)
		{
			m_writeClientLogCallBack(socketID, localSID, state, log);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	int Clients::Close(int socketID)
	{
		map<int, Client*>::iterator sIter = m_clients.find(socketID);
		if(sIter != m_clients.end())
		{
			Client *client = sIter->second;
			int ret = client->Close(socketID);
			m_clients.erase(sIter);
			client = 0;
			return ret;
		}
		return SOCKET_ERROR;
	}

	int Clients::Connect(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout)
	{
		Client *client = new Client(type, proxyType, ip, port, proxyIp, proxyPort, proxyUserName, proxyUserPwd, proxyDomain, timeout);
		ConnectStatus ret = client->Connect();
		if(ret != CONNECT_SERVER_FAIL)
		{
			int socketID = (int)client->m_hSocket;
			m_clients[socketID] = client;
			client->m_writeLogEvent = WriteLog;
			client->m_recvEvent = RecvServerMsg;
			return socketID;
		}
		else
		{
			delete client;
			client = 0;
			return -1;
		}
	}

	void Clients::RegisterLog(WriteClientLog writeLogCallBack)
	{
		m_writeClientLogCallBack = writeLogCallBack;
	}

	void Clients::RegisterRecv(RecvMsg recvMsgCallBack)
	{
		m_recvServerMsgCallBack = recvMsgCallBack;
	}

	int Clients::Send(int socketID, const char *str, int len)
	{
		return Client::Send(socketID, str, len);
	}

	int Clients::SendTo(int socketID, const char *str, int len)
	{
		map<int, Client*>::iterator sIter = m_clients.find(socketID);
		if(sIter != m_clients.end())
		{
			Client *client = sIter->second;
			return client->SendTo(str, len);
		}
		return -1;
	}
}