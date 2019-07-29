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

//Messageѹ����־ 0��ѹ�� 1ѹ��
#define  COMPRESSTYPE_NONE			  0
#define  COMPRESSTYPE_GZIP			  1

//���ն˸���
class BaseService
{
public:
	//���пͻ���IP��ַ
	static map<int, String> m_allIPs;
	//IP������
	static CLock m_allIPsLock;
private:
	//���յ�������(��λbyte)
	static _int64 m_downFlow;
	//���͵�������(��λbyte)
	static _int64 m_upFlow;
	//���պ���ָ��
	static MessageCallBack m_messageCallBack;
	//����״̬����ָ��
	static WriteLogCallBack m_writeLogCallBack;
public://�ײ㺯��Handler
	static int CloseServerClient(int localSID, int socketID);
	static int CloseServer(int socketID);
	static void RegisterCallBack(MessageCallBack callBack);
	static void RegisterLog(WriteLogCallBack callBack);
	static int SendByServer(int socketID, const char *str, int len);
	static int StartServer(int type, int port);
public://�����ϴ��������ϴ�����
	static _int64 GetDownFlow();
	static void SetDownFlow(_int64 downFlow);
	static _int64 GetUpFlow();
	static void SetUpFlow(_int64 upFlow);
public:
	//Ĭ�����ݽ��ջص�����
	static void __stdcall CallBack(int socketID, int localSID, const char *str, int len);
	//Ĭ������״̬�ص�����
	static void __stdcall WriteServerLog(int socketID, int localSID, int state, const char *log);
public:
	//���һ������(��һ�����Ĭ�Ͽ���CallBack������Ϊ���սӿ�)
	static void AddService(BaseService *service);
	//ɾ��һ������
	static void DeleteService(BaseService *service);
	//��ȡ���з���
	static void GetServices(vector<BaseService*> *services);
public:
	//��ȡ�������ִ���ļ�·��
	static string GetProgramDir();
	//��ȡһ��int����(��Ϊ��,������)
	static int GetRequestID();
protected:
	//�������ӵ�����ѹ�����
	map<int, int> m_compressTypes;
	//�����߼���
	map<int, MessageListener*> m_listeners;
	//MessageListener��
	CLock m_lock;
	//�����
	map<int, CMessage*> m_waitMessages;
protected:
	//Serviceѹ������
	int m_compressType;
	//Service��ID
	int m_groupID;
	//Service����ID
	int m_serviceID;
	//Service��ռ��SessionID
	int m_sessionID;
	//Service��ռ��SocketID
	int m_socketID;
	//Service����
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
	//��ָ�����ӷ���һ������
	virtual int KeepAlive(int socketID);
	//���ݽ��ջص�
	virtual void OnCallBack(Binary *binary, int socketID, int localSID, int len);
	//���ӶϿ��ص�
	virtual void OnClientClose(int socketID, int localSID);
	//���ӳɹ��ص�
	virtual void OnClientConnect(int socketID, int localSID);
	//��Ϣ����(һ�㱻��д)
	virtual void OnReceive(CMessage *message);
	//��Ϣ����(S->C)
	virtual int Send(CMessage *message);
	//��ϢȺ��(S->C)
	virtual int Send(CMessage *message, vector<int> *socketIDs);
public:
	//�����
	virtual void OnWaitMessageHandle(CMessage *message);
	//��Ӽ�����
	virtual void RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke);
	//�����
	virtual void RegisterWait(int requestID, CMessage *message);
	//��Ϣ�ַ�(C->S)
	virtual void SendToListener(CMessage *message);
	//ɾ��������
	virtual void UnRegisterListener(int requestID);
	//ɾ���������еļ�����
	virtual void UnRegisterListener(int requestID, ListenerMessageCallBack callBack);
	//�����
	virtual void UnRegisterWait(int requestID);
	//�����
	virtual int WaitMessage(int requestID, int timeout);
};


#endif