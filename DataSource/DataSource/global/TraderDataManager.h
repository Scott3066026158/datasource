#pragma once
#ifndef __TraderDataManager_H__
#define __TraderDataManager_H__

#include "..\\owsock\\CMessage.h"
#include "..\\bean\\CBean.h"
#include "..\\bean\\TraderBaseInfo.h"

class TraderDataManager
{
private:
	// 所有用户的交易数据
	map<String, TraderBaseInfo*> m_traderInfoMap;
	CLock m_traderInfoMapLock;
public:
	// 构造函数
	TraderDataManager();
	// 析构函数
	~TraderDataManager();
public:
	//用户登录
	void TraderLogin(CMessage* msg);
	// 根据TraderID获取用户的所有数据
	TraderBaseInfo* GetTraderData(String traderID);

	// 根据TraderID获取用户的所有委托
	void GetTraderAllOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap);

	// 根据TraderID获取用户的所有持仓
	TraderPosition* GetTraderPosition(String traderID);

	// 根据TraderID获取指定币种的持仓信息
	Position* GetPositionByCode(String traderID, String coinCode);

	// 根据TraderID获取用户的所有挂单
	void GetTraderOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap);

	// 根据TraderID获取用户的所有撤单
	void GetTraderCancelOrder(String traderID, map<String, CancelOrder*> &cancelOrderMap);

	// 根据TraderID获取用户的所有成交订单
	void GetTradeRecord(String traderID, map<String, TradeRecord*> &tradeRecordMap);

	// 根据TraderID获取用户的所有提现申请列表
	void GetWithdrawalApplyRecords(String traderID, map<String, WithdrawalApply*> &withdrawalApplyMap);

	// 根据TraderID获取用户币种对应充值地址列表
	Address* GetPositionAddress(String traderID, String coinCode);

	//根据OrderID查找委托回报对象
	//bool FindOrderInfoBySysID(LPDatas *lp, const String &traderID, const String &sysID, CoinOrder *order);

	//插入用户订单数据
	void InsertTraderOrderInfo(OrderInfo *orderInfo);
	//插入用户撤单记录
	void InsertTraderCancel(CancelOrder *cancelOrder);
	//插入用户所有资金数据
	void InsertTraderPosition(TraderPosition *traderPosition);
	//插入用户币种地址
	void InsertTraderAddress(Address *address);
	//插入提现申请
	void InsertTraderWithdrawalApply(WithdrawalApply *withdrawalApply);
	//插入成交记录
	void InsertTraderRecord(TradeRecord *tradeRecord);
	//成交后更新相应的委托订单
	void UpdateOrderInfo(TradeRecord *tradeRecord, int socketID);
	//撤单后更新相应的委托订单
	void UpdateOrderInfo(CancelOrder *cancelOrder, int socketID);
	//将变化后的委托数据发送到Client
	void SendMsgToClient(OrderInfo *orderInfo, int socketID);
	//用户资金更新
	void UpdateTraderPosition(String traderId, Position position, int socketID);
};
	

#endif