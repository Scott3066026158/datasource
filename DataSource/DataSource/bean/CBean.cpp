#include "..\\stdafx.h"
#include "CBean.h"
#include "..\\api\\CStr.h"
#include "..\\global\\BusinessIDs.h"


string Address::toString()
{
	char buf[1024];
	sprintf(buf, "%d,%S,%S,%S,%S,%S",this->errorCode,this->m_flag.c_str(),this->m_traderID.c_str()
									,this->m_coinCode.c_str(),this->m_addr.c_str(),this->m_memo.c_str());
	return buf;
};

string CancelOrder::toString()
{
	char buf[1024];
	sprintf(buf, "%S,%S,%S,%S,%d,%S,%f,%f,%d",this->m_flag.c_str(),this->m_traderID.c_str(),this->m_orderID.c_str(),
		this->m_cancelID.c_str(),this->m_status,this->m_tradePair.c_str(),this->m_price,this->m_volume,this->m_dir);
	
	return buf;
};

string OrderInfo::toString()
{
	char buf[2048];
	sprintf(buf,"%d,%S,%S,%S,%S,%S,%f,%f,%f,%f,%d,%d,%d,%d,%f,%f,%d,%S",
		this->m_errorCode, this->m_tradePair.c_str(), this->m_orderID.c_str(), this->m_targetFee.c_str(),
		this->m_flag.c_str(), this->m_traderID.c_str(), this->m_price, this->m_volume, this->m_orderFee, this->m_timestamp,
		this->m_isFeeTartget, this->m_isDealFeeDemand, this->m_orderWay, this->m_dir, this->m_tradedVolume, this->m_openedVolume,
		this->m_orderState, this->m_orderStatus.c_str());
	return buf;
};

void OrderInfo::toObject(const string &orderinfo)
{
	int errorCode;
	wchar_t tradePair[32], orderID[64], targetFee[64], flag[32], traderID[32],orderStatus[128];
	double 	price, volume, orderFee, timestamp;		
	int isFeeTartget, isDealFeeDemand, orderWay, dir;
	double tradedVolume, openedVolume;
    int orderState;
	vector<string> orderinfos = CStrA::Split(orderinfo,",");
	vector<string>::iterator it = orderinfos.begin();
	for(; it != orderinfos.end(); it++)
	{
		string order = *it;
		this->m_errorCode = atoi(orderinfos[0].c_str());
		CStrA::stringTowstring(this->m_tradePair,orderinfos[1]);
		CStrA::stringTowstring(this->m_orderID,orderinfos[2]);
		CStrA::stringTowstring(this->m_targetFee,orderinfos[3]);
		CStrA::stringTowstring(this->m_flag,"");
		CStrA::stringTowstring(this->m_traderID,orderinfos[4]);
		this->m_price = atof(orderinfos[5].c_str());
		this->m_volume = atof(orderinfos[6].c_str());
		this->m_orderFee = atof(orderinfos[7].c_str());
		this->m_timestamp = atof(orderinfos[8].c_str());
		this->m_isFeeTartget = atoi(orderinfos[9].c_str());
		this->m_isDealFeeDemand = atoi(orderinfos[10].c_str());
		this->m_orderWay = atoi(orderinfos[11].c_str());
		this->m_dir = atoi(orderinfos[12].c_str());
		this->m_tradedVolume = atof(orderinfos[13].c_str()); 
		this->m_openedVolume = atof(orderinfos[14].c_str());
		this->m_orderState = atoi(orderinfos[15].c_str());
		CStrA::stringTowstring(this->m_orderStatus,orderinfos[16]);
		return;
	}
	

};

String OrderInfo::getInsertSqlString()
{
	wchar_t buf[1024] = {0};
	swprintf(buf,L"insert into orderinfo values ('%s','%s',%d,'%s','%s','%s',%f,%f,%f,%f,%d,%d,%d,%d,%f,%f,%d,'%s');",
		this->m_flag.c_str(),this->m_traderID.c_str(),this->m_errorCode, this->m_tradePair.c_str(), this->m_orderID.c_str(),
		this->m_targetFee.c_str(), this->m_price, this->m_volume, this->m_orderFee, this->m_timestamp,
		this->m_isFeeTartget, this->m_isDealFeeDemand, this->m_orderWay, this->m_dir, this->m_tradedVolume, this->m_openedVolume,
		this->m_orderState, this->m_orderStatus.c_str());
	return buf;
}

string OrderInfo::getUpDateSqlString(OrderInfo *order)
{
	char buf[1024] = {0};
	sprintf(buf,"UPDATE orderinfo SET tradedVolume = %f,openedVolume = %f,orderState = %d,orderStatus = '%S' where orderid = '%S';",order->m_tradedVolume, order->m_openedVolume,
		order->m_orderState, order->m_orderStatus, order->m_orderID.c_str());
	return buf;
}

String OrderInfo::GetOrderStatus(int state)
{
	String result;
	switch(state)
	{
		case ORDERSTATUS_P1:
			result = L"InOrder";
			break;
		case ORDERSTATUS_P2:
			result = L"Canceled";
			break;
		case ORDERSTATUS_P3:
			result = L"PairCancel";
			break;
		case ORDERSTATUS_P4:
			result = L"PartTraded";
			break;
		case ORDERSTATUS_P5:
			result = L"Traded";
			break;
		case ORDERSTATUS_P6:
			result = L"Faild";
			break;
		default:
			result = L"Faild";
			break;
	}
	return result;
}

string Position::toString()
{
	char buf[128];
	sprintf(buf,"%S,%f,%f",this->m_code.c_str(),this->m_frozenVolume,this->m_volume);
	return buf;
};


string TradeRecord::toString()
{
	char buf[1024];
	sprintf(buf,"%S,%S,%S,%S,%f,%f,%f,%d,%d",this->m_code.c_str(), this->m_transID.c_str(), this->m_orderID.c_str(),
		this->m_traderID.c_str(),this->m_volume,this->m_price,this->m_timestamp,this->direction,this->m_isFinish);
	return buf;
};

string TradeRecord::getInsertSqlString()
{
	char buf[1024] = {0};
	sprintf(buf,"insert into traderinfo values ('%S','%S','%S','%S',%f,%f,%f,%d,%d);",this->m_code.c_str(), this->m_transID.c_str(), this->m_orderID.c_str(),
		this->m_traderID.c_str(),this->m_volume,this->m_price,this->m_timestamp,this->direction,this->m_isFinish);
	return buf;
}

string TradeRecord::getUpDateSqlString(OrderInfo *order)
{
	char buf[1024] = {0};
	sprintf(buf,"UPDATE orderInfo SET tradedVolume = %f,openedVolume = %f,orderState = %d where orderid = '%S';",order->m_tradedVolume, order->m_openedVolume,
		order->m_orderState, order->m_orderID.c_str());
	return buf;
}

	
string WithdrawalApply::toString()
{
	char buf[2048];
	sprintf(buf,"%S,%S,%d,%S,%S,%S,%S,%f,%f,%S,%S,%S,%f",this->m_flag.c_str(),this->m_traderID.c_str(),this->m_errorCode,
		this->m_withdrawalID.c_str(),this->m_coinCode.c_str(),this->m_outAddr.c_str(),this->m_memo.c_str(),this->m_balance,
		this->m_fee,this->m_withdrawalDate.c_str(),this->m_withdrawalTime.c_str(),this->m_finishStatus.c_str(),this->m_progress);
	return buf;
}


BalanceNoticeRecord::BalanceNoticeRecord()
{
	m_balance = 0;
	m_frozenBalance = 0;
	m_timestamp = 0;
	m_reason = 0;
	m_changeBalance = 0;
	m_changeFrozen = 0;
}

BalanceNoticeRecord::~BalanceNoticeRecord()
{
	m_balance = 0;
	m_frozenBalance = 0;
	m_timestamp = 0;
	m_reason = 0;
	m_changeBalance = 0;
	m_changeFrozen = 0;
}