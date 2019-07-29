#pragma once
#ifndef __Convert_H__
#define __Convert_H__

#include "..\\bean\\CBean.h"
#include "..\\owsock\\CMessage.h"

class Convert
{
	public:
		static void ReadOrderInfo(CMessage* message, OrderInfo* orderInfo);
		static void ReadCancelOrder(CMessage* message, CancelOrder* cancelOrder);
		static void ReadPosition(CMessage* message, TraderPosition *traderPosition);
		static void ReadAddress(CMessage* message ,Address *address);
		static void ReadWithdrawalApply(CMessage* message, WithdrawalApply *withdrawalApply);
		static void ReadTradeRecord(CMessage* message, TradeRecord *tradeRecord);
		static void ReadReqParamer(CMessage* message, ReqParamer *reqParamer);
		static void ReadReqAddrParamer(CMessage* message, ReqAddrParamer *reqParamer);
		static void ReadBalanceNoticeRecord(CMessage* message, BalanceNoticeRecord *balanceNoticeRecord, Position* position);
		static void WriteOrderInfo(CMessage* message, OrderInfo* orderInfo);
		static void WriteCancelOrder(CMessage* message, CancelOrder* cancelOrder);
		static void WriteWithdrawalApply(CMessage* message, WithdrawalApply *withdrawalApply);
		static void WriteTradeRecord(CMessage* message, TradeRecord *tradeRecord);
};


#endif