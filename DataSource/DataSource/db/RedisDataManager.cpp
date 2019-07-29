#include "..\\api\\CStr.h"
#include "RedisDataManager.h"
#include "..\\global\\DataCenter.h"
#include "..\\api\\CFile.h"
#include "..\\api\\PublicMethod.h"


RedisDataManager::RedisDataManager(RedisHelper *redisHelper)
{
	//��ʼ��redis���ӽ�
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

//�������ݿ�ί��
void RedisDataManager::AddUpdateOrderInfo(OrderInfo *orderInfo)
{
	if(!m_redisState)
	{
		return;
	}
	string orderContent = orderInfo->toString();
	string traderID;
	string orderID;
	//�û��������ݹ�ϣ������
	string hashName = getTraderHashTableName(orderInfo->m_traderID,ORDERINFOS_HASHNAME);
	CStrA::wstringTostring(traderID, orderInfo->m_traderID);
	CStrA::wstringTostring(orderID, orderInfo->m_orderID);
	m_redisClient->SetHashString(hashName.c_str(), orderID.c_str(), orderContent.c_str());
}


//������ݿ�����״̬����־�ļ�
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
	//��ȡ�����ļ�����
	IPStruct ipStruct;
	ipStruct.m_ip = m_dbServiceIP;
	ipStruct.m_port = m_dbServicePort;
	DataCenter::GetIPConfig()->GetIPPort(L"RedisDataManager", &ipStruct);
	string dbip;
	CStrA::wstringTostring(dbip, m_dbServiceIP);
	m_redisState = m_redisClient->Init(dbip.c_str(), m_dbServicePort, 0);
	//��ӡ��־
	if(m_redisState)
	{
		wchar_t buff[1024] = {0};
		String time = PublicMethod::getCurrentTime();
		swprintf_s(buff, 1023, L"[���ݿ���־]ʱ��:%s,IP:%s,Port:%d,����:redis���ݿ����ӳɹ�!\n", 
			time.c_str(), m_dbServiceIP.c_str(), m_dbServicePort);
		printLog(m_dbExceptionFilePath, buff);
	}
	else
	{
		wchar_t buff[1024] = {0};
		String time = PublicMethod::getCurrentTime();
		swprintf_s(buff, 1023, L"[���ݿ���־]ʱ��:%s,IP:%s,Port:%d,����:redis���ݿ�����ʧ��!\n",
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

//�������������ݱ��浽Redis��
bool RedisDataManager::InsertOrderInfoToRedis(String traderID, OrderInfo *orderInfo)
{
	//�û��������ݹ�ϣ������
	string hashName = getTraderHashTableName(traderID,ORDERINFOS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	//�������е�keyΪorderID
	string orderID;
	CStrA::wstringTostring(orderID,orderInfo->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),orderInfo->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//�������ҵ����ݱ��浽Redis
bool RedisDataManager::InsertOpenOrderToRedis(String traderID, OrderInfo *orderInfo)
{
	//��ȡ�û��ҵ���ϣ��keyֵ
	string hashName = getTraderHashTableName(traderID,OPENORDERS_HASHNAME);
	if(hashName == "")
	{
		return false;
	}
	//�������е�keyΪorderID
	string orderID;
	CStrA::wstringTostring(orderID,orderInfo->m_orderID); 
	int ret = m_redisClient->SetHashString(hashName.c_str(),orderID.c_str(),orderInfo->toString().c_str());
	bool result = (ret == 0 ? false : true);
	return result;
}

//�������������ݱ��浽Redis
bool RedisDataManager::InsertCancelOrderToRedis(String traderID, CancelOrder *cancelOrder)
{
	//��ȡ�û�������ϣ��keyֵ
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

//�������ɽ��������浽Redis
bool RedisDataManager::InsertTradeRecordToRedis(String traderID, TradeRecord *tradeRecord)
{
	//��ȡ�û��ɽ����ϣ��keyֵ
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

//�������������뱣�浽Redis
bool RedisDataManager::InsertWithdrawalRecordToRedis(String traderID, WithdrawalApply *withdrawalApply)
{
	//��ȡ�û����ּ�¼���ϣ��keyֵ
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

//��ĳ�����ֵĳ�ֵ��ַ������Redis
bool RedisDataManager::InsertDepositAddrToRedis(String traderID, Address *address)
{
	//�û������ֵ��ַ���ݵ�hash��keyֵ
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

//��ĳ�����ֵ��ʽ����ݱ�����Redis
bool RedisDataManager::InsertPositionToRedis(String traderID, Position *position)
{
	//�û������ʽ����ݵ�hash��keyֵ
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

//�����еĶ������ݱ��浽Redis
bool RedisDataManager::SaveOrderInfosToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	map<String, OrderInfo*>::iterator it = orderInfoMap.begin();
	bool ret;
	for(;it != orderInfoMap.end(); it++)
	{
		ret = InsertOrderInfoToRedis(traderID,it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ���붩�� %S ʧ��",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//�����еĹҵ����ݱ��浽Redis
bool RedisDataManager::SaveOpenOdersToRedis(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	map<String, OrderInfo*>::iterator it = orderInfoMap.begin();
	bool ret;
	for(;it != orderInfoMap.end(); it++)
	{
		ret = InsertOpenOrderToRedis(traderID,it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ����ҵ� %S ����ʧ��",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//�����еĳ������ݱ��浽Redis
bool RedisDataManager::SaveCancelOrdersToRedis(String traderID, map<String, CancelOrder*> &cancelOrderMap)
{
	map<String, CancelOrder*>::iterator it = cancelOrderMap.begin();
	bool ret;
	for(; it != cancelOrderMap.end(); it++)
	{
		ret = InsertCancelOrderToRedis(traderID, it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ���볷�� %S ����ʧ��",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//�����еĳɽ��������浽Redis
bool RedisDataManager::SaveTradeRecordsToRedis(String traderID, map<String, TradeRecord*> &tradeRecordMap)
{
	map<String, TradeRecord*>::iterator it = tradeRecordMap.begin();
	bool ret;
	for(; it != tradeRecordMap.end(); it++)
	{
		ret = InsertTradeRecordToRedis(traderID, it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ����ɽ����� %S ����ʧ��",traderID.c_str(),it->second->m_orderID.c_str());
		}
	}
	return true;
}

//�����е��û��ʽ����ݱ��浽redis
bool RedisDataManager::SaveTraderPositionsToRedis(TraderPosition *positons)
{
	vector<Position*>::iterator it = positons->m_traderPosition.begin();
	bool ret;
	for(;it != positons->m_traderPosition.end(); ++it)
	{
		ret = InsertPositionToRedis(positons->m_traderID,(*it));
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ������� %S �ʽ�����ʧ��",positons->m_traderID.c_str(),(*it)->m_code.c_str());
		}
	}
	return true;
}

//�����е������������ݱ��浽Redis
bool RedisDataManager::SaveWithdrawalRecordsToRedis(String traderID,  map<String, WithdrawalApply*> &withdrawalApplyMap)
{
	map<String, WithdrawalApply*>::iterator it = withdrawalApplyMap.begin();
	bool ret;
	for(;it != withdrawalApplyMap.end(); it++)
	{
		ret = InsertWithdrawalRecordToRedis(traderID,it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : �������ּ�¼ %S ����ʧ��",traderID.c_str(),it->second->m_withdrawalID.c_str());
		}
	}
	return true;
}

//�����б��ֵĳ�ֵ��ַ���ݱ��浽Redis
bool RedisDataManager::SaveDepositAddrsToRedis(String traderID, map<String,Address*> &coinAddrs)
{
	map<String,Address*>::iterator it = coinAddrs.begin();
	bool ret;
	for(;it != coinAddrs.end(); it++)
	{
		ret = InsertDepositAddrToRedis(traderID, it->second);
		if(!ret)
		{
			//���ĳ�����ݲ���ʧ�ܣ���ʱ��ӡ��־����
			//�ݴ���
			//TODO
			printf("%S : ������� %S ��ֵ��ַ����ʧ��",traderID.c_str(),it->second->m_coinCode.c_str());
		}
	}
	return true;
}

void RedisDataManager::printLog(const String& path, const String& content)
{
	CFileA::Append(path, content);
}