#pragma once
#ifndef __CBean_H__
#define __CBean_H__

class Address
{
public:
	int errorCode;		//�������
	String m_flag;		//Ԥ���ֶ�
	String m_traderID;	//����ID
	String m_coinCode;	//���ִ���
	String m_addr;		//���ֵ�ַ
	String m_memo;		//����memo
public:
	string toString();
};

class CancelOrder
{
public:  
	String m_flag;        //flag
    String m_traderID;    //�û�ID
    String m_orderID;     //ί��ID
	String m_cancelID;	  //����ID
    int m_status;         //0 ʧ�� 1�ɹ�//���ʧ��, ���治Ҫ��ȡ
    String m_tradePair;   //���׶���
    double m_price;       //ί�м۸�
    double m_volume;      //ί������
    int m_dir;            //����
public:
	string toString();
};

class LoginInfo
{
public:
	String m_flag;			//flag
	int m_errorCode;		//������
	String m_userName;		//�û���
	String m_passWord;		//����
};

class OrderInfo
{
public:
	//���ַ��ص��ֶ�
	int 	m_errorCode;		//������� ����Ϊ0
	String 	m_tradePair;		//���׶���
	String 	m_orderID;			//����id
	String 	m_targetFee;		//��������ȡĿ��
	String 	m_flag;				//�ͻ��˱�ʶ
	String 	m_traderID;			//�û�ID
	double 	m_price;			//�۸�
	double 	m_volume;			//����
	double 	m_orderFee;			//ί��������
	double 	m_timestamp;		//ʱ���
	int 	m_isFeeTartget;		//�Ƿ���ȡ����ָ����������
	int 	m_isDealFeeDemand;	//�Ƿ���Ҫ�ɽ�����ȡ������
	int 	m_orderWay;			//ί������
	int 	m_dir;				//����
public:
	//�Զ����ֶ�
    double m_tradedVolume;  //�ѳɽ�����
    double m_openedVolume;  //�ҵ�����
    int m_orderState;		//ί��״̬
	String m_orderStatus;   //ί��״̬����
public:
	string toString();
	String getInsertSqlString();
	String GetOrderStatus(int state);
	string getUpDateSqlString(OrderInfo *order);
	void toObject(const string &orderinfo);
};

class Position 
{
public:
	String m_code;			//��Լ����
	double m_frozenVolume;	//��������
	double m_volume;		//�����ʽ�
public:
	string toString();
};

class TraderPosition
{
public:
	String m_flag;		//Ԥ���ֶ�
	String m_traderID;	//Ͷ���ߴ���
	int m_count;		//���б�������
	vector<Position*> m_traderPosition;
public:
	TraderPosition()
	{
		m_count = 0;
	}
};

class TradeRecord
{
public:
	String m_code;		//���׶���
	String m_transID;	//�ɽ�ID
	String m_orderID;	//ί��ID
	String m_traderID;	//�û�ID
	double m_volume;	//����
	double m_price;		//�۸�
	double m_timestamp;	//ʱ���
	int direction;		//����
	int m_isFinish;		//�Ƿ���ȫ�ɽ�
public:
	string toString();
public:
	string getInsertSqlString();
	string getUpDateSqlString(OrderInfo *order);
};

class WithdrawalApply
{
public:
	//���ַ��ص��ֶ�
	String m_flag;			//flag
	String m_traderID;		//�û�ID
	int	   m_errorCode;		//����ɹ�,����ʧ�� 1,0
	String m_withdrawalID;	//��ˮ��
	String m_coinCode;		//����
	String m_outAddr;		//�����ַ
	String m_memo;			//����ע
	double m_balance;		//������
	double m_fee;			//����������

	//�Զ����ֶ�
	String m_withdrawalDate; //����ʱ��(������)
    String m_withdrawalTime; //����ʱ��(ʱ����)
	String m_finishStatus;	//���ֽ�������
	double m_progress;		//���ֽ��Ȱٷֱ�
public:
	string toString();
};

class BalanceNoticeRecord
{
public:
	BalanceNoticeRecord();
	~BalanceNoticeRecord();
	//��ˮ��
	String m_notifyID;
	//�û���
	String m_traderID;
	//����
	String m_coinCode;
	//�仯�����
	double m_balance;
	//�仯�󶳽����
	double m_frozenBalance;
	//�仯ʱ��,����
	double m_timestamp;
	//�仯ԭ��(�ο� : ���ױ�ʶ�� =>�ʽ�仯����)
	int m_reason;
	//���ϴ���ȿ����ʽ�ı仯
	double m_changeBalance;
	//���ϴ���ȶ����ʽ�ı仯��
	double m_changeFrozen;
};

//��ѯ�����������
class ReqParamer
{
public:
	String m_flag;
	String m_traderID;
};

class ReqAddrParamer
{
public:
	String m_flag;
	String m_traderID;
	String m_coinCode;
};

#endif