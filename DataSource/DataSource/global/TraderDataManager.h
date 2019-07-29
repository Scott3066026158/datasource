#pragma once
#ifndef __TraderDataManager_H__
#define __TraderDataManager_H__

#include "..\\owsock\\CMessage.h"
#include "..\\bean\\CBean.h"
#include "..\\bean\\TraderBaseInfo.h"

class TraderDataManager
{
private:
	// �����û��Ľ�������
	map<String, TraderBaseInfo*> m_traderInfoMap;
	CLock m_traderInfoMapLock;
public:
	// ���캯��
	TraderDataManager();
	// ��������
	~TraderDataManager();
public:
	//�û���¼
	void TraderLogin(CMessage* msg);
	// ����TraderID��ȡ�û�����������
	TraderBaseInfo* GetTraderData(String traderID);

	// ����TraderID��ȡ�û�������ί��
	void GetTraderAllOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap);

	// ����TraderID��ȡ�û������гֲ�
	TraderPosition* GetTraderPosition(String traderID);

	// ����TraderID��ȡָ�����ֵĳֲ���Ϣ
	Position* GetPositionByCode(String traderID, String coinCode);

	// ����TraderID��ȡ�û������йҵ�
	void GetTraderOrderInfo(String traderID, map<String, OrderInfo*> &orderInfoMap);

	// ����TraderID��ȡ�û������г���
	void GetTraderCancelOrder(String traderID, map<String, CancelOrder*> &cancelOrderMap);

	// ����TraderID��ȡ�û������гɽ�����
	void GetTradeRecord(String traderID, map<String, TradeRecord*> &tradeRecordMap);

	// ����TraderID��ȡ�û����������������б�
	void GetWithdrawalApplyRecords(String traderID, map<String, WithdrawalApply*> &withdrawalApplyMap);

	// ����TraderID��ȡ�û����ֶ�Ӧ��ֵ��ַ�б�
	Address* GetPositionAddress(String traderID, String coinCode);

	//����OrderID����ί�лر�����
	//bool FindOrderInfoBySysID(LPDatas *lp, const String &traderID, const String &sysID, CoinOrder *order);

	//�����û���������
	void InsertTraderOrderInfo(OrderInfo *orderInfo);
	//�����û�������¼
	void InsertTraderCancel(CancelOrder *cancelOrder);
	//�����û������ʽ�����
	void InsertTraderPosition(TraderPosition *traderPosition);
	//�����û����ֵ�ַ
	void InsertTraderAddress(Address *address);
	//������������
	void InsertTraderWithdrawalApply(WithdrawalApply *withdrawalApply);
	//����ɽ���¼
	void InsertTraderRecord(TradeRecord *tradeRecord);
	//�ɽ��������Ӧ��ί�ж���
	void UpdateOrderInfo(TradeRecord *tradeRecord, int socketID);
	//�����������Ӧ��ί�ж���
	void UpdateOrderInfo(CancelOrder *cancelOrder, int socketID);
	//���仯���ί�����ݷ��͵�Client
	void SendMsgToClient(OrderInfo *orderInfo, int socketID);
	//�û��ʽ����
	void UpdateTraderPosition(String traderId, Position position, int socketID);
};
	

#endif