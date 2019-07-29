#include "..\\global\\DataCenter.h"
#include "..\\global\\Convert.h"
#include "..\\global\\BusinessIDs.h"
#include "..\\global\\TraderDataManager.h"
#include "TraderQueryService.h"



//���캯��
TraderQueryService::TraderQueryService()
{
	m_traderDataManager = DataCenter::GetTraderDataManager();
	m_connectProxy = DataCenter::GetConnectProxy();
}

//��������
TraderQueryService::~TraderQueryService(){}

	//��ѯ����ί��
void TraderQueryService::QueryAllOrders(CMessage* msg)
{
	//�����������
	bool success = true;
	ReqParamer *reqParamer = new ReqParamer;
	Convert::ReadReqParamer(msg,reqParamer);
	printf("�û�%S�������ж�������\n",reqParamer->m_traderID.c_str());
	//�ӻ����л�ȡ�û�ί������
	map<String, OrderInfo*> orderInfoMap;
	if(m_traderDataManager->GetTraderData(reqParamer->m_traderID) == 0)
	{
		success = false;
	}
	else
	{
		//m_traderDataManager->GetTraderAllOrderInfo(reqParamer->m_traderID, orderInfoMap);
		
	}
	char buf[64] = {0};
	sprintf(buf,"select * from orderInfo where traderID = '%S'", reqParamer->m_traderID.c_str());
	vector<vector<string>> rowcount;
	DataCenter::GetMysqlHelper()->QueryDatabase(buf,rowcount);
	if(rowcount.size() == 0)
	{
		success = false;
	}
	//����ȡ����ί�����ݴ����CMessage
	Binary binary;
	binary.WriteString(reqParamer->m_flag);
	binary.WriteString(reqParamer->m_traderID);
	binary.WriteInt(rowcount.size());
	if(success)
	{
		vector<vector<string>>::iterator it = rowcount.begin();
		for(it; it != rowcount.end(); ++it)
		{
			vector<string> order = *it;
			binary.WriteString(order[0]);//flag
			binary.WriteString(order[1]);//tradetID
			binary.WriteInt(atoi(order[2].c_str()));//errorCode
			binary.WriteString(order[3]);//tradePair
			binary.WriteString(order[4]);//orderID
			binary.WriteString(order[5]);//targetFee
			binary.WriteDouble(atof(order[6].c_str()));//price
			binary.WriteDouble(atof(order[7].c_str()));//volume
			binary.WriteDouble(atof(order[8].c_str()));//orderFee
			binary.WriteDouble(atof(order[9].c_str()));//timestamp
			binary.WriteInt(atoi(order[10].c_str()));//isFeeTartget
			binary.WriteInt(atoi(order[11].c_str()));//isDealFeeDemand
			binary.WriteInt(atoi(order[12].c_str()));//orderWay
			binary.WriteInt(atoi(order[13].c_str()));//dir
			binary.WriteDouble(atoi(order[14].c_str()));//tradedVolume
			binary.WriteDouble(atoi(order[15].c_str()));//openedVolume
			binary.WriteInt(atoi(order[16].c_str()));//orderState
			//CStrA::stringTowstring(ordersInfo->m_orderStatus,order[17]);
		}
	}
	//��װMessage
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	delete reqParamer;
	m_connectProxy->SendMsg(message);
}

//��ѯ���йҵ�
void TraderQueryService::QueryAllOpenOrders(CMessage* msg)
{
	//�����������
	bool success = true;
	ReqParamer *reqParamer = new ReqParamer;
	Convert::ReadReqParamer(msg, reqParamer);
	printf("�û�%S�������йҵ�����\n",reqParamer->m_traderID.c_str());
	//�ӻ����л�ȡ�û�ί������
	map<String, OrderInfo*> orderInfoMap;
	if(m_traderDataManager->GetTraderData(reqParamer->m_traderID) == 0)
	{
		success = false;
	}
	else
	{
		m_traderDataManager->GetTraderOrderInfo(reqParamer->m_traderID, orderInfoMap);
		if(orderInfoMap.size() == 0)
		{
			success = false;
		}
	}
	//����ȡ�������ݴ����CMessage
	map<String, OrderInfo*>::iterator it = orderInfoMap.begin();
	Binary binary;
	binary.WriteString(reqParamer->m_traderID);
	binary.WriteInt(orderInfoMap.size());
	if(success)
	{
		for(; it != orderInfoMap.end(); ++it)
		{
			OrderInfo *orderInfo = it->second;
			binary.WriteInt(orderInfo->m_errorCode);
			binary.WriteString(orderInfo->m_tradePair);
			binary.WriteString(orderInfo->m_orderID);
			binary.WriteString(orderInfo->m_targetFee);
			binary.WriteString(orderInfo->m_flag);
			binary.WriteString(orderInfo->m_traderID);
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
		}
	}
	//��װMessage
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	delete reqParamer;
	m_connectProxy->SendMsg(message);
}

//��ѯ���гɽ�
void TraderQueryService::QueryAllTrades(CMessage* msg)
{
	//�����������
	bool success = true;
	ReqParamer *reqParamer = new ReqParamer;
	Convert::ReadReqParamer(msg,reqParamer);
	printf("�û�%S�������гɽ�����\n",reqParamer->m_traderID.c_str());
	//�ӻ����л�ȡ�û�ί������
	map<String, TradeRecord*> tradeRecordMap;
	if(m_traderDataManager->GetTraderData(reqParamer->m_traderID) == 0)
	{
		success = false;
	}
	else
	{
		//m_traderDataManager->GetTradeRecord(reqParamer->m_traderID, tradeRecordMap);
	}
	//����ȡ�������ݴ����CMessage
	char buf[64] = {0};
	sprintf(buf,"select * from traderinfo where traderID = '%S'", reqParamer->m_traderID.c_str());
	vector<vector<string>> rowcount;
	DataCenter::GetMysqlHelper()->QueryDatabase(buf,rowcount);
	if(rowcount.size() == 0 || rowcount.size() < 9)
	{
		success = false;
	}
	vector<vector<string>>::iterator it = rowcount.begin();
	Binary binary;
	binary.WriteString(reqParamer->m_traderID);
	binary.WriteInt(rowcount.size());
	if(success)
	{
		vector<vector<string>>::iterator it = rowcount.begin();
		for(it; it != rowcount.end(); ++it)
		{
			vector<string> tradeRecord = *it;
			binary.WriteString(tradeRecord[0]);//code
			binary.WriteString(tradeRecord[1]);//m_transID
			binary.WriteString(tradeRecord[2]);//orderID
			binary.WriteString(tradeRecord[3]);//traderID
			binary.WriteDouble(atof(tradeRecord[4].c_str()));//volume
			binary.WriteDouble(atof(tradeRecord[5].c_str()));//price
			binary.WriteDouble(atof(tradeRecord[6].c_str()));//timestamp
			binary.WriteInt(atoi(tradeRecord[7].c_str()));//direction
			binary.WriteInt(atoi(tradeRecord[8].c_str()));//isFinish
			//CStrA::stringTowstring(ordersInfo->m_orderStatus,order[17]);
		}
	}
	//��װMessage
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0,0, binary.GetBytesLen(), (char*)binary.GetBytes());
	delete reqParamer;
	m_connectProxy->SendMsg(message);
}

//��ѯ�������ּ�¼
void TraderQueryService::QueryAllWithdrawals(CMessage* msg)
{
	//�����������
	bool success = true;
	ReqParamer *reqParamer = new ReqParamer;
	Convert::ReadReqParamer(msg,reqParamer);
	printf("�û�%S����������������\n",reqParamer->m_traderID.c_str());
	map<String, WithdrawalApply*> withdrawalApplyRecordMap;
	if(m_traderDataManager->GetTraderData(reqParamer->m_traderID) == 0)
	{
		success = false;
	}
	else
	{
		m_traderDataManager->GetWithdrawalApplyRecords(reqParamer->m_traderID, withdrawalApplyRecordMap);
		if(withdrawalApplyRecordMap.size() == 0)
		{
			success = false;
		}
	}
	map<String, WithdrawalApply*>::iterator it = withdrawalApplyRecordMap.begin();
	Binary binary;
	binary.WriteString(reqParamer->m_traderID);
	binary.WriteInt(withdrawalApplyRecordMap.size());
	if(success)
	{
		for(; it != withdrawalApplyRecordMap.end(); ++it)
		{
			WithdrawalApply *withdrawalApply = it->second;
			binary.WriteString(withdrawalApply->m_flag);
			binary.WriteString(withdrawalApply->m_traderID);
			binary.WriteInt(withdrawalApply->m_errorCode);
			binary.WriteString(withdrawalApply->m_coinCode);
			binary.WriteString(withdrawalApply->m_outAddr);
			binary.WriteString(withdrawalApply->m_memo);
			binary.WriteDouble(withdrawalApply->m_balance);
			binary.WriteDouble(withdrawalApply->m_fee);
			binary.WriteString(withdrawalApply->m_withdrawalID);
			binary.WriteString(withdrawalApply->m_withdrawalDate);
			binary.WriteString(withdrawalApply->m_withdrawalTime);
			binary.WriteString(withdrawalApply->m_finishStatus);
			binary.WriteDouble(withdrawalApply->m_progress);
			
		}
	}
	//��װMessage
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	delete reqParamer;
	m_connectProxy->SendMsg(message);
}

//��ѯ���б����ʽ�
void TraderQueryService::QueryAllPositions(CMessage* msg)
{
	//�����������
	bool success = true;
	ReqParamer *reqParamer = new ReqParamer;
	Convert::ReadReqParamer(msg,reqParamer);
	printf("�û�%S���������ʽ�����\n",reqParamer->m_traderID.c_str());
	if(m_traderDataManager->GetTraderData(reqParamer->m_traderID) == 0)
	{
		success = false;
	}
	TraderPosition *traderPosition = m_traderDataManager->GetTraderPosition(reqParamer->m_traderID);
	success = traderPosition == 0 ? false : true;
	if(traderPosition->m_count == 0)
	{
		//���û���������DataSource��ʱ,��Ginex������û��ʽ�
		Binary binary;
		binary.WriteString(L"");
		binary.WriteString(reqParamer->m_traderID);
		//��װMessage
		CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, API_TD_POSITION, 0, 0, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
		DataCenter::GetConnectProxy()->SendMsg(message);
	}

	Binary binary;
	binary.WriteString(traderPosition->m_flag);
	binary.WriteString(traderPosition->m_traderID);
	binary.WriteInt(traderPosition->m_count);
	if(success)
	{
		vector<Position*> positions = traderPosition->m_traderPosition;
		for(vector<Position*>::iterator it = positions.begin(); it != positions.end(); ++it)
		{
			Position *position = *it;
			binary.WriteString(position->m_code);
			binary.WriteDouble(position->m_volume);
			binary.WriteDouble(position->m_frozenVolume);
		}
	}
	//��װMessage
	CMessage* message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	delete reqParamer;
	m_connectProxy->SendMsg(message);
}

//��ѯ�������ֳ�ֵ��ַ
void TraderQueryService::QueryCoinAddr(CMessage* msg)
{
	//�����������
	ReqAddrParamer *reqParamer = new ReqAddrParamer;
	Convert::ReadReqAddrParamer(msg,reqParamer);
	printf("�û�%S�������%s��ַ\n",reqParamer->m_traderID.c_str(),reqParamer->m_coinCode.c_str());
	Address *address = m_traderDataManager->GetPositionAddress(reqParamer->m_traderID, reqParamer->m_coinCode);
	Binary binary;
	CMessage* message;
	if(address != 0)
	{
		binary.WriteString(address->m_flag);
		binary.WriteString(address->m_traderID);
		binary.WriteString(address->m_coinCode);
		binary.WriteString(address->m_addr);
		binary.WriteString(address->m_memo);
	}
	else
	{
		binary.WriteString(reqParamer->m_flag);
		binary.WriteString(reqParamer->m_traderID);
		binary.WriteString(reqParamer->m_coinCode);
		binary.WriteString(L"");
		binary.WriteString(L"");
	}
	//��װMessage
	message = new CMessage(0, DATASOURCE_SERVICE_ID, msg->m_functionID, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
	m_connectProxy->SendMsg(message);
	binary.ClearBytes();

	//�������޷���ѯ����ֵ��ַʱ,���´�Ginex�л�ȡ
	if(address == 0 || address->m_addr == L"")
	{
		binary.WriteString(reqParamer->m_flag);
		binary.WriteString(reqParamer->m_traderID);
		binary.WriteString(reqParamer->m_coinCode);
		message = new CMessage(0, DATASOURCE_SERVICE_ID, API_TD_DEPOSIT, 0, msg->m_requestID, msg->m_socketID, 0, 0, binary.GetBytesLen(), (char*)binary.GetBytes());
		m_connectProxy->SendMsg(message);
	}
	
	delete reqParamer;
}

void TraderQueryService::QueryMysqlData()
{
	const char* sql2 = "select * from traderinfo";
	vector<vector<string>> rowcount;
	DataCenter::GetMysqlHelper()->QueryDatabase(sql2, rowcount);
}