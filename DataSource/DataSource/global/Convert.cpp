#include "..\\stdafx.h"
#include "..\\global\\DataCenter.h"
#include "..\\owsock\\Binary.h"
#include "BusinessIDs.h"
#include "..\\api\\PublicMethod.h"
#include "..\\bean\\CBean.h"
#include "Convert.h"

void Convert::ReadOrderInfo(CMessage* message, OrderInfo* orderInfo)
{
	Binary binary;
	char *sendDatas = message->m_body;
	binary.Write(sendDatas, message->m_bodyLength);

	binary.ReadString(orderInfo->m_flag);
	binary.ReadString(orderInfo->m_traderID);
	orderInfo->m_errorCode = binary.ReadInt();
	binary.ReadString(orderInfo->m_tradePair);

	binary.ReadString(orderInfo->m_orderID);
	binary.ReadString(orderInfo->m_targetFee);
	orderInfo->m_price = binary.ReadDouble();
	orderInfo->m_volume = binary.ReadDouble();
	orderInfo->m_orderFee = binary.ReadDouble();
	orderInfo->m_timestamp = binary.ReadDouble();
	orderInfo->m_isFeeTartget = binary.ReadInt();
	orderInfo->m_isDealFeeDemand = binary.ReadInt();
	orderInfo->m_orderWay = binary.ReadInt();
	orderInfo->m_dir = binary.ReadInt();
	/*
	orderInfo->m_tradedVolume = binary.ReadDouble();
	orderInfo->m_openedVolume = binary.ReadDouble();
	orderInfo->m_orderState = binary.ReadInt();
	binary.ReadString(orderInfo->m_orderStatus);
	*/
}

void Convert::ReadCancelOrder(CMessage* message,CancelOrder* cancelOrder)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(cancelOrder->m_flag);
	binary.ReadString(cancelOrder->m_traderID);
	cancelOrder->m_status = binary.ReadInt();
	if(cancelOrder->m_status == CANCEL_ORDER_SUCCESS)
	{
		binary.ReadString(cancelOrder->m_orderID);
		binary.ReadString(cancelOrder->m_tradePair);
		cancelOrder->m_price = binary.ReadDouble();
		cancelOrder->m_volume = binary.ReadDouble();
		cancelOrder->m_dir = binary.ReadInt();
	}
	//binary.ReadString(cancelOrder->m_cancelID);
}


void Convert::ReadPosition(CMessage* message,TraderPosition *traderPosition)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);

	binary.ReadString(traderPosition->m_flag);
	binary.ReadString(traderPosition->m_traderID);
	traderPosition->m_count = binary.ReadInt();
	
	for(int i = 0; i < traderPosition->m_count; i++)
	{
		Position *position = new Position;
		binary.ReadString(position->m_code);
		position->m_volume = binary.ReadDouble();
		position->m_frozenVolume = binary.ReadDouble();
		traderPosition->m_traderPosition.push_back(position);
	}
}

void Convert::ReadAddress(CMessage* message,Address *address)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(address->m_flag);
	binary.ReadString(address->m_traderID);
	binary.ReadString(address->m_coinCode);
	binary.ReadString(address->m_addr);
	binary.ReadString(address->m_memo);
}

void Convert::ReadWithdrawalApply(CMessage* message, WithdrawalApply *withdrawalApply)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(withdrawalApply->m_flag);
	binary.ReadString(withdrawalApply->m_traderID);
	withdrawalApply->m_errorCode = binary.ReadInt();
	binary.ReadString(withdrawalApply->m_coinCode);
	binary.ReadString(withdrawalApply->m_outAddr);
	binary.ReadString(withdrawalApply->m_memo);
	withdrawalApply->m_balance = binary.ReadDouble();
	withdrawalApply->m_fee = binary.ReadDouble();
	/*binary.ReadString(withdrawalApply->m_withdrawalID);
	binary.ReadString(withdrawalApply->m_withdrawalDate);
	binary.ReadString(withdrawalApply->m_withdrawalTime);
	binary.ReadString(withdrawalApply->m_finishStatus);
	withdrawalApply->m_progress = binary.ReadDouble();*/
}

void Convert::ReadTradeRecord(CMessage* message,TradeRecord *tradeRecord)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(tradeRecord->m_code);
	binary.ReadString(tradeRecord->m_transID);
	binary.ReadString(tradeRecord->m_orderID);
	binary.ReadString(tradeRecord->m_traderID);
	tradeRecord->m_volume = binary.ReadDouble();
	tradeRecord->m_price = binary.ReadDouble();
	tradeRecord->m_timestamp = binary.ReadDouble();
	tradeRecord->direction = binary.ReadInt();
	tradeRecord->m_isFinish = binary.ReadInt();
}

void Convert::ReadReqParamer(CMessage* message,ReqParamer *reqParamer)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(reqParamer->m_flag);
	binary.ReadString(reqParamer->m_traderID);
}

void Convert::ReadReqAddrParamer(CMessage* message, ReqAddrParamer *reqParamer)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(reqParamer->m_flag);
	binary.ReadString(reqParamer->m_traderID);
	binary.ReadString(reqParamer->m_coinCode);
}

void Convert::ReadBalanceNoticeRecord(CMessage* message, BalanceNoticeRecord *balanceNoticeRecord, Position* position)
{
	Binary binary;
	binary.Write(message->m_body, message->m_bodyLength);
	binary.ReadString(balanceNoticeRecord->m_notifyID);
	binary.ReadString(balanceNoticeRecord->m_traderID);
	binary.ReadString(balanceNoticeRecord->m_coinCode);
	balanceNoticeRecord->m_balance = binary.ReadDouble();
	balanceNoticeRecord->m_frozenBalance = binary.ReadDouble();
	balanceNoticeRecord->m_timestamp = binary.ReadDouble();
	balanceNoticeRecord->m_reason = binary.ReadInt();

	position->m_code = balanceNoticeRecord->m_coinCode;
	position->m_frozenVolume = balanceNoticeRecord->m_frozenBalance;
	position->m_volume = balanceNoticeRecord->m_balance;
}

void Convert::WriteOrderInfo(CMessage* message,OrderInfo* orderInfo)
{
	Binary binary;
	binary.WriteString(orderInfo->m_flag);
	binary.WriteString(orderInfo->m_traderID);
	binary.WriteInt(orderInfo->m_errorCode);
	binary.WriteString(orderInfo->m_tradePair);
	binary.WriteString(orderInfo->m_orderID);//orderID
	binary.WriteString(orderInfo->m_targetFee);
	binary.WriteDouble(orderInfo->m_price);
	binary.WriteDouble(orderInfo->m_volume);
	binary.WriteDouble(orderInfo->m_orderFee);//委托手续费
	binary.WriteDouble(orderInfo->m_timestamp);//时间戳
	binary.WriteInt(orderInfo->m_isFeeTartget);//是否收取额外的指定手续费
	binary.WriteInt(orderInfo->m_isDealFeeDemand);//是否需要成交后收取手续费
	binary.WriteInt(orderInfo->m_orderWay);
	binary.WriteInt(orderInfo->m_dir);//下单方向
	binary.WriteDouble(orderInfo->m_tradedVolume);//成交手数
	binary.WriteDouble(orderInfo->m_openedVolume);//挂单手数
	binary.WriteInt(orderInfo->m_orderState);//委托状态
	CMessage* msg = new CMessage(0, DATASOURCE_SERVICE_ID, message->m_functionID, 0, message->m_requestID, message->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->SendMsg(msg);
}
void Convert::WriteCancelOrder(CMessage* message,CancelOrder* cancelOrder)
{
	Binary binary;
	binary.WriteString(cancelOrder->m_flag);
	binary.WriteString(cancelOrder->m_traderID);
	int orderID = CStrA::ConvertStrToInt(cancelOrder->m_orderID.c_str());
	binary.WriteInt(orderID);
	binary.WriteString(cancelOrder->m_orderID);//委托ID
	binary.WriteString(cancelOrder->m_tradePair);//交易对子
	binary.WriteDouble(cancelOrder->m_price);//委托价格
	binary.WriteDouble(cancelOrder->m_volume);//委托手数
	binary.WriteInt(cancelOrder->m_dir);//方向
	binary.WriteString(cancelOrder->m_cancelID);//撤单ID
	CMessage* msg = new CMessage(0, DATASOURCE_SERVICE_ID, message->m_functionID, 0, message->m_requestID, message->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->SendMsg(msg);
}
void Convert::WriteWithdrawalApply(CMessage* message, WithdrawalApply *withdrawalApply)
{
	Binary binary;
	binary.WriteString(withdrawalApply->m_flag);
	binary.WriteString(withdrawalApply->m_traderID);
	binary.WriteInt(withdrawalApply->m_errorCode);
	binary.WriteString(withdrawalApply->m_coinCode);
	binary.WriteString(withdrawalApply->m_outAddr);
	binary.WriteString(withdrawalApply->m_memo);
	binary.WriteDouble(withdrawalApply->m_balance);
	binary.WriteDouble(withdrawalApply->m_fee);//出金手续费为0
	binary.WriteString(withdrawalApply->m_withdrawalID);//出金申请流水号为空
	binary.WriteString(withdrawalApply->m_withdrawalDate);//出金日期
	binary.WriteString(withdrawalApply->m_withdrawalTime);//出金时间
	binary.WriteString(withdrawalApply->m_finishStatus);//出金进度描述
	binary.WriteDouble(withdrawalApply->m_progress);//出金进度百分比
	CMessage* msg = new CMessage(0, DATASOURCE_SERVICE_ID, message->m_functionID, 0, message->m_requestID, message->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->Send(msg);
}

void Convert::WriteTradeRecord(CMessage* message,TradeRecord *tradeRecord)
{
	Binary binary;
	binary.WriteString(tradeRecord->m_code);
	binary.WriteString(tradeRecord->m_transID);
	binary.WriteString(tradeRecord->m_orderID);
	binary.WriteString(tradeRecord->m_traderID);
	binary.WriteDouble(tradeRecord->m_volume);
	binary.WriteDouble(tradeRecord->m_price);
	binary.WriteDouble(tradeRecord->m_timestamp);
	binary.WriteInt(tradeRecord->direction);
	binary.WriteInt(tradeRecord->m_isFinish);
	CMessage* msg = new CMessage(0, DATASOURCE_SERVICE_ID, message->m_functionID, 0, message->m_requestID, message->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	DataCenter::GetConnectProxy()->Send(msg);
}