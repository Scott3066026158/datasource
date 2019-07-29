#include "..\\stdafx.h"
#include "..\\sock\\Clients.h"
#include "..\\api\\CStr.h"
#include "..\\api\\PublicMethod.h"
#include "ClientBaseService.h"
#include "CMessage.h"

using namespace OwLibSock;

static int m_requestID = 10000;

_int64 ClientBaseService::m_downFlow = 0;
_int64 ClientBaseService::m_upFlow = 0;

MessageCallBack ClientBaseService::m_messageCallBack;
WriteLogCallBack ClientBaseService::m_writeLogCallBack;
map<int, ClientBaseService*> m_services;

//funcCloseClient p_funcCloseClient;
//funcConnectToServer p_funcConnectToServer;
//funcRegisterCallBack p_funcClientRegisterCallBack;
//funcRegisterLog p_funcClientRegisterLog;
//funcSendByClient p_funcSendByClient;

int ClientBaseService::CloseClient(int socketID)
{
	//return p_funcCloseClient(socketID);
	return Clients::Close(socketID);
}

int ClientBaseService::ConnectToServer(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout)
{
	//return p_funcConnectToServer(type, proxyType, ip, port, proxyIp, proxyPort, proxyUserName, proxyUserPwd, proxyDomain, timeout);
	return Clients::Connect(type, proxyType, ip, port, proxyIp, proxyPort, proxyUserName, proxyUserPwd, proxyDomain, timeout);
}

int ClientBaseService::ConnectToServer(const wchar_t *ip, int port)
{
	string cstr_ip;
	String wip(ip);
	CStrA::stringTowstring(wip, cstr_ip);
	return ConnectToServer(0, 0, cstr_ip.c_str(), port, "", 0, "", "", "", 10);
}

void ClientBaseService::RegisterCallBack(MessageCallBack callBack)
{
	//p_funcClientRegisterCallBack(callBack);
	Clients::RegisterRecv(callBack);
}

void ClientBaseService::RegisterLog(WriteLogCallBack callBack)
{
	//p_funcClientRegisterLog(callBack);
	Clients::RegisterLog(callBack);
}

int ClientBaseService::SendByClient(int socketID, const char *str, int len)
{
	//return p_funcSendByClient(socketID, str, len);
	return Clients::Send(socketID, str, len);
}

ClientBaseService::ClientBaseService()
{
	m_compressType = COMPRESSTYPE_NONE;
	m_groupID = 0;
	m_serviceID = 0;
	m_sessionID = 0;
	m_socketID = -1;
	m_lock.SetName("ClientBaseService_m_lock");
}

ClientBaseService::~ClientBaseService()
{
	m_lock.Lock();
	map<int, MessageListener*>::iterator sIter = m_listeners.begin();
	for(; sIter != m_listeners.end(); ++sIter)
	{
		delete sIter->second;
	}
	m_listeners.clear();
	m_waitMessages.clear();
	m_lock.UnLock();
}

int ClientBaseService::GetCompressType()
{
	return m_compressType;
}

void ClientBaseService::SetCompressType(int compressType)
{
	m_compressType = compressType;
}

_int64 ClientBaseService::GetDownFlow()
{
	return m_downFlow;
}

void ClientBaseService::SetDownFlow(_int64 downFlow)
{
	m_downFlow = downFlow;
}

int ClientBaseService::GetGroupID()
{
	return m_groupID;
}

void ClientBaseService::SetGroupID(int groupID)
{
	m_groupID = groupID;
}

int ClientBaseService::GetServiceID()
{
	return m_serviceID;
}

void ClientBaseService::SetServiceID(int serviceID)
{
	m_serviceID = serviceID;
}

int ClientBaseService::GetSessionID()
{
	return m_sessionID;
}

void ClientBaseService::SetSessionID(int sessionID)
{
	m_sessionID = sessionID;
}

int ClientBaseService::GetSocketID()
{
	return m_socketID;
}

void ClientBaseService::SetSocketID(int socketID)
{
	m_socketID = socketID;
}

String ClientBaseService::GetServiceName()
{
	return m_serviceName;
}

void ClientBaseService::SetServiceName(String serviceName)
{
	m_serviceName = serviceName;
}

_int64 ClientBaseService::GetUpFlow()
{
	return m_upFlow;
}

void ClientBaseService::SetUpFlow(_int64 upFlow)
{
	m_upFlow = upFlow;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientBaseService::AddService(ClientBaseService *service)
{
	if (!m_messageCallBack)
	{
		//string path = GetProgramDir() + "\\owsock_client(x64).dll";
		//HINSTANCE hdll = LoadLibraryA(path.c_str());
		//p_funcCloseClient = (funcCloseClient)GetProcAddress(hdll, "CloseClient");
		//p_funcConnectToServer = (funcConnectToServer)GetProcAddress(hdll, "ConnectToServer");
		//p_funcClientRegisterCallBack = (funcRegisterCallBack)GetProcAddress(hdll, "RegisterClientCallBack");
		//p_funcClientRegisterLog = (funcRegisterLog)GetProcAddress(hdll, "RegisterClientLog");
		//p_funcSendByClient = (funcSendByClient)GetProcAddress(hdll, "SendByClient");
		MessageCallBack callBack = &CallBack;
		m_messageCallBack = callBack;
		RegisterCallBack(callBack);
		WriteLogCallBack writeLogCallBack = &WriteServerLog;
		m_writeLogCallBack = writeLogCallBack;
		RegisterLog(m_writeLogCallBack);
	}
	m_services[service->GetServiceID()] = service;
}

void ClientBaseService::CallBack(int socketID, int localSID, const char *str, int len)
{
	m_downFlow += len;
	if (len > 4)
    {
		Binary binary;
		binary.Write(str, len);
		int head = binary.ReadInt();
		int groupID = (int)binary.ReadShort();
		int serviceID = (int)binary.ReadShort();
		ClientBaseService *service = 0;
		if(m_services.find(serviceID) != m_services.end())
		{
			m_services[serviceID]->OnCallBack(&binary, socketID, localSID, len);
		}
	}
}

string ClientBaseService::GetProgramDir()
{
	char exeFullPath[MAX_PATH]; 
	string strPath;
	GetModuleFileNameA(0, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath; 
	int pos = (int)strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);
}

int ClientBaseService::GetRequestID()
{
	return m_requestID ++;
}

void ClientBaseService::GetServices(vector<ClientBaseService*> *services)
{
	map<int, ClientBaseService*>::iterator sIter = m_services.begin();
	for(; sIter != m_services.end(); ++sIter)
	{
		services->push_back(sIter->second);
	}
}

int ClientBaseService::KeepAlive(int socketID)
{
	Binary binary;
	binary.Initialize(4, false);
	binary.WriteInt(4);
	return SendByClient(socketID, (char*)binary.GetBytes(), 4);
}

void ClientBaseService::OnCallBack(Binary *binary, int socketID, int localSID, int len)
{
	int headSize = sizeof(int) * 4 + sizeof(short) * 3 + sizeof(byte) * 2;
	int functionID = (int)binary->ReadShort();
	int sessionID = binary->ReadInt();
	int requestID = binary->ReadInt();
	int state = (int)binary->ReadChar();
	int compressType = (int)binary->ReadChar();
	int uncBodyLength = binary->ReadInt();
	int bodyLength = len - headSize;
	char *body = new char[bodyLength];
	memset(body, '\0', bodyLength);
	binary->Read(body, bodyLength);
	if (compressType == COMPRESSTYPE_GZIP)
	{
		uLong deLen = uncBodyLength;
		char *buffer = new char[deLen];
		memset(buffer, '\0', deLen);
		CStrA::GZDeCompress((Byte*)body, bodyLength, (Byte*)buffer, &deLen);
		delete[] body;
		body = buffer;
	}
	CMessage message(GetGroupID(), GetServiceID(), functionID, sessionID, requestID, socketID, state, compressType, uncBodyLength, body);
	OnReceive(&message);
	OnWaitMessageHandle(&message);
	delete[] body;
	body = 0;
}

void ClientBaseService::OnClientClose(int socketID, int localSID)
{
}

void ClientBaseService::OnClientConnect(int socketID, int localSID)
{
}

void ClientBaseService::OnReceive(CMessage *message)
{
	
}

void ClientBaseService::OnWaitMessageHandle(CMessage *message)
{
	if((int)m_waitMessages.size() > 0)
	{
		m_lock.Lock();
		map<int, CMessage*>::iterator sIter = m_waitMessages.find(message->m_requestID);
		if(sIter != m_waitMessages.end())
		{
			*(sIter->second) = *message;
		}
		m_lock.UnLock();
	}
}

void ClientBaseService::RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke)
{
	m_lock.Lock();
	MessageListener *listener = 0;
	map<int, MessageListener*>::iterator sIter = m_listeners.find(requestID);
	if(sIter != m_listeners.end())
	{
		listener = sIter->second;
	}
	else
	{
		listener = new MessageListener;
		m_listeners[requestID] = listener;
	}
	listener->Add(callBack, pInvoke);
	m_lock.UnLock();
}

void ClientBaseService::RegisterWait(int requestID, CMessage *message)
{
	m_lock.Lock();
	m_waitMessages[requestID] = message;
	m_lock.UnLock();
}

int ClientBaseService::SendToServer(CMessage *message)
{
	Binary binary;
	char *buffer = 0;
	const char *body = message->m_body;
	int bodyLength = message->m_bodyLength;
	int uncBodyLength = bodyLength;
	if (message->m_compressType == COMPRESSTYPE_GZIP)
    {
		uLong cLen = 128;
		if(uncBodyLength > cLen)
		{
			cLen = uncBodyLength;
		}
		buffer = new char[cLen];
		memset(buffer, '\0', cLen);
		CStrA::GZCompress((Byte*)body, bodyLength, (Byte*)buffer, &cLen);
		body = buffer;
		bodyLength = (int)cLen;
	}
	int len = sizeof(int) * 4 + bodyLength + sizeof(short) * 3 + sizeof(char) * 2;
	binary.Initialize(len, false);
	binary.WriteInt(len);
	binary.WriteShort((short)message->m_groupID);
	binary.WriteShort((short)message->m_serviceID);
	binary.WriteShort((short)message->m_functionID);
	binary.WriteInt(message->m_sessionID);
	binary.WriteInt(message->m_requestID);
	binary.WriteChar((char)message->m_state);
	binary.WriteChar((char)message->m_compressType);
	binary.WriteInt(uncBodyLength);
	binary.Write(body, bodyLength);
	if(buffer)
	{
		delete[] buffer;
		buffer = 0;
	}
	int ret = SendByClient(message->m_socketID, (char*)binary.GetBytes(), len);
	m_upFlow += ret;
	return ret;
}

void ClientBaseService::SendToListener(CMessage *message)
{
	MessageListener *listener = 0;
	void *pInvoke = 0;
	m_lock.Lock();
	map<int, MessageListener*>::iterator sIter = m_listeners.find(message->m_requestID);
	if(sIter != m_listeners.end())
	{
		listener = sIter->second;
	}
	m_lock.UnLock();
	if(listener)
	{
		listener->CallBack(message);
	}
}

void ClientBaseService::UnRegisterListener(int requestID)
{
	m_lock.Lock();
	map<int, MessageListener*>::iterator sIter = m_listeners.find(requestID);
	if(sIter != m_listeners.end())
	{
		delete sIter->second;
		m_listeners.erase(sIter);
	}
	m_lock.UnLock();
}

void ClientBaseService::UnRegisterListener(int requestID, ListenerMessageCallBack callBack)
{
	m_lock.Lock();
	map<int, MessageListener*>::iterator sIter = m_listeners.find(requestID);
	if(sIter != m_listeners.end())
	{
		sIter->second->Remove(callBack);
	}
	m_lock.UnLock();
}

void ClientBaseService::UnRegisterWait(int requestID)
{
	m_lock.Lock();
	map<int, CMessage*>::iterator sIter = m_waitMessages.find(requestID);
	if(sIter != m_waitMessages.end())
	{
		m_waitMessages.erase(sIter);
	}
	m_lock.UnLock();
}

int ClientBaseService::WaitMessage(int requestID, int timeout)
{
	int state = 0;
	while(timeout > 0)
	{
		m_lock.Lock();
		map<int, CMessage*>::iterator sIter = m_waitMessages.find(requestID);
		if(sIter != m_waitMessages.end())
		{
			CMessage *message = sIter->second;
			if(message->m_bodyLength > 0)
			{
				state = 1;
				m_lock.UnLock();
				break;
			}
		}
		else
		{
			m_lock.UnLock();
			break;
		}
		m_lock.UnLock();
		timeout -= 10;
		Sleep(10);
	}
	UnRegisterWait(requestID);
	return state;
}

void ClientBaseService::WriteServerLog(int socketID, int localSID, int state, const char *log)
{
	//连接成功
	if(state == 1)
	{
		map<int, ClientBaseService*>::iterator sIter = m_services.begin();
		for(; sIter != m_services.end(); ++sIter)
		{
			ClientBaseService *service = sIter->second;
			service->OnClientConnect(socketID, localSID);
		}
	}
	//断开连接或连接错误
	else if(state == 2 || state == 3)
	{
		map<int, ClientBaseService*>::iterator sIter = m_services.begin();
		for(; sIter != m_services.end(); ++sIter)
		{
			ClientBaseService *service = sIter->second;
			service->OnClientClose(socketID, localSID);
		}
	}
	else
	{
		printf("连接标识:%d\n",state);
	}
}