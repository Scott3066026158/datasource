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
	//���յ�������(��λbyte)
	static _int64 m_downFlow;
	//���͵�������(��λbyte)
    static _int64 m_upFlow;
	//���պ���ָ��
	static MessageCallBack m_messageCallBack;
	//����״̬����ָ��
	static WriteLogCallBack m_writeLogCallBack;
public://�ײ㺯��Handler
	static int CloseClient(int socketID);
	static int ConnectToServer(int type, int proxyType, const char *ip, int port, const char *proxyIp, int proxyPort, const char *proxyUserName, const char *proxyUserPwd, const char *proxyDomain, int timeout);
	static int ConnectToServer(const wchar_t *ip, int port);
	static void RegisterCallBack(MessageCallBack callBack);
	static void RegisterLog(WriteLogCallBack callBack);
	static int SendByClient(int socketID, const char *str, int len);
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
	static void AddService(ClientBaseService *service);
	//��ȡ���з���
	static void GetServices(vector<ClientBaseService*> *services);
public:
	//��ȡ�������ִ���ļ�·��
	static string GetProgramDir();
	//��ȡһ��int����(��Ϊ��,������)
	static int GetRequestID();
private:
	//MessageListener��
	CLock m_lock;
	//�����߼���
	map<int, MessageListener*> m_listeners;
	map<int, CMessage*> m_waitMessages;
private:
	//Serviceѹ������
	int m_compressType;
	//Service��ID
	int m_groupID;
	//Service����ID
	int m_serviceID;
	//Service��ռ��SessionID
	int m_sessionID;
	//������ͨ�ŵ�SocketID
	int m_socketID;
	//Service����
	String m_serviceName;
public://���������������
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
	//��ָ�����ӷ���һ������
	int KeepAlive(int socketID);
	//���ݽ��ջص�
	virtual void OnCallBack(Binary *binary, int socketID, int localSID, int len);
	//���ӶϿ��ص�
	virtual void OnClientClose(int socketID, int localSID);
	//���ӳɹ��ص�
	virtual void OnClientConnect(int socketID, int localSID);
	//��Ϣ����(һ�㱻��д)
	virtual void OnReceive(CMessage *message);
	//�����˷�����Ϣ
	int SendToServer(CMessage *message);
	//��Ϣ�ַ�(C->S)
	void SendToListener(CMessage *message);
public:
	//�����
	virtual void OnWaitMessageHandle(CMessage *message);
	//��Ӽ�����
	void RegisterListener(int requestID, ListenerMessageCallBack callBack, void *pInvoke);
	//�����
	void RegisterWait(int requestID, CMessage *message);
	//ɾ��������
	void UnRegisterListener(int requestID);
	//ɾ���������еļ�����
	void UnRegisterListener(int requestID, ListenerMessageCallBack callBack);
	//�����
	void UnRegisterWait(int requestID);
	//�����
	int WaitMessage(int requestID, int timeout);
};

#endif