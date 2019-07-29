#include "..\\stdafx.h"
#include "..\\sock\\Servers.h"
#include "BaseService.h"
#include "Binary.h"
#include "CMessage.h"

using namespace OwLibSock;

static int m_requestID = 10000;

map<int, String> BaseService::m_allIPs;
CLock BaseService::m_allIPsLock;
_int64 BaseService::m_downFlow = 0;
_int64 BaseService::m_upFlow = 0;
MessageCallBack BaseService::m_messageCallBack;
WriteLogCallBack BaseService::m_writeLogCallBack;
map<int, BaseService*> m_services;
map<int, SocketIDState> m_socketIDStates;
CLock m_socketIDStatesLock;

//funcCloseServerClient p_funcCloseServerClient;
//funcCloseServer p_funcCloseServer;
//funcRegisterCallBack p_funcRegisterCallBack;
//funcRegisterLog p_funcRegisterLog;
//funcSendByServer p_funcSendByServer;
//funcStartServer p_funcStartServer;
/*
DWORD WINAPI CheckKeepAlive(LPVOID lpParam)
{
	while(1)
	{
		if(DataCenter::m_heartBeat)
		{
			vector<SocketIDState> removeSocketIDs;
			m_socketIDStatesLock.Lock();
			map<int, SocketIDState>::iterator sIter = m_socketIDStates.begin();
			for(; sIter != m_socketIDStates.end(); ++sIter)
			{
				SocketIDState &socketIDState = sIter->second;
				if(socketIDState.m_alive == 2)
				{
					socketIDState.m_alive = 1;
				}
				else
				{
					if(socketIDState.m_alive != 0)
					{
						removeSocketIDs.push_back(socketIDState);
						socketIDState.m_alive = 0;
					}
				}
			}
			m_socketIDStatesLock.UnLock();
			int removeSocketIDsSize = (int)removeSocketIDs.size();
			for(int i = 0; i < removeSocketIDsSize; i++)
			{
				SocketIDState socketIDState = removeSocketIDs[i];
				BaseService::CloseServerClient(socketIDState.m_localSID, socketIDState.m_socketID);
			}
			removeSocketIDs.clear();
		}
		::Sleep(6000);
	}
	return 1;
}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BaseService::CloseServerClient(int localSID, int socketID)
{
	//return p_funcCloseServerClient(localSID, socketID);
	return Servers::CloseClient(localSID, socketID);
}

int BaseService::CloseServer(int socketID)
{
	//return p_funcCloseServer(socketID);
	return Servers::Close(socketID);
}

void BaseService::RegisterCallBack(MessageCallBack callBack)
{
	//p_funcRegisterCallBack(callBack);
	Servers::RegisterRecv(callBack);
}

void BaseService::RegisterLog(WriteLogCallBack callBack)
{
	//p_funcRegisterLog(callBack);
	Servers::RegisterLog(callBack);
}

int BaseService::SendByServer(int socketID, const char *str, int len)
{
	//return p_funcSendByServer(socketID, str, len);
	return Servers::Send(socketID, str, len);
}

int BaseService::StartServer(int type, int port)
{
	//return p_funcStartServer(type, port);
	return Servers::Start(type, port);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseService::BaseService()
{
	m_compressType = COMPRESSTYPE_GZIP;
	m_groupID = 0;
	m_serviceID = 0;
	m_sessionID = 0;
	m_socketID = 0;
}

BaseService::~BaseService()
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

int BaseService::GetCompressType()
{
	return m_compressType;
}

void BaseService::SetCompressType(int compressType)
{
	m_compressType = compressType;
}

_int64 BaseService::GetDownFlow()
{
	return m_downFlow;
}

void BaseService::SetDownFlow(_int64 downFlow)
{
	m_downFlow = downFlow;
}

int BaseService::GetGroupID()
{
	return m_groupID;
}

void BaseService::SetGroupID(int groupID)
{
	m_groupID = groupID;
}

int BaseService::GetServiceID()
{
	return m_serviceID;
}

void BaseService::SetServiceID(int serviceID)
{
	m_serviceID = serviceID;
}

int BaseService::GetSessionID()
{
	return m_sessionID;
}

void BaseService::SetSessionID(int sessionID)
{
	m_sessionID = sessionID;
}

int BaseService::GetSocketID()
{
	return m_socketID;
}

void BaseService::SetSocketID(int socketID)
{
	m_socketID = socketID;
}

_int64 BaseService::GetUpFlow()
{
	return m_upFlow;
}

void BaseService::SetUpFlow(_int64 upFlow)
{
	m_upFlow = upFlow;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseService::AddService(BaseService *service)
{
	if (!m_messageCallBack)
	{
		//string path = GetProgramDir() + "\\owsock_server(x64).dll";
		//HINSTANCE hdll = LoadLibraryA(path.c_str());
		//p_funcCloseServerClient = (funcCloseServerClient)GetProcAddress(hdll, "CloseServerClient");
		//p_funcCloseServer = (funcCloseServer)GetProcAddress(hdll, "CloseServer");
		//p_funcRegisterCallBack = (funcRegisterCallBack)GetProcAddress(hdll, "RegisterServerCallBack");
		//p_funcRegisterLog = (funcRegisterLog)GetProcAddress(hdll, "RegisterServerLog");
		//p_funcSendByServer = (funcSendByServer)GetProcAddress(hdll, "SendByServer");
		//p_funcStartServer = (funcStartServer)GetProcAddress(hdll, "StartServer");
		MessageCallBack callBack = &CallBack;
		m_messageCallBack = callBack;
		RegisterCallBack(callBack);
		WriteLogCallBack writeLogCallBack = &WriteServerLog;
		m_writeLogCallBack = writeLogCallBack;
		RegisterLog(m_writeLogCallBack);
	}
	m_services[service->GetServiceID()] = service;
}

void BaseService::CallBack(int socketID, int localSID, const char *str, int len)
{
	m_downFlow += len;
	if (len > 4)
    {
		Binary binary;
		binary.Write(str, len);
		int head = binary.ReadInt();
		int groupID = (int)binary.ReadShort();
		int serviceID = (int)binary.ReadShort();
		BaseService *service = 0;
		if(m_services.find(serviceID) != m_services.end())
		{
			m_services[serviceID]->OnCallBack(&binary, socketID, localSID, len);
		}
	}
	else
	{
		m_socketIDStatesLock.Lock();
		SocketIDState socketIDState;
		socketIDState.m_alive = 2;
		socketIDState.m_localSID = localSID;
		socketIDState.m_socketID = socketID;
		m_socketIDStates[socketID] = socketIDState;
		m_socketIDStatesLock.UnLock();
	}
}

void BaseService::DeleteService(BaseService *service)
{
	map<int, BaseService*>::iterator sIter = m_services.find(service->GetServiceID());
	if (sIter != m_services.end())
	{
		m_services.erase(sIter);
	}
}

string BaseService::GetProgramDir()
{
	char exeFullPath[MAX_PATH]; 
	string strPath;
	GetModuleFileNameA(0, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath; 
	int pos = (int)strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);
}


int BaseService::GetRequestID()
{
	return m_requestID ++;
}

void BaseService::GetServices(vector<BaseService*> *services)
{
	map<int, BaseService*>::iterator sIter = m_services.begin();
	for(; sIter != m_services.end(); ++sIter)
	{
		services->push_back(sIter->second);
	}
}

int BaseService::KeepAlive(int socketID)
{
	Binary binary;
	binary.Initialize(4, false);
	binary.WriteInt(4);
	return SendByServer(socketID, (char*)binary.GetBytes(), 4);
}

void BaseService::OnCallBack(Binary *binary, int socketID, int localSID, int len)
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
		uLong cLen = 128;
		if(uncBodyLength > cLen)
		{
			cLen = uncBodyLength;
		}
		char *buffer = new char[cLen];
		memset(buffer, '\0', cLen);
		CStrA::GZDeCompress((Byte*)body, bodyLength, (Byte*)buffer, &cLen);
		delete[] body;
		body = buffer;
		uncBodyLength = cLen;
	}
	CMessage* message = new CMessage(GetGroupID(), GetServiceID(), functionID, sessionID, requestID, socketID, state, compressType, uncBodyLength, body);
	OnReceive(message);
	OnWaitMessageHandle(message);
	delete[] body;
	body = 0;
}

void BaseService::OnClientClose(int socketID, int localSID)
{
}

void BaseService::OnClientConnect(int socketID, int localSID)
{
	printf("连接socketID为%d\n",socketID);
}

void BaseService::OnReceive(CMessage *message)
{
	m_lock.Lock();
	m_compressTypes[message->m_socketID] = message->m_compressType;
	m_lock.UnLock();
}

void BaseService::OnWaitMessageHandle(CMessage *message)
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

void BaseService::RegisterWait(int requestID, CMessage *message)
{
	m_lock.Lock();
	m_waitMessages[requestID] = message;
	m_lock.UnLock();
}

void BaseService::RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke)
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

int BaseService::Send(CMessage *message)
{
	Binary binary;
	char *buffer = 0;
	const char *body = message->m_body;
	int bodyLength = message->m_bodyLength;
	int uncBodyLength = bodyLength;
	m_lock.Lock();
	map<int, int>::iterator sIter = m_compressTypes.find(message->m_socketID);
	if(sIter != m_compressTypes.end())
	{
		message->m_compressType = sIter->second;
	}
	m_lock.UnLock();
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
	int ret = SendByServer(message->m_socketID, (char*)binary.GetBytes(), len);
	m_upFlow += ret;
	return ret;
}

int BaseService::Send(CMessage *message, vector<int> *socketIDs)
{
	message->m_compressType = COMPRESSTYPE_GZIP;
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
	int socketIDsSize = (int)socketIDs->size();
	char *bytes = (char*)binary.GetBytes();
	int lengthByte = binary.GetBytesLen();
	for(int i = 0; i < socketIDsSize; i++)
	{
		int ret = SendByServer((*socketIDs)[i], bytes, lengthByte);
		m_upFlow += ret;
	}
	return 1;
}

void BaseService::SendToListener(CMessage *message)
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

void BaseService::UnRegisterListener(int requestID)
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

void BaseService::UnRegisterListener(int requestID, ListenerMessageCallBack callBack)
{
	m_lock.Lock();
	map<int, MessageListener*>::iterator sIter = m_listeners.find(requestID);
	if(sIter != m_listeners.end())
	{
		sIter->second->Remove(callBack);
	}
	m_lock.UnLock();
}

void BaseService::UnRegisterWait(int requestID)
{
	m_lock.Lock();
	map<int, CMessage*>::iterator sIter = m_waitMessages.find(requestID);
	if(sIter != m_waitMessages.end())
	{
		m_waitMessages.erase(sIter);
	}
	m_lock.UnLock();
}

int BaseService::WaitMessage(int requestID, int timeout)
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

void BaseService::WriteServerLog(int socketID, int localSID, int state, const char *log)
{
	//登入
	if(state == 1)
	{
		string ip = log;
		String wIP;
		CStrA::stringTowstring(wIP, ip);
		wIP = CStrA::Replace(wIP, L"accept:", L"");
		m_allIPsLock.Lock();
		m_allIPs[socketID] = wIP;
		m_allIPsLock.UnLock();
		SocketIDState socketIDState;
		socketIDState.m_alive = 2;
		socketIDState.m_localSID = localSID;
		socketIDState.m_socketID = socketID;
		m_socketIDStates[socketID] = socketIDState;
		m_socketIDStatesLock.UnLock();
		map<int, BaseService*>::iterator sIter = m_services.begin();
		for(; sIter != m_services.end(); ++sIter)
		{
			BaseService *service = sIter->second;
			service->OnClientConnect(socketID, localSID);
			//if(service->GetServiceID()  == 55)
			//{
			//	service->OnClientConnect(socketID, localSID);
			//}
		}
	}
	//登出
	else if(state == 2)
	{
		map<int, BaseService*>::iterator sIter = m_services.begin();
		for(; sIter != m_services.end(); ++sIter)
		{
			BaseService *service = sIter->second;
			service->OnClientClose(socketID, localSID);
		}
	}
}


