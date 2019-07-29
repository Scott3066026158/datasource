#pragma once
#ifndef __TraderQueryService_H__
#define __TraderQueryService_H__

#include "..\\owsock\\CMessage.h"
#include "..\\global\\TraderDataManager.h"
#include "..\\servers\\ConnectProxy.h"

class TraderQueryService
{
public:
	TraderDataManager *m_traderDataManager;
	ConnectProxy *m_connectProxy;
public:
	//���캯��
	TraderQueryService();
	//��������
	~TraderQueryService();
public:
	//��ѯ����ί��
	void QueryAllOrders(CMessage* msg);
	//��ѯ���йҵ�
	void QueryAllOpenOrders(CMessage* msg);
	//��ѯ���гɽ�
	void QueryAllTrades(CMessage* msg);
	//��ѯ�������ּ�¼
	void QueryAllWithdrawals(CMessage* msg);
	//��ѯ���б����ʽ�
	void QueryAllPositions(CMessage* msg);
	//��ѯ�������ֳ�ֵ��ַ
	void QueryCoinAddr(CMessage* msg);
	//��ѯmysql���ݿ������
	void QueryMysqlData();
};
#endif