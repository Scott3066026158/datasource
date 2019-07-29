#include "..\\global\\DataCenter.h"
#include "..\\bean\\TraderBaseInfo.h"
#include "..\\bean\\CBean.h"
#include "..\\global\\Convert.h"
#include "TraderUpdateService.h"
#include "..\\global\\BusinessIDs.h"
#include "..\\api\\PublicMethod.h"

TraderUpdateService::TraderUpdateService()
{
	m_traderDataManager = DataCenter::GetTraderDataManager();
}

TraderUpdateService::~TraderUpdateService(){}

// 委托回报
int TraderUpdateService::InsertOrder(CMessage* msg)
{
	OrderInfo *orderInfo = new OrderInfo;
	Convert::ReadOrderInfo(msg, orderInfo);
	orderInfo->m_tradedVolume = 0.0;
	orderInfo->m_openedVolume = orderInfo->m_volume;
	if(orderInfo->m_errorCode == ERROR_NOERROR)
	{
		orderInfo->m_orderState = ORDERSTATUS_P1;
		orderInfo->m_orderStatus = orderInfo->GetOrderStatus(ORDERSTATUS_P1);
	}
	else
	{
		orderInfo->m_orderState = ORDERSTATUS_P6;
		orderInfo->m_orderStatus = orderInfo->GetOrderStatus(ORDERSTATUS_P6);
	}
	if(m_traderDataManager->GetTraderData(orderInfo->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	OrderInfo* newOrderInfo = new OrderInfo();
	*newOrderInfo = *orderInfo;
	m_orderInfoLock.Lock();
	m_orderInfoList.push_back(newOrderInfo);
	m_orderInfoLock.UnLock();
	//m_traderDataManager->InsertTraderOrderInfo(copyorderInfo);
	DataCenter::GetRedisDataManager()->InsertOrderInfoToRedis(orderInfo->m_traderID, orderInfo);
	string ordersql;
	CStrA::wstringTostring(ordersql, orderInfo->getInsertSqlString());
	DataCenter::GetRabbitmqProducter()->send_to_rabbit_mq(ordersql.c_str());
	Convert::WriteOrderInfo(msg, orderInfo);
	delete orderInfo;
	return 1;
}

// 撤单回报
int TraderUpdateService::InsertCancel(CMessage* msg)
{
	CancelOrder *cancelOrder = new CancelOrder;
	Convert::ReadCancelOrder(msg,cancelOrder);
	cancelOrder->m_cancelID = cancelOrder->m_orderID;
	if(m_traderDataManager->GetTraderData(cancelOrder->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	//插入撤单列表
	m_traderDataManager->InsertTraderCancel(cancelOrder);
	//更新订单委托列表
	m_traderDataManager->UpdateOrderInfo(cancelOrder, msg->m_socketID);
	DataCenter::GetRedisDataManager()->InsertCancelOrderToRedis(cancelOrder->m_traderID, cancelOrder);
	Convert::WriteCancelOrder(msg,cancelOrder);
	return 1;
}

// 资金回报
int TraderUpdateService::InsertPosition(CMessage* msg)
{
	TraderPosition *traderPosition = new TraderPosition;
	Convert::ReadPosition(msg,traderPosition);
	if(m_traderDataManager->GetTraderData(traderPosition->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	//更新用户资金数据
	m_traderDataManager->InsertTraderPosition(traderPosition);
	return 1;
}

// 地址回报
int TraderUpdateService::InsertAddr(CMessage* msg)
{
	Address *address = new Address;
	Convert::ReadAddress(msg,address);
	if(m_traderDataManager->GetTraderData(address->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	m_traderDataManager->InsertTraderAddress(address);
	DataCenter::GetRedisDataManager()->InsertDepositAddrToRedis(address->m_traderID, address);
	return 0;
}

// 提现申请回报
int TraderUpdateService::InsertWithdrawalApply(CMessage* msg)
{
	WithdrawalApply *withdrawalApply = new WithdrawalApply;
	Convert::ReadWithdrawalApply(msg,withdrawalApply);
	withdrawalApply->m_withdrawalID = CStrA::ConvertIntToStr(rand()%1000000);
	withdrawalApply->m_finishStatus = L"Completed";
	PublicMethod::getCurrentTime(&withdrawalApply->m_withdrawalDate, &withdrawalApply->m_withdrawalTime);
	if(m_traderDataManager->GetTraderData(withdrawalApply->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	m_traderDataManager->InsertTraderWithdrawalApply(withdrawalApply);
	DataCenter::GetRedisDataManager()->InsertWithdrawalRecordToRedis(withdrawalApply->m_traderID, withdrawalApply);
	Convert::WriteWithdrawalApply(msg,withdrawalApply);
	return 1;
}

// 成交回报
int TraderUpdateService::InsertTrade(CMessage* msg)
{
	TradeRecord *tradeRecord = new TradeRecord;
	Convert::ReadTradeRecord(msg, tradeRecord);
	if(m_traderDataManager->GetTraderData(tradeRecord->m_traderID) == 0)
	{
		//用户不存在
		return 0;
	}
	//插入用户成交记录表
	//m_traderDataManager->InsertTraderRecord(tradeRecord);
	DataCenter::GetRedisDataManager()->InsertTradeRecordToRedis(tradeRecord->m_traderID, tradeRecord);
	DataCenter::GetRabbitmqProducter()->send_to_rabbit_mq(tradeRecord->getInsertSqlString().c_str());
	//更新相应的委托信息
	m_traderDataManager->UpdateOrderInfo(tradeRecord, msg->m_socketID);

	delete tradeRecord;
	return 1;
}

//用户资金变化回报
int TraderUpdateService::UpdateTraderFund(CMessage* msg)
{
	BalanceNoticeRecord* record = new BalanceNoticeRecord();
	
	Position* position = new Position();
	Convert::ReadBalanceNoticeRecord(msg, record, position);
	if(m_traderDataManager->GetTraderData(record->m_traderID) == 0)
	{
		return 0;
	}
	Position* oldPosition = DataCenter::GetTraderDataManager()->GetPositionByCode(record->m_traderID, record->m_coinCode);
	if(oldPosition == 0)
	{
		record->m_changeBalance = record->m_balance - 0;
		record->m_changeFrozen = record->m_frozenBalance - 0;
	}
	else
	{
		record->m_changeBalance = record->m_balance - oldPosition->m_volume;
		record->m_changeFrozen = record->m_frozenBalance - oldPosition->m_frozenVolume;
	}
	BalanceNoticeRecord* newBalanceNotice = new BalanceNoticeRecord();
	*newBalanceNotice = *record;
	m_balanceNoticeLock.Lock();
	m_balanceNoticeList.push_back(newBalanceNotice);
	m_balanceNoticeLock.UnLock();
	DataCenter::GetRedisDataManager()->InsertPositionToRedis(record->m_traderID, position);
	m_traderDataManager->UpdateTraderPosition(record->m_traderID, *position, msg->m_socketID);
	delete record, position;
	return 1;
}
