
#include "../stdafx.h"
#include "Clients.h"
#include "Servers.h"
using namespace OwLibSock;
#pragma comment(lib, "ws2_32.lib")
#include "winsock2.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif



namespace OwLibSock
{
	class OwSock
	{
		int CloseClient(int socketID);

		int CloseServerClient(int socketID, int clientSocketID);

		int CloseServer(int socketID);
		int ConnectToServer(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, 
					const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout);

		void RegisterClientCallBack(MessageCallBack callBack);
		void RegisterClientLog(WriteLogCallBack callBack);

		void RegisterServerCallBack(MessageCallBack callBack);
		void RegisterServerLog(WriteLogCallBack callBack);

		int SendByClient(int socketID, const char *str, int len);

		int SendByServer(int socketID, const char *str, int len);

		int StartServer(int type, int port);
	};
}

