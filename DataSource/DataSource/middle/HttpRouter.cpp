#include "..\\stdafx.h"
#include "..\\global\\DataCenter.h"
#include "..\\global\\BusinessIDs.h"
#include "HttpRouter.h"
#include "..\\jsonapi\\json.h"
using namespace OwLibCT;
using namespace Json;

HttpRouter::HttpRouter()
{
	//启动处理消息线程
	::CreateThread(0, 0, Wan, (LPVOID)this, 0, 0);
}

HttpRouter::~HttpRouter()
{
}

DWORD WINAPI HttpRouter::Wan(LPVOID lpParam)
{
	TraderUpdateService* traderUpdateService = DataCenter::GetTraderUpdateService();
	HttpRouter* router = (HttpRouter*)lpParam;
	while(true)
	{
		if(traderUpdateService->m_balanceNoticeList.size() == 0 && traderUpdateService->m_orderInfoList.size() == 0)
		{
			::Sleep(10);
			continue;
		}
		traderUpdateService->m_balanceNoticeLock.Lock();
		vector<BalanceNoticeRecord*> balanceNoticeList;
		balanceNoticeList.swap(traderUpdateService->m_balanceNoticeList);
		traderUpdateService->m_balanceNoticeLock.UnLock();
		router->ReqBalanceNotice(balanceNoticeList);
		
		traderUpdateService->m_orderInfoLock.Lock();
		vector<OrderInfo*> orderInfoList;
		orderInfoList.swap(traderUpdateService->m_orderInfoList);
		traderUpdateService->m_orderInfoLock.UnLock();
		router->ReqOrderInfo(orderInfoList);
	}

	
}

void HttpRouter::ReqBalanceNotice(vector<BalanceNoticeRecord*> msg)
{
	HttpPostService* m_httpPostService = DataCenter::GetHttpPostService();
	for(vector<BalanceNoticeRecord*>::iterator iter = msg.begin(); iter != msg.end(); iter++)
	{
		BalanceNoticeRecord* record = *iter;
		Json::Value reqValue;
			
		reqValue["noticeid"] = CStrA::wstringTostring(record->m_notifyID);
		reqValue["traderid"] = CStrA::wstringTostring(record->m_traderID);
		reqValue["coincode"] = CStrA::wstringTostring(record->m_coinCode);
		reqValue["balance"] = record->m_balance;
		reqValue["frozen"] = record->m_frozenBalance;
		reqValue["cbalance"] = record->m_changeBalance;
		reqValue["cfrozen"] = record->m_changeFrozen;
		reqValue["reason"] = record->m_reason;
		reqValue["timestamp"] = record->m_timestamp;
		Json::FastWriter fw;
		string data = fw.write(reqValue);
		string result = m_httpPostService->Post(L"http://192.168.86.220:8083/trade/funds", (char*)data.c_str(), (size_t)data.size());
		Json::Reader reader;
		Json::Value respValue;
		if(reader.parse(result.c_str(), respValue)) 
		{
			int status = respValue["code"].asInt();
			if(status == 0)
			{
				printf("发送给AllinEx的数据是:%s", data.c_str());
			}
		}
		break;
	}
}

void HttpRouter::ReqOrderInfo(vector<OrderInfo*> orderInfoList)
{
	HttpPostService* m_httpPostService = DataCenter::GetHttpPostService();
	for(vector<OrderInfo*>::iterator iter = orderInfoList.begin(); iter != orderInfoList.end(); iter++)
	{
		OrderInfo* orderInfo = *iter;
		Json::Value reqValue;
		reqValue["errorcode"] = orderInfo->m_errorCode;
		reqValue["pair"] = CStrA::wstringTostring(orderInfo->m_tradePair);
		reqValue["orderid"] = CStrA::wstringTostring(orderInfo->m_orderID);
		reqValue["targetfee"] = CStrA::wstringTostring(orderInfo->m_targetFee);
		reqValue["flag"] = CStrA::wstringTostring(orderInfo->m_flag);
		reqValue["traderid"] = CStrA::wstringTostring(orderInfo->m_traderID);
		reqValue["price"] = orderInfo->m_price;
		reqValue["volume"] = orderInfo->m_volume;
		reqValue["orderfee"] = orderInfo->m_orderFee;
		reqValue["timestamp"] = orderInfo->m_timestamp;
		reqValue["isfeetarget"] = orderInfo->m_isFeeTartget;
		reqValue["isdealfeedemand"] = orderInfo->m_isDealFeeDemand;
		reqValue["orderway"] = orderInfo->m_orderWay;
		reqValue["dir"] = orderInfo->m_dir;
		reqValue["tradedvolume"] = orderInfo->m_tradedVolume;
		reqValue["openedvolume"] = orderInfo->m_openedVolume;
		reqValue["state"] = orderInfo->m_orderState;
		reqValue["status"] = CStrA::wstringTostring(orderInfo->m_orderStatus);
		Json::FastWriter fw;
		string data = fw.write(reqValue);
		string result = m_httpPostService->Post(L"http://192.168.86.220:8083/trade/order", (char*)data.c_str(), (size_t)data.size());
		Json::Reader reader;
		Json::Value respValue;
		if(reader.parse(result.c_str(), respValue)) 
		{
			int status = respValue["code"].asInt();
			if(status == 0)
			{
				printf("发送给AllinEx的数据是:%s", data.c_str());
			}
		}
		break;
	}
}
