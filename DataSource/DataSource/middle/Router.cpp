#include "..\\stdafx.h"
#include "..\\global\\DataCenter.h"
#include "..\\global\\BusinessIDs.h"
#include "Router.h"

Router::Router()
{
	//����������Ϣ�߳�
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
			//�û���¼
			case API_TD_LOGIN:
				DataCenter::GetTraderDataManager()->TraderLogin(msg);
				break;
			// ��ѯ����ί��
			case QRY_ALL_ORDERS:
				traderQueryService->QueryAllOrders(msg);
				break;
			// ��ѯ���гɽ�
			case QRY_ALL_TRADES:
				traderQueryService->QueryAllTrades(msg);
				break;
			// ��ѯ�������ּ�¼
			case QRY_ALL_WITHDRAWALS:
				traderQueryService->QueryAllWithdrawals(msg);
				break;
			// ��ѯ���б����ʽ�
			case QRY_ALL_POSITIONS:
				traderQueryService->QueryAllPositions(msg);
				break;
			// ��ѯ�������ֳ�ֵ��ַ
			case QRY_RECHARGE_ADDR:
				traderQueryService->QueryCoinAddr(msg);
				break;
			// ί�лر�������ί������
			case API_TD_ORDER:
				traderUpdateService->InsertOrder(msg);
				break;
			// �����ر�����������
			case API_TD_CANCEL_ORDER:
				traderUpdateService->InsertCancel(msg);
				break;
			// �ʽ�ر�����������
			case API_TD_POSITION:
				traderUpdateService->InsertPosition(msg);
				break;
			// ��ַ�ر�����������
			case API_TD_DEPOSIT:
				traderUpdateService->InsertAddr(msg);
				break;
			// ��������ر�����������
			case API_TD_WITHDRAWAL:
				traderUpdateService->InsertWithdrawalApply(msg);
				break;
			// �ɽ��ر�����������
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

