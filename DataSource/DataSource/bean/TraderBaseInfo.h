#pragma once
#ifndef __TraderBaseInfo_H__
#define __TraderBaseInfo_H__

#include "CBean.h"
#include "..\\api\\CLock.h"
class TraderBaseInfo
{
public: 
	//traderID
	String m_traderID;
	//资金列表锁
	CLock m_positionsLock;
	//资金列表
	TraderPosition *m_Positions;
	//委托列表锁
	CLock m_orderInfosLock;
	//委托列表
	map<String, OrderInfo*> m_orderInfosMap;
	//挂单列表锁
	CLock m_openOrdersLock;
	//挂单列表
	map<String, OrderInfo*> m_openOrdersMap;
	//撤单列表锁
	CLock m_cancelOrdersLock;
	//撤单列表
	map<String, CancelOrder*> m_cancelOrdersMap;
	//成交列表锁
	CLock m_tradeRecordsLock;
	//成交列表
	map<String, TradeRecord*> m_tradeRecordsMap;
	//提现申请列表锁
	CLock m_withdrawApplyLock;
	//提现申请列表
	map<String, WithdrawalApply*> m_withdrawalApplyRecordsMap;
	//充值地址列表锁
	CLock m_coinAddrLock;
	//充值地址列表
	map<String,Address*> m_coinAddr;
};

#endif
