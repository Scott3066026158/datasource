#pragma once
#ifndef __TraderUpdateService_H__
#define __TraderUpdateService_H__

#include "..\\owsock\\CMessage.h"
#include "..\\global\\TraderDataManager.h"
#include "..\\rabbitmq\\RabbitmqProducter.h"
//#include "..\\rabbitmq\\RabbitmqCustomer.h"

class TraderUpdateService
{
private:
	TraderDataManager *m_traderDataManager;
public:
	//�ʽ�仯֪ͨ��(HTTP)
	CLock m_balanceNoticeLock;
	//�ʽ�仯֪ͨ(HTTP)
	vector<BalanceNoticeRecord*> m_balanceNoticeList;

	//ί���µ���(HTTP)
	CLock m_orderInfoLock;
	//ί���µ�(HTTP)
	vector<OrderInfo*> m_orderInfoList;
public:
	// ���캯��
	TraderUpdateService();
	// ��������
	~TraderUpdateService();
public:
	//ί�лر�
	int InsertOrder(CMessage* msg);
	//�����ر�
	int InsertCancel(CMessage* msg);
	//�ʽ�ر�
	int InsertPosition(CMessage* msg);
	//��ַ�ر�
	int InsertAddr(CMessage* msg);
	//��������ر�
	int InsertWithdrawalApply(CMessage* msg);
	//�ɽ��ر�
	int InsertTrade(CMessage* msg);
	//�û��ʽ�仯�ر�
	int UpdateTraderFund(CMessage* msg);

};
#endif