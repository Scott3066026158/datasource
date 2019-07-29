#include "..\\api\\CStr.h"
#include "RedisDataManager.h"
#include "..\\global\\DataCenter.h"
#include "..\\api\\CFile.h"
#include "..\\api\\PublicMethod.h"


RedisDataManager::RedisDataManager(RedisHelper *redisHelper)
{
	//初始化redis连接接
	//TODO
	m_HashTableNameOfTraderIDs = "traderIDs";
	m_parentDir = DataCenter::m_logPath + L"\\DBLog\\";
	m_dbExceptionFilePath = m_parentDir + L"dbException.txt";
    m_dbServiceIP = L"127.0.0.1";
	m_dbServicePort = 6379;
	m_redisClient = redisHelper;
	CheckEnvironment();
	//m_redisClient.init();
}

RedisDataManager::~RedisDataManager()
{
	delete m_redisClient;
}

//更新数据库委托
void RedisDataManager::AddUpdateOrderInfo(OrderInfo *orderInfo)
{
	if(!m_redisState)
	{
		return;
	}
	string orderContent = orderInfo->toString();
	string traderID;
	string orderID;
	//用户订单数据哈希表名称
	string hashName = getTraderHashTableName(orderInfo->m_traderID,ORDERINFOS_HASHNAME);
	CStrA::wstringTostring(traderID, orderInfo->m_traderID);
	CStrA::wstringTostring(orderID, orderInfo->m_orderID);
	m_redisClient->SetHashString(hashName.c_str(), orderID.c_str(), orderContent.c_str());
}


//检查数据库连接状态和日志文件
void RedisDataManager::CheckEnvironment()
{
	if(!CFileA::IsDirectoryExist(m_parentDir))
	{
		CFileA::CreateDirectoryW(m_parentDir);
	}
	if(!CFileA::IsFileExist(m_dbExceptionFilePath))
	{
		CFileA::Write(m_dbExceptionFilePath, L"");
	}
	//获取配置文件内容
	IPStruct ipStruct;
	ipStruct.m_ip = m_dbServiceIP;
	ipStruct.m_port = m_dbServicePort;
	DataCenter::GetIPConfig()->GetIPPort(L"RedisDataManager", &ipStruct);
	string dbip;
	CStrA::wstringTostring(dbip, m_dbServiceIP);
	m_redisState = m_redisClient->Init(dbip.c_str(), m_dbServicePort, 0);
	//打印日志
	if(m_redisState)
	{
		wchar_t buff[1024] = {0};
		String time = PublicMethod::getCurrentTime();
		swprintf_s(buff, 1023, L"[数据库日志]时间:%s,IP:%s,Port:%d,描述:redis数据库连接成功!\n", 
			time.c_str(), m_dbServiceIP.c_str(), m_dbServicePort);
		printLog(m_dbExceptionFilePath, buff);
	}
	else
	{
		wchar_t buff[1024] = {0};
		String time = PublicMethod::getCurrentTime();
		swprintf_s(buff, 1023, L"[数据库日志]时间:%s,IP:%s,Port:%d,描述:redis数据库连接失败!\n",
			time.c_str(), m_dbServiceIP.c_str(), m_dbServicePort);
		printLog(m_dbExceptionFilePath, buff);
	}
}

string RedisDataManager::getTraderHashTableName(String traderID, int select)
{
	char hash_name[128];
	switch(select)
	{
		case ORDERINFOS_HASHNAME:
			sprintf(hash_name,"%S::orderInfos",traderID.c_str());
			break;
		case OPENORDERS_HASHNAME:
			sprintf(hash_name,"%S::openOrders",traderID.c_str());
			break;
		case CANCELORDERS_HASHNAME:
			sprintf(hash_name,"%S::cancelOrders",traderID.c_str());
			break;
		case TRADERRECORDS_HASHNAME:
			sprintf(hash_name,"%S::tradeRecords",traderID.c_str());
			break;
		case TRADERPOSITIONS_HASHNAME:
			sprintf(hash_name,"%S::traderPositions",traderID.c_str());
			break;
		case WITHDRAWALRECORDS_HASHNAME:
			sprintf(hash_name,"%S::withdrawalRecords",traderID.c_str());
			break;
		case DEPOSITADDR_HASHNAME:
			sprintf(hash_name,"%S::depositAddrs",traderID.c_str());
			break;
		default:
			return "";
	}
	return hash_name;
}

//将单条订单数据保存到Redis中
bool RedisDataManager::InsertOrderInfoToRedis(String traderID, OrderInfo *orderInfo)
{
	//用户订单数据哈希表名称
	string hashName = getTraderHashTableName(traderID,ORDERINFOS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	//订单表中的key为orderID
	string orderID;
	CStrA::wstringTostring(orderID,orderInfo->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),orderInfo->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将单条挂单数据保存到Redis
bool RedisDataManager::InsertOpenOrderToRedis(String traderID, OrderInfo *orderInfo)
{
	//获取用户挂单哈希表key值
	string hashName = getTraderHashTableName(traderID,OPENORDERS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	//订单表中的key为orderID
	string orderID;
	CStrA::wstringTostring(orderID,orderInfo->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),orderInfo->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将单条撤单数据保存到Redis
bool RedisDataManager::InsertCancelOrderToRedis(String traderID, CancelOrder *cancelOrder)
{
	//获取用户撤单哈希表key值
	string hashName = getTraderHashTableName(traderID,CANCELORDERS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	string orderID;
	CStrA::wstringTostring(orderID,cancelOrder->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),cancelOrder->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将单条成交订单保存到Redis
bool RedisDataManager::InsertTradeRecordToRedis(String traderID, TradeRecord *tradeRecord)
{
	//获取用户成交表哈希表key值
	string hashName = getTraderHashTableName(traderID,TRADERRECORDS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	string orderID;
	CStrA::wstringTostring(orderID,tradeRecord->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),tradeRecord->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将单条提现申请保存到Redis
bool RedisDataManager::InsertWithdrawalRecordToRedis(String traderID, WithdrawalApply *withdrawalApply)
{
	//获取用户提现记录表哈希表key值
	string hashName = getTraderHashTableName(traderID,WITHDRAWALRECORDS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	string withdrawalID;
	CStrA::wstringTostring(withdrawalID,withdrawalApply->m_withdrawalID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),withdrawalID.c_str(),withdrawalApply->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将某个币种的充值地址保存至Redis
bool RedisDataManager::InsertDepositAddrToRedis(String traderID, Address *address)
{
	//用户储存充值地址数据的hash表key值
	string hashName = getTraderHashTableName(traderID,DEPOSITADDR_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	string coinCode;
	CStrA::wstringTostring(coinCode,address->m_coinCode); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),coinCode.c_str(),address->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将某个币种的资金数据保存至Redis
bool RedisDataManager::InsertPositionToRedis(String traderID, Position *position)
{
	//用户储存资金数据的hash表key值
	string hashName = getTraderHashTableName(traderID, TRADERPOSITIONS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	string code;
	CStrA::wstringTostring(code,position->m_code); 
	int ret = m_redisClient->SetHashString(hashName.c_str(), code.c_str(), position->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//将所有的订单数据保存到Redis
bool RedisDataManager::SaveOrderInfosToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	map<String, OrderInfo*>::iterator it = orderInfoMap.begin();
	bool ret;
	for(;it != orderInfoMap.end(); it++)
	{
		ret = InsertOrderInfoToRedis(traderID,it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入订单 %S 失败",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//将所有的挂单数据保存到Redis
bool RedisDataManager::SaveOpenOdersToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	map<String, OrderInfo*>::iterator it = orderInfoMap.begin();
	bool ret;
	for(;it != orderInfoMap.end(); it++)
	{
		ret = InsertOpenOrderToRedis(traderID,it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入挂单 %S 数据失败",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//将所有的撤单数据保存到Redis
bool RedisDataManager::SaveCancelOrdersToRedis(String traderID, map<String, CancelOrder*> &cancelOrderMap)
{
	map<String, CancelOrder*>::iterator it = cancelOrderMap.begin();
	bool ret;
	for(; it != cancelOrderMap.end(); it++)
	{
		ret = InsertCancelOrderToRedis(traderID, it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入撤单 %S 数据失败",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//将所有的成交订单保存到Redis
bool RedisDataManager::SaveTradeRecordsToRedis(String traderID, map<String, TradeRecord*> &tradeRecordMap)
{
	map<String, TradeRecord*>::iterator it = tradeRecordMap.begin();
	bool ret;
	for(; it != tradeRecordMap.end(); it++)
	{
		ret = InsertTradeRecordToRedis(traderID, it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入成交订单 %S 数据失败",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//将所有的用户资金数据保存到redis
bool RedisDataManager::SaveTraderPositionsToRedis(TraderPosition *positons)
{
	vector<Position*>::iterator it = positons->m_traderPosition.begin();
	bool ret;
	for(;it != positons->m_traderPosition.end(); ++it)
	{
		ret = InsertPositionToRedis(positons->m_traderID,(*it));
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入币种 %S 资金数据失败",positons->m_traderID.c_str(),(*it)->m_code.c_str());
		}
	}
	return true;
}

//将所有的提现申请数据保存到Redis
bool RedisDataManager::SaveWithdrawalRecordsToRedis(String traderID,  map<String, WithdrawalApply*> &withdrawalApplyMap)
{
	map<String, WithdrawalApply*>::iterator it = withdrawalApplyMap.begin();
	bool ret;
	for(;it != withdrawalApplyMap.end(); it++)
	{
		ret = InsertWithdrawalRecordToRedis(traderID,it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入提现记录 %S 数据失败",traderID.c_str(),it->second->m_withdrawalID.c_str());
		}
	}
	return true;
}

//将所有币种的充值地址数据保存到Redis
bool RedisDataManager::SaveDepositAddrsToRedis(String traderID, map<String,Address*> &coinAddrs)
{
	map<String,Address*>::iterator it = coinAddrs.begin();
	bool ret;
	for(;it != coinAddrs.end(); it++)
	{
		ret = InsertDepositAddrToRedis(traderID, it->second);
		if(!ret)
		{
			//如果某条数据插入失败，暂时打印日志处理
			//容错处理
			//TODO
			printf("%S : 插入币种 %S 充值地址数据失败",traderID.c_str(),it->second->m_coinCode.c_str());
		}
	}
	return true;
}

void RedisDataManager::printLog(const String& path, const String& content)
{
	CFileA::Append(path, content);
}