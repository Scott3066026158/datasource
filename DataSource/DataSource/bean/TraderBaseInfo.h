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
	//�ʽ��б���
	CLock m_positionsLock;
	//�ʽ��б�
	TraderPosition *m_Positions;
	//ί���б���
	CLock m_orderInfosLock;
	//ί���б�
	map<String, OrderInfo*> m_orderInfosMap;
	//�ҵ��б���
	CLock m_openOrdersLock;
	//�ҵ��б�
	map<String, OrderInfo*> m_openOrdersMap;
	//�����б���
	CLock m_cancelOrdersLock;
	//�����б�
	map<String, CancelOrder*> m_cancelOrdersMap;
	//�ɽ��б���
	CLock m_tradeRecordsLock;
	//�ɽ��б�
	map<String, TradeRecord*> m_tradeRecordsMap;
	//���������б���
	CLock m_withdrawApplyLock;
	//���������б�
	map<String, WithdrawalApply*> m_withdrawalApplyRecordsMap;
	//��ֵ��ַ�б���
	CLock m_coinAddrLock;
	//��ֵ��ַ�б�
	map<String,Address*> m_coinAddr;
};

#endif
