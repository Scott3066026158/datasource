#pragma once
#ifndef __DataCenter_H__
#define __DataCenter_H__

#include "..\\config\\IPConfig.h"
#include "..\\servers\\ConnectProxy.h"
#include "..\\middle\\Router.h"
#include "..\\middle\\HttpRouter.h"
#include "..\\bean\\TraderBaseInfo.h"
#include "..\\service\\TraderUpdateService.h"
#include "..\\service\\TraderQueryService.h"
#include "TraderDataManager.h"
#include "..\\db\\RedisDataManager.h"
#include "..\\db\\MysqlHelper.h"
#include "..\\rabbitmq\\RabbitmqProducter.h"
#include "..\\owsock\\HttpGetService.h"
#include "..\\owsock\\HttpPostService.h"

using namespace OwLibCT;


class DataCenter
{
public:
	// ���ӿ��ƶ���
	static ConnectProxy* m_connectProxy;
	// ·�ɿ��ƶ���
	static Router* m_router;
	// HTTP·�ɿ��ƶ���
	static HttpRouter* m_httpRouter;
	//�����ѯ�������
	static TraderQueryService* m_traderQueryService;
	//������������������
	static TraderUpdateService* m_traderUpdateService;
	//�û����ݹ������
	static TraderDataManager* m_traderDataManager;
	//�������ݿ����
	static RedisDataManager* m_redisDataManager;
	//
	static RedisHelper* m_redisHelper;
	//IP�����ļ���������
	static IPConfig *m_ipConfig;
	//��־�ļ���·��
	static String m_logPath;
	//����mysql����
	static MysqlHelper* m_mysqlHelper;
	//����Rabbitmq����
	static RabbitmqProducter* m_rabbitmqProducter;
private:
	//HttpGet�������
	static HttpGetService* m_httpGetService;
	//HttpPost�������
	static HttpPostService* m_httpPostService;

public:
	DataCenter();
	~DataCenter();
public:
	//��ʼ����������� 0:ʧ�� 1:�ɹ�
	static int StartService();
	//��ȡ����������·��
	static string GetAppPath();
	//��ȡ����������·��
	static String GetAppPathW();

	static Router* GetRouter();
	//��ȡ���ӿ�����
	static ConnectProxy* GetConnectProxy();
	//��ȡ��ѯ����
	static TraderQueryService* GetTraderQueryService();
	//��ȡ�������
	static TraderUpdateService* GetTraderUpdateService();
	//��ȡ�û����ݹ������
	static TraderDataManager* GetTraderDataManager();
	//��ȡ�������ݿ�
	static RedisDataManager* GetRedisDataManager();
	//��ȡ���ݿ������
	static RedisHelper* GetRedisHelper();
	//��ȡIPConfig
	static IPConfig* GetIPConfig();
	//��ȡmysql���ݿ����Ӷ���
	static MysqlHelper* GetMysqlHelper();
	//��ȡrabbitmq���Ӷ���
	static RabbitmqProducter* GetRabbitmqProducter();
	//��ȡHttpGet�������
	static HttpGetService* GetHttpGetService();
	//��ȡHttpPost�������
	static HttpPostService* GetHttpPostService();
};
#endif