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
	//资金变化通知锁(HTTP)
	CLock m_balanceNoticeLock;
	//资金变化通知(HTTP)
	vector<BalanceNoticeRecord*> m_balanceNoticeList;

	//委托下单锁(HTTP)
	CLock m_orderInfoLock;
	//委托下单(HTTP)
	vector<OrderInfo*> m_orderInfoList;
public:
	// 构造函数
	TraderUpdateService();
	// 析构函数
	~TraderUpdateService();
public:
	//委托回报
	int InsertOrder(CMessage* msg);
	//撤单回报
	int InsertCancel(CMessage* msg);
	//资金回报
	int InsertPosition(CMessage* msg);
	//地址回报
	int InsertAddr(CMessage* msg);
	//提现申请回报
	int InsertWithdrawalApply(CMessage* msg);
	//成交回报
	int InsertTrade(CMessage* msg);
	//用户资金变化回报
	int UpdateTraderFund(CMessage* msg);

};
#endif