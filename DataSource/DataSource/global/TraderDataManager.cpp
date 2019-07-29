#include "..\\stdafx.h"
#include "..\\owsock\\Binary.h"
#include "..\\api\\PublicMethod.h"
#include "DataCenter.h"
#include "TraderDataManager.h"
#include "..\\bean\\CBean.h"
#include "..\\global\\BusinessIDs.h"
#include "..\\global\\Convert.h"
TraderDataManager::TraderDataManager()
{
	//初始化用户数据
}

TraderDataManager::~TraderDataManager(){}

//用户登录
void TraderDataManager::TraderLogin(CMessage* msg)
{
	Binary binary;
	binary.Write(msg->m_body, msg->m_bodyLength);
	String flag,traderID,password;
	binary.ReadString(flag);
	binary.ReadString(traderID);
	binary.ReadString(password);
	printf("用户%S登录\n",traderID.c_str());
	vector<string> orderInfos;
	//string hashOrderName = DataCenter::GetRedisDataManager()->getTraderHashTableName(traderID,ORDERINFOS_HASHNAME);
	RedisHelper* ss = DataCenter::m_redisHelper;
	//ss->GetHashTableValue(hashOrderName.c_str(),&orderInfos);
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		TraderBaseInfo *traderBaseInfo = new TraderBaseInfo;
		traderBaseInfo->m_traderID = traderID;
		TraderPosition *positions = new TraderPosition;
		positions->m_traderID = traderID;
		traderBaseInfo->m_Positions = positions;
		m_traderInfoMap.insert(make_pair(traderID, traderBaseInfo));
		//当用户不存在于DataSource中时,向Ginex请求此用户资金
		Binary binary;
		binary.WriteString(L"");
		binary.WriteString(traderID);
		//封装Message
		CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, API_TD_POSITION, 0, 0, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
		DataCenter::GetConnectProxy()->SendMsg(message);
		//获取所有历史委托数据
		/*if(ordersize > 0)
		{
			vector<vector<string>>::iterator it = rowcount.begin();
			for(it; it != rowcount.end(); ++it)
			{
				vector<string> order = *it;
				OrderInfo *ordersInfo = new OrderInfo();
				CStrA::stringTowstring(ordersInfo->m_flag,order[0]);
				CStrA::stringTowstring(ordersInfo->m_traderID,order[1]);
				ordersInfo->m_errorCode = atoi(order[2].c_str());
				CStrA::stringTowstring(ordersInfo->m_tradePair,order[3]);
				CStrA::stringTowstring(ordersInfo->m_orderID,order[4]);
				CStrA::stringTowstring(ordersInfo->m_targetFee,order[5]);
				ordersInfo->m_price = atof(order[6].c_str());
				ordersInfo->m_volume = atof(order[7].c_str());
				ordersInfo->m_orderFee = atof(order[8].c_str());
				ordersInfo->m_timestamp = atof(order[9].c_str());
				ordersInfo->m_isFeeTartget = atoi(order[10].c_str());
				ordersInfo->m_isDealFeeDemand = atoi(order[11].c_str());
				ordersInfo->m_orderWay = atoi(order[12].c_str());
				ordersInfo->m_dir = atoi(order[13].c_str());
				ordersInfo->m_tradedVolume = atof(order[14].c_str());
				ordersInfo->m_openedVolume = atof(order[15].c_str());
				ordersInfo->m_orderState = atoi(order[16].c_str());
				CStrA::stringTowstring(ordersInfo->m_orderStatus,order[17]);
				InsertTraderOrderInfo(ordersInfo);
			}
		}*/
	}
}

// 根据TraderID获取用户的所有数据
TraderBaseInfo* TraderDataManager::GetTraderData(String traderID)
{
	if(m_traderInfoMap.find(traderID) != m_traderInfoMap.end())
	{
		return m_traderInfoMap.find(traderID)->second;
	}
	else
	{
		return 0;
	}
}

// 根据TraderID获取用户的所有委托
void TraderDataManager::GetTraderAllOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		
		return;
	}	
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	traderBaseInfo->m_orderInfosLock.Lock();
	orderInfoMap = traderBaseInfo->m_orderInfosMap;
	traderBaseInfo->m_orderInfosLock.UnLock();
}

// 根据TraderID获取用户的所有持仓
TraderPosition* TraderDataManager::GetTraderPosition(String traderID)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return 0;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	traderBaseInfo->m_positionsLock.Lock();
	TraderPosition *position = traderBaseInfo->m_Positions;
	traderBaseInfo->m_positionsLock.UnLock();
	return position;
}


// 根据TraderID获取指定币种的持仓信息
Position* TraderDataManager::GetPositionByCode(String traderID, String coinCode)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return 0;
	}
	TraderBaseInfo* traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	
	traderBaseInfo->m_positionsLock.Lock();
	TraderPosition* traderPosition = traderBaseInfo->m_Positions;
	vector<Position*> positionList(traderPosition->m_traderPosition);
	traderBaseInfo->m_positionsLock.UnLock();
	for(vector<Position*>::iterator iter = positionList.begin(); iter != positionList.end(); iter++)
	{
		Position* position = *iter;
		if(position->m_code == coinCode)
		{
			return position;
		}
	}
	return 0;
}

// 根据TraderID获取用户的所有挂单
void TraderDataManager::GetTraderOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return;
	}	
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	orderInfoMap = traderBaseInfo->m_openOrdersMap;
}

// 根据TraderID获取用户的所有撤单
void TraderDataManager::GetTraderCancelOrder(String traderID, map<String, CancelOrder*> &cancelOrderMap)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return;
	}	
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	cancelOrderMap = traderBaseInfo->m_cancelOrdersMap;
}

// 根据TraderID获取用户的所有成交订单
void TraderDataManager::GetTradeRecord(String traderID, map<String, TradeRecord*> &tradeRecordMap)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return;
	}	
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	traderBaseInfo->m_tradeRecordsLock.Lock();
	tradeRecordMap = traderBaseInfo->m_tradeRecordsMap;
	traderBaseInfo->m_tradeRecordsLock.UnLock();
}

// 根据TraderID获取用户的所有提现申请列表
void TraderDataManager::GetWithdrawalApplyRecords(String traderID, map<String, WithdrawalApply*> &withdrawalApplyMap)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return;
	}	
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	traderBaseInfo->m_withdrawApplyLock.Lock();
	withdrawalApplyMap = traderBaseInfo->m_withdrawalApplyRecordsMap;
	traderBaseInfo->m_withdrawApplyLock.UnLock();
}

// 根据TraderID获取用户币种对应充值地址列表
Address* TraderDataManager::GetPositionAddress(String traderID, String coinCode)
{
	if(m_traderInfoMap.find(traderID) == m_traderInfoMap.end())
	{
		return 0;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderID)->second;
	map<String,Address*> addressMap = traderBaseInfo->m_coinAddr;
	
	return (addressMap.find(coinCode) == addressMap.end()) ? 0 : addressMap.find(coinCode)->second;
}

//根据OrderID查找委托回报对象
/*bool TraderDataManager::FindOrderInfoBySysID(LPDatas *lp, const String &traderID, const String &sysID, CoinOrder *order)
{
	bool flag = false;
	wchar_t key[1024] = {0};
	_stprintf_s(key, 1023, L"%s%s", traderID.c_str(), sysID.c_str());
	lp->m_orderInfosLock.Lock();
	map<String, CoinOrder*>::iterator sIter = lp->m_orderInfosMap.find(key);
	if(sIter != lp->m_orderInfosMap.end())
	{
		*order = *(sIter->second);
		flag = true;
	}
	lp->m_orderInfosLock.UnLock();
	return flag;
}*/


//插入用户订单数据
void TraderDataManager::InsertTraderOrderInfo(OrderInfo *orderInfo)
{
	if(m_traderInfoMap.find(orderInfo->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(orderInfo->m_traderID)->second;
	traderBaseInfo->m_orderInfosLock.Lock();
	traderBaseInfo->m_orderInfosMap[orderInfo->m_orderID] = orderInfo;
	traderBaseInfo->m_orderInfosLock.UnLock();
}

//插入用户撤单数据
void TraderDataManager::InsertTraderCancel(CancelOrder *cancelOrder)
{
	if(m_traderInfoMap.find(cancelOrder->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(cancelOrder->m_traderID)->second;
	traderBaseInfo->m_cancelOrdersLock.Lock();
	traderBaseInfo->m_cancelOrdersMap[cancelOrder->m_orderID] = cancelOrder;
	traderBaseInfo->m_cancelOrdersLock.UnLock();
}

//插入用户所有资金数据
void TraderDataManager::InsertTraderPosition(TraderPosition *traderPosition)
{
	if(m_traderInfoMap.find(traderPosition->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderPosition->m_traderID)->second;
	traderBaseInfo->m_positionsLock.Lock();
	delete traderBaseInfo->m_Positions;
	traderBaseInfo->m_Positions = 0;
	traderBaseInfo->m_Positions = traderPosition;
	traderBaseInfo->m_positionsLock.Lock();
}

//插入用户币种地址
void TraderDataManager::InsertTraderAddress(Address *address)
{
	if(m_traderInfoMap.find(address->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(address->m_traderID)->second;
	traderBaseInfo->m_coinAddrLock.Lock();
	traderBaseInfo->m_coinAddr[address->m_coinCode] = address;	
	traderBaseInfo->m_coinAddrLock.UnLock();
}	

//插入提现申请
void TraderDataManager::InsertTraderWithdrawalApply(WithdrawalApply *withdrawalApply)
{
	if(m_traderInfoMap.find(withdrawalApply->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(withdrawalApply->m_traderID)->second;
	traderBaseInfo->m_withdrawApplyLock.Lock();
	traderBaseInfo->m_withdrawalApplyRecordsMap[withdrawalApply->m_withdrawalID] = withdrawalApply;
	traderBaseInfo->m_withdrawApplyLock.UnLock();
}

//插入成交记录
void TraderDataManager::InsertTraderRecord(TradeRecord *tradeRecord)
{
	if(m_traderInfoMap.find(tradeRecord->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(tradeRecord->m_traderID)->second;
	traderBaseInfo->m_tradeRecordsLock.Lock();
	traderBaseInfo->m_tradeRecordsMap[tradeRecord->m_orderID] = tradeRecord;
	traderBaseInfo->m_tradeRecordsLock.UnLock();
}

//成交后更新相应的委托订单
void TraderDataManager::UpdateOrderInfo(TradeRecord *tradeRecord, int socketID)
{
	char buf[64] = {0};
	vector<vector<string>> rowcount;
	string hashOrderName = DataCenter::GetRedisDataManager()->getTraderHashTableName(tradeRecord->m_traderID,ORDERINFOS_HASHNAME);
	RedisHelper* ss = DataCenter::m_redisHelper;
	string orderInfos;
	string orderID;
	CStrA::wstringTostring(orderID,tradeRecord->m_orderID);
	ss->GetHashStringValue(hashOrderName.c_str(),orderID.c_str(),&orderInfos);
	OrderInfo *orderInfo = new OrderInfo;
	orderInfo->toObject(orderInfos);
	orderInfo->m_tradedVolume += tradeRecord->m_volume;
	orderInfo->m_openedVolume = orderInfo->m_volume - orderInfo->m_tradedVolume;
	if(PublicMethod::d_eq(orderInfo->m_tradedVolume,orderInfo->m_volume))
	{
		orderInfo->m_orderState = ORDERSTATUS_P5;
		orderInfo->m_orderStatus = PublicMethod::GetOrderStatus(orderInfo->m_orderState);
	}
	else if(orderInfo->m_volume > orderInfo->m_tradedVolume)
	{
		orderInfo->m_orderState = ORDERSTATUS_P4;
		orderInfo->m_orderStatus = PublicMethod::GetOrderStatus(orderInfo->m_orderState);
	}
	DataCenter::GetRabbitmqProducter()->send_to_rabbit_mq(orderInfo->getUpDateSqlString(orderInfo).c_str());
	DataCenter::GetRedisDataManager()->AddUpdateOrderInfo(orderInfo);
	SendMsgToClient(orderInfo, socketID);
	printf("datasource update success \n");
	delete orderInfo;
}

//撤单后更新相应的委托订单
void TraderDataManager::UpdateOrderInfo(CancelOrder *cancelOrder, int socketID)
{
	if(m_traderInfoMap.find(cancelOrder->m_traderID) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(cancelOrder->m_traderID)->second;
	if(traderBaseInfo->m_orderInfosMap.find(cancelOrder->m_orderID) == traderBaseInfo->m_orderInfosMap.end())
	{
		return;
	}
	OrderInfo *orderInfo = traderBaseInfo->m_orderInfosMap.find(cancelOrder->m_orderID)->second;
	if(cancelOrder->m_status == CANCEL_ORDER_FINISHED)
	{
		orderInfo->m_tradedVolume = orderInfo->m_volume;
		orderInfo->m_openedVolume = 0;
		orderInfo->m_orderState = ORDERSTATUS_P5;
		orderInfo->m_orderStatus = PublicMethod::GetOrderStatus(orderInfo->m_orderState);
	}
	switch(orderInfo->m_orderState)
	{
		case ORDERSTATUS_P1:
			orderInfo->m_orderState = ORDERSTATUS_P2;
			orderInfo->m_orderStatus = PublicMethod::GetOrderStatus(orderInfo->m_orderState);
			break;
		case ORDERSTATUS_P2:
			break;
		case ORDERSTATUS_P3:
			break;
		case ORDERSTATUS_P4:
			orderInfo->m_orderState = ORDERSTATUS_P3;
			orderInfo->m_orderStatus = PublicMethod::GetOrderStatus(orderInfo->m_orderState);
			break;
		case ORDERSTATUS_P5:
			break;
		case ORDERSTATUS_P6:
			break;
		default:
			break;
	}
	DataCenter::GetRedisDataManager()->AddUpdateOrderInfo(orderInfo);
	SendMsgToClient(orderInfo, socketID);
}

void TraderDataManager::UpdateTraderPosition(String traderId, Position position, int socketID)
{
	if(m_traderInfoMap.find(traderId) == m_traderInfoMap.end())
	{
		return;
	}
	TraderBaseInfo *traderBaseInfo = m_traderInfoMap.find(traderId)->second;
	traderBaseInfo->m_positionsLock.Lock();
	vector<Position*> positions = traderBaseInfo->m_Positions->m_traderPosition;
	vector<Position*>::iterator iter = positions.begin();
	for(;iter != positions.end(); iter++)
	{
		Position *po = *iter;
		if(position.m_code == po->m_code)
		{
			po->m_frozenVolume = position.m_frozenVolume;
			po->m_volume = position.m_volume;
			break;
		}
	}
	traderBaseInfo->m_positionsLock.UnLock();
	Binary binary;
	binary.WriteString(L"");
	binary.WriteString(traderId);
	binary.WriteString(position.m_code);
	binary.WriteDouble(position.m_volume);
	binary.WriteDouble(position.m_frozenVolume);
	//封装Message
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, API_TD_NOTIFY_POSITION, 0, 0, socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->SendMsg(message);
}


void TraderDataManager::SendMsgToClient(OrderInfo *orderInfo, int socketID)
{
	Binary binary;
	binary.WriteString(orderInfo->m_flag);
	binary.WriteString(orderInfo->m_traderID);
	binary.WriteInt(orderInfo->m_errorCode);
	binary.WriteString(orderInfo->m_tradePair);
	binary.WriteString(orderInfo->m_orderID);
	binary.WriteString(orderInfo->m_targetFee);
	binary.WriteDouble(orderInfo->m_price);
	binary.WriteDouble(orderInfo->m_volume);
	binary.WriteDouble(orderInfo->m_orderFee);
	binary.WriteDouble(orderInfo->m_timestamp);
	binary.WriteInt(orderInfo->m_isFeeTartget);
	binary.WriteInt(orderInfo->m_isDealFeeDemand);
	binary.WriteInt(orderInfo->m_orderWay);
	binary.WriteInt(orderInfo->m_dir);
	binary.WriteDouble(orderInfo->m_tradedVolume);
	binary.WriteDouble(orderInfo->m_openedVolume);
	binary.WriteInt(orderInfo->m_orderState);
	binary.WriteString(orderInfo->m_orderStatus);
	//封装Message
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, API_TD_ORDER, 0, 0, socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->SendMsg(message);
}