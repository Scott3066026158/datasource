#pragma once
#ifndef __CLIENTBASESERVICECT_H__
#define __CLIENTBASESERVICECT_H__

#include "Binary.h"
#include "..//api//CLock.h"
#include "MessageListener.h"
#include "SocketArray.h"
#define  DOWNHELPER_AGENTNAME         "SECURITY"  
#define  LEN_OF_BUFFER_FOR_QUERYINFO  128  
#define  MAX_DOWNLOAD_REQUEST_TIME    10   
#define  COMPRESSTYPE_NONE			  0
#define  COMPRESSTYPE_GZIP			  1

struct CMessage;

class ClientBaseService
{
private:
	//接收的数据量(单位byte)
	static _int64 m_downFlow;
	//发送的数据量(单位byte)
    static _int64 m_upFlow;
	//接收函数指针
	static MessageCallBack m_messageCallBack;
	//连接状态函数指针
	static WriteLogCallBack m_writeLogCallBack;
public://底层函数Handler
	static int CloseClient(int socketID);
	static int ConnectToServer(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout);
	static int ConnectToServer(const wchar_t *ip, int port);
	static void RegisterCallBack(MessageCallBack callBack);
	static void RegisterLog(WriteLogCallBack callBack);
	static int SendByClient(int socketID, const char *str, int len);
public://设置上传总量和上传总量
	static _int64 GetDownFlow();
	static void SetDownFlow(_int64 downFlow);
	static _int64 GetUpFlow();
	static void SetUpFlow(_int64 upFlow);
public:
	//默认数据接收回调函数
	static void __stdcall CallBack(int socketID, int localSID, const char *str, int len);
	//默认连接状态回调函数
	static void __stdcall WriteServerLog(int socketID, int localSID, int state, const char *log);
public:
	//添加一个服务(第一次添加默认开启CallBack函数作为接收接口)
	static void AddService(ClientBaseService *service);
	//获取所有服务
	static void GetServices(vector<ClientBaseService*> *services);
public:
	//获取本程序可执行文件路径
	static string GetProgramDir();
	//获取一个int主键(不为空,自增长)
	static int GetRequestID();
private:
	//MessageListener锁
	CLock m_lock;
	//监听者集合
	map<int, MessageListener*> m_listeners;
	map<int, CMessage*> m_waitMessages;
private:
	//Service压缩类型
	int m_compressType;
	//Service组ID
	int m_groupID;
	//Service服务ID
	int m_serviceID;
	//Service所占的SessionID
	int m_sessionID;
	//与服务端通信的SocketID
	int m_socketID;
	//Service名称
	String m_serviceName;
public://对象基本属性设置
	ClientBaseService();
	virtual ~ClientBaseService();
	int GetCompressType();
	void SetCompressType(int compressType);
	int GetGroupID();
	void SetGroupID(int groupID);
	int GetServiceID();
	void SetServiceID(int serviceID);
	int GetSessionID();
	void SetSessionID(int sessionID);
	int GetSocketID();
	void SetSocketID(int socketID);
	String GetServiceName();
	void SetServiceName(String serviceName);
public:
	//向指定连接发送一个心跳
	int KeepAlive(int socketID);
	//数据接收回调
	virtual void OnCallBack(Binary *binary, int socketID, int localSID, int len);
	//连接断开回调
	virtual void OnClientClose(int socketID, int localSID);
	//连接成功回调
	virtual void OnClientConnect(int socketID, int localSID);
	//消息处理(一般被重写)
	virtual void OnReceive(CMessage *message);
	//向服务端发送消息
	int SendToServer(CMessage *message);
	//消息分发(C->S)
	void SendToListener(CMessage *message);
public:
	//不清楚
	virtual void OnWaitMessageHandle(CMessage *message);
	//添加监听者
	void RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke);
	//不清楚
	void RegisterWait(int requestID, CMessage *message);
	//删除监听者
	void UnRegisterListener(int requestID);
	//删除监听者中的监听者
	void UnRegisterListener(int requestID, ListenerMessageCallBack callBack);
	//不清楚
	void UnRegisterWait(int requestID);
	//不清楚
	int WaitMessage(int requestID, int timeout);
};

#endif