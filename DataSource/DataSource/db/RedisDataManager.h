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
	//redis�ڴ洢�����е�traderID�ı���
	string m_HashTableNameOfTraderIDs;
	//��־��Ŀ¼
	String m_parentDir;
	//���ݿ������־
	String m_dbExceptionFilePath;
	//���ݿ�ip��ַ
	String m_dbServiceIP;
	//���ݿ�port
	int m_dbServicePort;
	//���ݿ��������
	RedisHelper *m_redisClient;
	//���ݿ�״̬��
	int m_redisState;
public:
	RedisDataManager(RedisHelper *redisHelper);
	~RedisDataManager();
public:
	string getTraderHashTableName(String traderID, int select);
public:
	//�����еĶ������ݱ��浽Redis
	bool SaveOrderInfosToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap);
	//�����еĹҵ����ݱ��浽Redis
	bool SaveOpenOdersToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap);
	//�����еĳ������ݱ��浽Redis
	bool SaveCancelOrdersToRedis(String traderID, map<String, CancelOrder*> &cancelOrderMap);
	//�����еĳɽ��������浽Redis
	bool SaveTradeRecordsToRedis(String traderID, map<String, TradeRecord*> &tradeRecordMap);
	//�����е��û��ʽ����ݱ��浽redis
	bool SaveTraderPositionsToRedis(TraderPosition *positons);
	//�����е������������ݱ��浽Redis
	bool SaveWithdrawalRecordsToRedis(String traderID,  map<String, WithdrawalApply*> &withdrawalApplyMap);
	//�����б��ֵĳ�ֵ��ַ���ݱ��浽Redis
	bool SaveDepositAddrsToRedis(String traderID, map<String,Address*> &coinAddrs);
public:
	//�������������ݱ��浽Redis��
	bool InsertOrderInfoToRedis(String traderID, OrderInfo *orderInfo);
	//�������ҵ����ݱ��浽Redis
	bool InsertOpenOrderToRedis(String traderID, OrderInfo *orderInfo);
	//�������������ݱ��浽Redis
	bool InsertCancelOrderToRedis(String traderID, CancelOrder *cancelOrder);
	//�������ɽ��������浽Redis
	bool InsertTradeRecordToRedis(String traderID, TradeRecord *tradeRecord);
	//�������������뱣�浽Redis
	bool InsertWithdrawalRecordToRedis(String traderID, WithdrawalApply *withdrawalApply);
	//��ĳ�����ֵĳ�ֵ��ַ������Redis
	bool InsertDepositAddrToRedis(String traderID, Address *address);
	//��ĳ�����ֵ��ʽ����ݱ�����Redis
	bool InsertPositionToRedis(String traderID, Position *position);
public:
	void CheckEnvironment();
	//��ӡ��־
	void printLog(const String& path, const String& content);
	//�����ݿ��������ί�е���������
	void AddUpdateOrderInfo(OrderInfo *orderInfo);
};
#endif