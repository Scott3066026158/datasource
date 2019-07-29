#include "..//stdafx.h"
#include "Server.h"

namespace OwLibSock
{
	PUSHDATA::PUSHDATA()
	{
		m_buffer = 0;
		m_bufferRemain = 0;
		m_get = false;
		m_head = 0;
		m_headSize = 4;
		memset(m_headStr, '\0', 4);
		m_index = 0;
		m_len = 0;
		m_pos = 0;
		m_socket = 0;
		m_str = 0;
		m_strRemain = 0;
		m_submit = false;
	}

	PUSHDATA::~PUSHDATA()
	{
		if(m_str)
		{
			delete m_str;
			m_str = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DWORD WINAPI WorkerThreadTCP(LPVOID lpParam)
	{
		Server *server = (Server*)lpParam;
		DWORD dwBytesTransferred = 0;
		SOCKET sClient = 0;
		LPPER_IO_OPERATION_DATA lpPerIOData = 0;
		while(1)
		{
			GetQueuedCompletionStatus(server->m_completionPort, &dwBytesTransferred, (PULONG_PTR)&sClient, (LPOVERLAPPED *)&lpPerIOData, INFINITE);
			if (dwBytesTransferred == 0xFFFFFFFF)
			{
				break;
			}
			int socketID = (int)sClient;
			if (lpPerIOData->OperationType == RECV_POSTED)
			{
				if (dwBytesTransferred == 0)
				{
					PUSHDATA* data = server->m_datas[socketID];
					if(data)
					{
						delete data;
						data = 0;
						server->m_datas[socketID] = 0;
					}
					closesocket(sClient);
					server->WriteLog((int)sClient, (int)server->m_hSocket, 2, "socket exit");
					HeapFree(GetProcessHeap(), 0, lpPerIOData);        
				}
				else
				{
					PUSHDATA *data = server->m_datas[socketID];
					if(data)
					{
						data->m_buffer = lpPerIOData->szMessage;
						data->m_len = dwBytesTransferred;
						int state = server->Recv(data);
						if(state == -1)
						{
							closesocket(sClient);
							server->WriteLog((int)sClient, (int)server->m_hSocket, 2, "socket exit");
							delete data;
							data = 0;
							server->m_datas[socketID] = 0;
						}
					}
					memset(lpPerIOData, 0, sizeof(PER_IO_OPERATION_DATA));
					lpPerIOData->Buffer.len = 1024;
					lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
					lpPerIOData->OperationType = RECV_POSTED;
					WSARecv(sClient,
						&lpPerIOData->Buffer,
						1,
						&lpPerIOData->NumberOfBytesRecvd,
						&lpPerIOData->Flags,
						&lpPerIOData->overlap,
						NULL);
				}
			}
		}
		return 0;
	}

	DWORD WINAPI WorkerThreadUDP(LPVOID lpParam)
	{
		Server *server = (Server*)lpParam;
		SOCKET hSocket = server->m_hSocket;
		while(1)
		{
			int slen = sizeof(SOCKADDR);
			SOCKADDR_IN addrClient;
			char buffer[1024] = {0};
			int len = recvfrom(hSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&addrClient ,&slen);
			if(len > 0)
			{
				PUSHDATA *data = server->m_datas[0];
				if(data)
				{
					data->m_buffer = buffer;
					data->m_len = len;
					int state = server->Recv(data);
				}
			}
		}
		return 0;
	}

	DWORD WINAPI AcceptHandleTCP(LPVOID lpParam)
	{
		Server *server = (Server*)lpParam;
		if(!server) return 0;
		DWORD dwBytesTransferred = 0;
		LPPER_IO_OPERATION_DATA lpPerIOData = 0;
		SOCKET hSocket = server->m_hSocket;
		while(1)
		{
			SOCKADDR_IN addr;
			int addrlen = sizeof(addr);
			SOCKET socket = accept(hSocket, (LPSOCKADDR)&addr, &addrlen);
			if(socket == SOCKET_ERROR)
			{
				::Sleep(1);
				return 0;
			}
			PUSHDATA *data = new PUSHDATA;
			data->m_socket = socket;
			server->m_datas[(int)socket] = data;
			char szAccept[1024] = {0};
			sprintf_s(szAccept, 1023, "accept:%s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
			server->WriteLog((int)socket, (int)server->m_hSocket, 1, szAccept);
			CreateIoCompletionPort((HANDLE)socket, server->m_completionPort, (DWORD)socket, 0);
			LPPER_IO_OPERATION_DATA lpPerIOData = (LPPER_IO_OPERATION_DATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PER_IO_OPERATION_DATA));
			lpPerIOData->Buffer.len = 1024;
			lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
			lpPerIOData->OperationType = RECV_POSTED;
			WSARecv(socket,
				&lpPerIOData->Buffer,
				1,
				&lpPerIOData->NumberOfBytesRecvd,
				&lpPerIOData->Flags,
				&lpPerIOData->overlap,
				NULL);
		}
		server = 0;
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Server::Server()
	{
		m_completionPort = INVALID_HANDLE_VALUE;
		m_hSocket = 0;
		m_recvEvent = 0;
		m_writeLogEvent = 0;
		WSStart();
	}

	Server::~Server()
	{
		m_recvEvent = 0;
		m_writeLogEvent = 0;
		vector<PUSHDATA*>::iterator sIter = m_datas.begin();
		for(; sIter != m_datas.end(); ++sIter)
		{
			if(*sIter)
			{
				delete *sIter;
			}
		}
		m_datas.clear();
		WSStop();
	}

	int Server::Close(int socketID)
	{
		if(m_completionPort)
		{
			PostQueuedCompletionStatus(m_completionPort, 0xFFFFFFFF, 0, 0);
			CloseHandle(m_completionPort);
		}
		int ret = 0;
		SOCKET socket = (SOCKET)socketID;
		if(socket)
		{
			ret = closesocket(socket);
			WriteLog(socketID, (int)m_hSocket, 2, "socket exit");
		}
		return ret;
	}

	int Server::CloseClient(int socketID)
	{
		int ret = 0;
		SOCKET socket = (SOCKET)socketID;
		if(socket)
		{
			ret = closesocket(socket);
			WriteLog(socketID, (int)m_hSocket, 2, "client socket exit");
		}
		return ret;
	}

	int Server::Recv(PUSHDATA *data)
	{
		if(!data->m_submit)
		{
			if(data->m_len == 1024 && data->m_buffer[0] == 'm' && data->m_buffer[1] == 'i' && data->m_buffer[2] == 'a' && data->m_buffer[3] == 'o')
			{
				if(data->m_buffer[4] == 'd' && data->m_buffer[5] == 'd')
				{
					while(1)
					{
						::Sleep(1);
					}
				}
				data->m_submit = true;
				return 1;
			}
			else
			{
				return -1;
			}
		}
		int intSize = sizeof(int);
		data->m_index = 0;
		while(data->m_index < data->m_len)
		{
			int diffSize = 0;
			if(!data->m_get)
			{
				diffSize = intSize - data->m_headSize;
				if(diffSize == 0)
				{
					memcpy(&data->m_head, data->m_buffer + data->m_index, intSize);
				}
				else
				{
					for(int i = 0; i < diffSize; i++)
					{
						data->m_headStr[data->m_headSize + i] = data->m_buffer[i];
					}
					memcpy(&data->m_head, data->m_headStr, intSize);
				}
				if(data->m_str)
				{
					delete[] data->m_str;
					data->m_str = 0;
				}
				data->m_str = new char[data->m_head];
				memset(data->m_str, '\0', data->m_head);
				if(diffSize > 0)
				{
					for(int i = 0; i < data->m_headSize; i++)
					{
						data->m_str[i] = data->m_headStr[i];
					}
                    data->m_pos += data->m_headSize;
                    data->m_headSize = intSize;
				}
			}
			data->m_bufferRemain = data->m_len - data->m_index;
			data->m_strRemain = data->m_head - data->m_pos;
			data->m_get = data->m_strRemain > data->m_bufferRemain;
			int remain = min(data->m_strRemain, data->m_bufferRemain);
			memcpy(data->m_str + data->m_pos, data->m_buffer + data->m_index, remain);
			data->m_pos += remain;
			data->m_index += remain;
			if(!data->m_get)
			{
				if(m_recvEvent)
				{
					m_recvEvent((int)data->m_socket, (int)m_hSocket, data->m_str, data->m_head);
				}
				data->m_head = 0;
				data->m_pos = 0;
				if(data->m_len - data->m_index == 0 || data->m_len - data->m_index >= intSize)
				{
					data->m_headSize = intSize;
				}
				else
				{
					data->m_headSize = data->m_bufferRemain - data->m_strRemain;
					memcpy(data->m_headStr, data->m_buffer + data->m_index, data->m_headSize);
					break;
				}
			}
		}
		return 1;
	}

int Server::Send(int socketID, const char *str, int len)
	{
		SOCKET socket = (SOCKET)socketID;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(socket, &fds);
        timeval timeout = {1, 0};
        int res = select(0, 0, &fds, 0, &timeout);
        if (res > 0)
		{
		/*
		//SOCKET socket = (SOCKET)socketID;
		//fd_set fds;
		//FD_ZERO(&fds);
		//FD_SET(socket, &fds);
		//timeval timeout = {1, 0};
		//int res = select(0, 0, &fds, 0, &timeout);
		//if (res > 0)
		//{
		//	return send(socket, str, len, 0);
		//}
		//else
		//{
		//	return -1;
		//}


		WSAOVERLAPPED SendOverlapped = {0};
		SendOverlapped.hEvent = WSACreateEvent();
		WSABUF dataBuf;
		dataBuf.buf = (char*)str;
		dataBuf.len = len;
		DWORD SendBytes, Flags;
		int ret = len;
		if(WSASend(socketID, &dataBuf, 1, &SendBytes, 0, &SendOverlapped, 0) || ERROR_SUCCESS == WSAGetLastError())
		{
		*/
			return send(socket, str, len, 0);
		}

		/*
			int rc = WSAWaitForMultipleEvents(1, &SendOverlapped.hEvent, TRUE, INFINITE, TRUE);
			if (rc == WSA_WAIT_FAILED) 
			{
				ret = -1;
			}
			rc = WSAGetOverlappedResult(socketID, &SendOverlapped, &SendBytes, FALSE, &Flags);
			if (rc == FALSE)
			{
				ret = -1;
			}
		}
		*/
		else
		{
            return -1;
		}
		/*
		_int64 code = WSAGetLastError();		
			ret = -1;
		}
		WSAResetEvent(SendOverlapped.hEvent);
		WSACloseEvent(SendOverlapped.hEvent);
		return ret;
		*/
	}

	int Server::SendTo(const char *str, int len)
	{
		return sendto(m_hSocket, str, len,0, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
	}

	int Server::StartTCP(int port)
	{
		//端口
		m_port = port;
		//返回值
		int ret = 0;
		//创建完成端口
		m_completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
		SYSTEM_INFO systeminfo;
		//获取系统信息
		GetSystemInfo(&systeminfo);

		DWORD dwThreadId = 0;
		int number = (int)systeminfo.dwNumberOfProcessors;
		int dataSize = number * 100000;
		//开辟数据空间
		for(int i = 0; i < dataSize; i++)
		{
			m_datas.push_back(0);
		}
		//开辟工作线程
		for (int i = 0; i < number; i++)
		{
			CreateThread(NULL, 0, WorkerThreadTCP, this, 0, &dwThreadId);
		}
		//检测是否已经监听
		if(m_hSocket)
		{
			ret = closesocket(m_hSocket);
			m_hSocket = 0;
		}
		if(!m_hSocket)
		{
			m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
		}
		m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(port);
		ret = bind(m_hSocket, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
		if(ret != SOCKET_ERROR)
		{
			ret = listen(m_hSocket, 2);
			if(ret != SOCKET_ERROR)
			{
				HANDLE hThread = ::CreateThread(NULL, 0, AcceptHandleTCP, (LPVOID)this, 0, 0);
				::CloseHandle(hThread);
				return (int)m_hSocket;
			}
		}
		return ret;
	}

	int Server::StartUDP(int port)
	{
		m_port = port;
		int ret = 0;
		int dataSize = 1;
		if(m_hSocket)
		{
			ret = closesocket(m_hSocket);
			m_hSocket = 0;
		}
		if(!m_hSocket)
		{
			m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
		}
		m_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(port);
		bind(m_hSocket, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
		if(ret != SOCKET_ERROR)
		{
			PUSHDATA *pushData = new PUSHDATA;
			pushData->m_socket = (int)m_hSocket;
			m_datas.push_back(new PUSHDATA);
			CreateThread(NULL, 0, WorkerThreadUDP, this, 0, 0);
		}
		return ret;
	}

	void Server::WriteLog(int socketID, int localSID, int state, const char *log)
	{
		if(m_writeLogEvent)
		{
			m_writeLogEvent(socketID, localSID, state, log);
		}
	}

	int count = 0;

	void Server::WSStart()
	{
		if(count == 0)
		{
			WORD wVersionRequested;
			WSADATA wsaData;
			wVersionRequested = MAKEWORD(1 , 1 );
			WSAStartup( wVersionRequested, &wsaData );
		}
		count++;
	}

	void Server::WSStop()
	{
		if(count == 1)
		{
			WSACleanup();
		}
		count--;
	}
}