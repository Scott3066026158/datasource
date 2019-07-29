/*****************************************************************************\
*                                                                             *
* Servers.h -    Servers functions, types, and definitions.                   *
*                                                                             *
*               Version 1.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2010-2014, Lord's server. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __SERVERS_H__
#define __SERVERS_H__
#pragma once

namespace OwLibSock
{
	typedef void (__stdcall *RecvMsg)(int socketID, int localSID, const char *str, int len);

	typedef void (__stdcall *WriteServerLog)(int socketID, int localSID, int state, const char *str);

	class Servers
	{
	public:
		static void __stdcall RecvClientMsg(int socketID, int localSID, const char *str, int len);
		static void __stdcall WriteLog(int socketID, int localSID, int state, const char *log);
	public:
		static int Close(int socketID);
		static int CloseClient(int socketID, int clientSocketID);
		static void RegisterLog(WriteServerLog writeLogCallBack);
		static void RegisterRecv(RecvMsg recvMsgCallBack);
		static int Send(int socketID, const char *str, int len);
		static int SendTo(int socketID, const char *str, int len);
		static int Start(int type, int port);
	};
}
#endif