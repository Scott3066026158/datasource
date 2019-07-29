#pragma once
#ifndef __BASESERVICE_H__
#define __BASESERVICE_H__

#include <string>
#include <map>
#include "Binary.h"
#include "..//api//CLock.h"
#include "SocketArray.h"
#include "MessageListener.h"

using namespace std;

//Message压缩标志 0不压缩 1压缩
#define  COMPRESSTYPE_NONE			  0
#define  COMPRESSTYPE_GZIP			  1

//接收端父类
class BaseService
{
public:
	//所有客户端IP地址
	static map<int, String> m_allIPs;
	//IP集合锁
	static CLock m_allIPsLock;
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
	static int CloseServerClient(int localSID, int socketID);
	static int CloseServer(int socketID);
	static void RegisterCallBack(MessageCallBack callBack);
	static void RegisterLog(WriteLogCallBack callBack);
	static int SendByServer(int socketID, const char *str, int len);
	static int StartServer(int type, int port);
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
	static void AddService(BaseService *service);
	//删除一个服务
	static void DeleteService(BaseService *service);
	//获取所有服务
	static void GetServices(vector<BaseService*> *services);
public:
	//获取本程序可执行文件路径
	static string GetProgramDir();
	//获取一个int主键(不为空,自增长)
	static int GetRequestID();
protected:
	//所有连接的数据压缩标记
	map<int, int> m_compressTypes;
	//监听者集合
	map<int, MessageListener*> m_listeners;
	//MessageListener锁
	CLock m_lock;
	//不清楚
	map<int, CMessage*> m_waitMessages;
protected:
	//Service压缩类型
	int m_compressType;
	//Service组ID
	int m_groupID;
	//Service服务ID
	int m_serviceID;
	//Service所占的SessionID
	int m_sessionID;
	//Service所占的SocketID
	int m_socketID;
	//Service名称
	String m_serviceName;
public:
	BaseService();
	virtual ~BaseService();
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
public:
	//向指定连接发送一个心跳
	virtual int KeepAlive(int socketID);
	//数据接收回调
	virtual void OnCallBack(Binary *binary, int socketID, int localSID, int len);
	//连接断开回调
	virtual void OnClientClose(int socketID, int localSID);
	//连接成功回调
	virtual void OnClientConnect(int socketID, int localSID);
	//消息处理(一般被重写)
	virtual void OnReceive(CMessage *message);
	//消息单发(S->C)
	virtual int Send(CMessage *message);
	//消息群发(S->C)
	virtual int Send(CMessage *message, vector<int> *socketIDs);
public:
	//不清楚
	virtual void OnWaitMessageHandle(CMessage *message);
	//添加监听者
	virtual void RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke);
	//不清楚
	virtual void RegisterWait(int requestID, CMessage *message);
	//消息分发(C->S)
	virtual void SendToListener(CMessage *message);
	//删除监听者
	virtual void UnRegisterListener(int requestID);
	//删除监听者中的监听者
	virtual void UnRegisterListener(int requestID, ListenerMessageCallBack callBack);
	//不清楚
	virtual void UnRegisterWait(int requestID);
	//不清楚
	virtual int WaitMessage(int requestID, int timeout);
};


#endif