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
	//构造函数
	TraderQueryService();
	//析构函数
	~TraderQueryService();
public:
	//查询所有委托
	void QueryAllOrders(CMessage* msg);
	//查询所有挂单
	void QueryAllOpenOrders(CMessage* msg);
	//查询所有成交
	void QueryAllTrades(CMessage* msg);
	//查询所有提现记录
	void QueryAllWithdrawals(CMessage* msg);
	//查询所有币种资金
	void QueryAllPositions(CMessage* msg);
	//查询单个币种充值地址
	void QueryCoinAddr(CMessage* msg);
	//查询mysql数据库的数据
	void QueryMysqlData();
};
#endif