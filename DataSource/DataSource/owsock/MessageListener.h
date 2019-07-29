#pragma once
#ifndef __MESSAGELISTENER_H__
#define __MESSAGELISTENER_H__

#include "CMessage.h"
typedef void (__stdcall *ListenerMessageCallBack)(CMessage *message, void *pInvoke);
typedef void (__stdcall *MessageCallBack)(int socketID, int localSID, const char *str, int len);
typedef void (__stdcall *WriteLogCallBack)(int socketID, int localSID, int state, const char *log);
typedef int (*funcCloseServerClient)(int, int);
typedef int (*funcCloseServer)(int);
typedef void (*funcRegisterCallBack)(MessageCallBack);
typedef void (*funcRegisterLog)(WriteLogCallBack);
typedef int (*funcSendByServer)(int, const char*, int);
typedef int (*funcStartServer)(int, int);
typedef int (*funcCloseClient)(int);
typedef int (*funcConnectToServer)(int, int, const char*, int, const char*, int, const char*, const char*, const char*, int);
typedef int (*funcSendByClient)(int, const char*, int);

class MessageListener
{
private:
	vector<ListenerMessageCallBack> m_callBacks;
	vector<void*> m_callBackInvokes;
public:
	MessageListener();
	virtual ~MessageListener();
public:
	void Add(ListenerMessageCallBack callBack, void *pInvoke);
	void CallBack(CMessage *message);
	void Clear();
	void Remove(ListenerMessageCallBack callBack);
};

struct SocketIDState
{
public:
	int m_alive;
	int m_localSID;
	int m_socketID;
};

#endif