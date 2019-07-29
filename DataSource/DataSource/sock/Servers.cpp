#include "..//stdafx.h"
#include "Servers.h"
#include "Server.h"

namespace OwLibSock
{
	map<int, Server*> m_servers;

	RecvMsg m_recvClientMsgCallBack = 0;

	WriteServerLog m_writeServerLogCallBack = 0;
	
	void Servers::RecvClientMsg(int socketID, int localSID, const char *str, int len)
	{
		if(m_recvClientMsgCallBack)
		{
			m_recvClientMsgCallBack(socketID, localSID, str, len);
		}
	}

	void Servers::WriteLog(int socketID, int localSID, int state, const char *log)
	{
		if(m_writeServerLogCallBack)
		{
			m_writeServerLogCallBack(socketID, localSID, state, log);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	int Servers::Close(int socketID)
	{
		map<int, Server*>::iterator sIter = m_servers.find(socketID);
		if(sIter != m_servers.end())
		{
			Server *server = sIter->second;
			int ret = server->Close(socketID);
			m_servers.erase(sIter);
			delete server;
			server = 0;
			return ret;
		}
		return SOCKET_ERROR;
	}

	int Servers::CloseClient(int socketID, int clientSocketID)
	{
		map<int, Server*>::iterator sIter = m_servers.find(socketID);
		if(sIter != m_servers.end())
		{
			Server *server = sIter->second;
			int ret = server->CloseClient(clientSocketID);
			return ret;
		}
		return SOCKET_ERROR;
	}
	
	void Servers::RegisterLog(WriteServerLog writeLogCallBack)
	{
		m_writeServerLogCallBack = writeLogCallBack;
	}

	void Servers::RegisterRecv(RecvMsg recvMsgCallBack)
	{
		m_recvClientMsgCallBack = recvMsgCallBack;
	}

	int Servers::Send(int socketID, const char *str, int len)
	{
		return Server::Send(socketID, str, len);
	}

	int Servers::SendTo(int socketID, const char *str, int len)
	{
		map<int, Server*>::iterator sIter = m_servers.find(socketID);
		if(sIter != m_servers.end())
		{
			Server *server = sIter->second;
			return server->SendTo(str, len);
		}
		return -1;
	}

	int Servers::Start(int type, int port)
	{
		Server *server = new Server;
		int socketID = 0;
		if(type == 0)
		{
			socketID = server->StartTCP(port);
		}
		else
		{
			socketID = server->StartUDP(port);
		}
		if(socketID <= 0)
		{
			delete server;
			server = 0;
		}
		else
		{
			m_servers[socketID] = server;
			server->m_writeLogEvent = WriteLog;
			server->m_recvEvent = RecvClientMsg;
		}
		return socketID;
	}
}