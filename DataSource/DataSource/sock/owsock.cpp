// owclient.cpp : Defines the entry point for the console application.
//

#include "..\\stdafx.h"
#include "Clients.h"
#include "Servers.h"
using namespace OwLibSock;
#pragma comment(lib, "ws2_32.lib")
#include "winsock2.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

typedef void (__stdcall *MessageCallBack)(int socketID, int localSID, const char *str, int len);

typedef void (__stdcall *WriteLogCallBack)(int socketID, int localSID, int state, const char *log);

vector<MessageCallBack> m_clientCallBacks;

vector<WriteLogCallBack> m_clientLogs;

vector<MessageCallBack> m_serverCallBacks;

vector<WriteLogCallBack> m_serverLogs;

void __stdcall OnClientMsg(int socketID, int localSID, const char *str, int len)
{
	vector<MessageCallBack>::iterator sIter = m_clientCallBacks.begin();
	for(; sIter != m_clientCallBacks.end(); ++sIter)
	{
		double list[1] = {0};
		(*sIter)(socketID, localSID, str, len);
	}
}

void __stdcall OnClientLog(int socketID, int localSID, int state, const char *log)
{
	cout << socketID << ":" << log << "\r\n";
	vector<WriteLogCallBack>::iterator sIter = m_clientLogs.begin();
	for(; sIter != m_clientLogs.end(); ++sIter)
	{
		(*sIter)(socketID, localSID, state, log);
	}
}

void __stdcall OnServerMsg(int socketID, int localSID, const char *str, int len)
{
	vector<MessageCallBack>::iterator sIter = m_serverCallBacks.begin();
	for(; sIter != m_serverCallBacks.end(); ++sIter)
	{
		double list[1] = {0};
		(*sIter)(socketID, localSID, str, len);
	}
}

void __stdcall OnServerLog(int socketID, int localSID, int state, const char *log)
{
	cout << socketID << ":" << log << "\r\n";
	vector<WriteLogCallBack>::iterator sIter = m_serverLogs.begin();
	for(; sIter != m_serverLogs.end(); ++sIter)
	{
		(*sIter)(socketID, localSID, state, log);
	}
}

extern "C" __declspec(dllexport) int CloseClient(int socketID)
{
	return Clients::Close(socketID);
}

extern "C" __declspec(dllexport) int CloseServerClient(int socketID, int clientSocketID)
{
	return Servers::CloseClient(socketID, clientSocketID);
}

extern "C" __declspec(dllexport) int CloseServer(int socketID)
{
	return Servers::Close(socketID);
}

extern "C" __declspec(dllexport) int ConnectToServer(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout)
{
	int socketID = Clients::Connect(type, proxyType, ip, port, proxyIp, proxyPort, proxyUserName, proxyUserPwd, proxyDomain, timeout);
	Clients::RegisterLog(&OnClientLog);
	Clients::RegisterRecv(&OnClientMsg);
	return socketID;
}

extern "C" __declspec(dllexport) void RegisterClientCallBack(MessageCallBack callBack)
{
	m_clientCallBacks.push_back(callBack);
}

extern "C" __declspec(dllexport) void RegisterClientLog(WriteLogCallBack callBack)
{
	m_clientLogs.push_back(callBack);
}

extern "C" __declspec(dllexport) void RegisterServerCallBack(MessageCallBack callBack)
{
	m_serverCallBacks.push_back(callBack);
}

extern "C" __declspec(dllexport) void RegisterServerLog(WriteLogCallBack callBack)
{
	m_serverLogs.push_back(callBack);
}

extern "C" __declspec(dllexport) int SendByClient(int socketID, const char *str, int len)
{
	return Clients::Send(socketID, str, len);
}

extern "C" __declspec(dllexport) int SendByServer(int socketID, const char *str, int len)
{
	return Servers::Send(socketID, str, len);
}

extern "C" __declspec(dllexport) int StartServer(int type, int port)
{
	int socketID = Servers::Start(type, port);
	Servers::RegisterLog(&OnServerLog);
	Servers::RegisterRecv(&OnServerMsg); 
	return socketID;
}

