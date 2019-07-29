/*****************************************************************************\
*                                                                             *
* Server.h -    Server functions, types, and definitions.                     *
*                                                                             *
*               Version 1.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2010-2014, Lord's server. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__
#pragma once
#include "..//stdafx.h"
#include "Servers.h"
#pragma comment (lib,"winmm")

namespace OwLibSock
{
	typedef enum
	{
		RECV_POSTED
	}OPERATION_TYPE;

	typedef struct
	{
		WSAOVERLAPPED  overlap;
		WSABUF         Buffer;
		char           szMessage[1024];
		DWORD          NumberOfBytesRecvd;
		DWORD          Flags;
		OPERATION_TYPE OperationType;
	}PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

	class PUSHDATA
	{
	public:
		PUSHDATA();
		~PUSHDATA();
		char *m_buffer;
		int m_bufferRemain;
		bool m_get;
		int m_head;
		int m_headSize;
		char m_headStr[4];
		int m_index;
		int m_len;
		int m_pos;
		SOCKET m_socket;
		char *m_str;
		int m_strRemain;
		bool m_submit;
	};

	class Server
	{
	public:
		SOCKADDR_IN m_addr;
		HANDLE m_completionPort;
		vector<PUSHDATA*> m_datas;
		SOCKET m_hSocket;
		int m_port;
		RecvMsg m_recvEvent;
		WriteServerLog m_writeLogEvent;
	public:
		Server();
		virtual ~Server();
		int Close(int socketID);
		int CloseClient(int socketID);
		int Recv(PUSHDATA *data);
		static int Send(int socketID, const char *str, int len);
		int SendTo(const char *str, int len);
		int StartTCP(int port);
		int StartUDP(int port);
		void WriteLog(int socketID, int localSID, int state, const char *log);
	public:
		static void WSStart();
		static void WSStop();
	};
}
#endif