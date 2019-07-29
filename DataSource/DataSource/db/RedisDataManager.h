#pragma once
#ifndef __RedisDataManager_H__
#define __RedisDataManager_H__

#include "..\\stdafx.h"
#include "..\\redis\\RedisHelper.h"
#include "..\\bean\\CBean.h"

#define	ORDERINFOS_HASHNAME			1
#define OPENORDERS_HASHNAME			2
#define CANCELORDERS_HASHNAME		3
#define TRADERRECORDS_HASHNAME		4
#define TRADERPOSITIONS_HASHNAME	5
#define WITHDRAWALRECORDS_HASHNAME	6
#define DEPOSITADDR_HASHNAME		7

class RedisDataManager
{
public:
	//redis内存储的所有的traderID的表名
	string m_HashTableNameOfTraderIDs;
	//日志根目录
	String m_parentDir;
	//数据库操作日志
	String m_dbExceptionFilePath;
	//数据库ip地址
	String m_dbServiceIP;
	//数据库port
	int m_dbServicePort;
	//数据库操作对象
	RedisHelper *m_redisClient;
	//数据库状态码
	int m_redisState;
public:
	RedisDataManager(RedisHelper *redisHelper);
	~RedisDataManager();
public:
	string getTraderHashTableName(String traderID, int select);
public:
	//将所有的订单数据保存到Redis
	bool SaveOrderInfosToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap);
	//将所有的挂单数据保存到Redis
	bool SaveOpenOdersToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap);
	//将所有的撤单数据保存到Redis
	bool SaveCancelOrdersToRedis(String traderID, map<String, CancelOrder*> &cancelOrderMap);
	//将所有的成交订单保存到Redis
	bool SaveTradeRecordsToRedis(String traderID, map<String, TradeRecord*> &tradeRecordMap);
	//将所有的用户资金数据保存到redis
	bool SaveTraderPositionsToRedis(TraderPosition *positons);
	//将所有的提现申请数据保存到Redis
	bool SaveWithdrawalRecordsToRedis(String traderID,  map<String, WithdrawalApply*> &withdrawalApplyMap);
	//将所有币种的充值地址数据保存到Redis
	bool SaveDepositAddrsToRedis(String traderID, map<String,Address*> &coinAddrs);
public:
	//将单条订单数据保存到Redis中
	bool InsertOrderInfoToRedis(String traderID, OrderInfo *orderInfo);
	//将单条挂单数据保存到Redis
	bool InsertOpenOrderToRedis(String traderID, OrderInfo *orderInfo);
	//将单条撤单数据保存到Redis
	bool InsertCancelOrderToRedis(String traderID, CancelOrder *cancelOrder);
	//将单条成交订单保存到Redis
	bool InsertTradeRecordToRedis(String traderID, TradeRecord *tradeRecord);
	//将单条提现申请保存到Redis
	bool InsertWithdrawalRecordToRedis(String traderID, WithdrawalApply *withdrawalApply);
	//将某个币种的充值地址保存至Redis
	bool InsertDepositAddrToRedis(String traderID, Address *address);
	//将某个币种的资金数据保存至Redis
	bool InsertPositionToRedis(String traderID, Position *position);
public:
	void CheckEnvironment();
	//打印日志
	void printLog(const String& path, const String& content);
	//向数据库插入已有委托的最新数据
	void AddUpdateOrderInfo(OrderInfo *orderInfo);
};
#endif