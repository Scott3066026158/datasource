#include "..\\stdafx.h"
#include "..\\global\\DataCenter.h"
#include "..\\global\\BusinessIDs.h"
#include "Router.h"

Router::Router()
{
	//启动处理消息线程
	::CreateThread(0, 0, Wan, (LPVOID)this, 0, 0);
}

Router::~Router()
{
}

DWORD WINAPI Router::Wan(LPVOID lpParam)
{
	ConnectProxy* cs = DataCenter::GetConnectProxy();
	TraderQueryService *traderQueryService =  DataCenter::GetTraderQueryService();
	TraderUpdateService *traderUpdateService = DataCenter::GetTraderUpdateService();
	while(true)
	{
		::Sleep(10);
		if(cs->m_revMsg.size() == 0)
		{
			continue;
		}
		cs->m_revLock.Lock();
        vector<CMessage*> messages(cs->m_revMsg);
        cs->m_revMsg.clear();
		cs->m_revLock.UnLock();
		for(vector<CMessage*>::iterator msgIter = messages.begin(); msgIter != messages.end(); msgIter++)
		{
			CMessage* msg = *msgIter;
			switch(msg->m_functionID)
			{
			//用户登录
			case API_TD_LOGIN:
				DataCenter::GetTraderDataManager()->TraderLogin(msg);
				break;
			// 查询所有委托
			case QRY_ALL_ORDERS:
				traderQueryService->QueryAllOrders(msg);
				break;
			// 查询所有成交
			case QRY_ALL_TRADES:
				traderQueryService->QueryAllTrades(msg);
				break;
			// 查询所有提现记录
			case QRY_ALL_WITHDRAWALS:
				traderQueryService->QueryAllWithdrawals(msg);
				break;
			// 查询所有币种资金
			case QRY_ALL_POSITIONS:
				traderQueryService->QueryAllPositions(msg);
				break;
			// 查询单个币种充值地址
			case QRY_RECHARGE_ADDR:
				traderQueryService->QueryCoinAddr(msg);
				break;
			// 委托回报，更新委托数据
			case API_TD_ORDER:
				traderUpdateService->InsertOrder(msg);
				break;
			// 撤单回报，更新数据
			case API_TD_CANCEL_ORDER:
				traderUpdateService->InsertCancel(msg);
				break;
			// 资金回报，更新数据
			case API_TD_POSITION:
				traderUpdateService->InsertPosition(msg);
				break;
			// 地址回报，更新数据
			case API_TD_DEPOSIT:
				traderUpdateService->InsertAddr(msg);
				break;
			// 提现申请回报，更新数据
			case API_TD_WITHDRAWAL:
				traderUpdateService->InsertWithdrawalApply(msg);
				break;
			// 成交回报，更新数据
			case API_TD_NOTIFY_ORDER_DEAL:
				traderUpdateService->InsertTrade(msg);
				break;
			case API_TD_NOTIFY_USER_FUND:
				traderUpdateService->UpdateTraderFund(msg);
				break;
			default:
				break;
			}	
			delete msg;
		}
	}
}

int Router::Lan()
{
	return 0;
}

