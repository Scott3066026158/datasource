#pragma once
#ifndef __BusinessIDs_H__
#define __BusinessIDs_H__

#define BTSP_SERVICE_ID			55 //BTSP��ServiceID
#define GINEX_SERVICE_ID		2 //GINEX��ServiceID
#define DATASOURCE_SERVICE_ID	57 //DataSource��ServiceID

#define QRY_ALL_ORDERS		500		//��ѯ����ί��
#define QRY_ALL_TRADES		501		//��ѯ���гɽ�
#define QRY_ALL_WITHDRAWALS 502		//��ѯ��������
#define QRY_ALL_POSITIONS	503		//��ѯ���гֲ�
#define QRY_ALL_CANCEL		504		//��ѯ���г���
#define QRY_RECHARGE_ADDR	505		//��ѯ��ֵ��ַ

//����ָ��//ָ��ص�������ָ��һ��
#define API_TD_LOGIN			205  //��¼����
#define API_TD_ORDER			206  //ί������
#define API_TD_CANCEL_ORDER 	207  //��������
#define API_TD_POSITION			208  //�ʽ�����
#define API_TD_DEPOSIT			209  //��ַ����
#define API_TD_WITHDRAWAL		210  //��������

#define RTN_TD_ORDER			211		//��������ί��
#define RTN_TD_CANCEL_ORDER		212		//�������г���
#define RTN_TD_WITHDRAWAL		213		//�������г���

//������ָ֪ͨ��
#define API_TD_NOTIFY_ORDER				301 //ί�лر�
#define API_TD_NOTIFY_ORDER_DEAL		302 //�ɽ��ر�
#define API_TD_NOTIFY_ORDER_CANCEL		303 //�����ر�
#define API_TD_NOTIFY_USER_FUND			306 //�ʽ�仯�ر�
#define API_TD_NOTIFY_POSITION			307 //�ʽ�仯����(DataSource-->Client)
#define API_TD_TESTRECHAR		999			//��ֵ�ӿ�

#define SUCCESS 1 //�ɹ�
#define FAIL	0 //ʧ��

#define SERVICE_ID_MD 1 //��������ID
#define SERVICE_ID_TD 2 //���׷����ID

#define DIR_SELL				83	 //ί�з�����
#define DIR_BUY					66	 //ί�з�����


//������ָ֪ͨ��
#define API_TD_NOTIFY_ORDER				301 //ί�лر�
#define API_TD_NOTIFY_ORDER_DEAL		302 //ί�гɽ�֪ͨ
#define API_TD_NOTIFY_ORDER_CANCEL		303 //ί�г���
#define API_TD_NOTIFY_USER_LOGIN		305 //�û���¼
#define API_TD_NOTIFY_USER_FUND			306 //�û��ʽ�仯
#define API_TD_NOTIFY_USER_WITHDRAWAL	307 //�û�����ɹ�

//��ѯָ��//ָ��ص�������ָ��һ��
#define API_TD_FIND_FUNDS		402			//�ʽ�仯��¼
#define API_TD_FIND_STATUS		403			//ί��״̬
#define API_TD_FIND_ORDERS		405			//��ʷί��

#define API_TD_TESTRECHAR		999			//��ֵ�ӿ�

//ί�����
#define ORDER_TYPE_SIMPLE	1 //��ͨί��
#define ORDER_TYPE_TRY		2 //�粻��һ����ȫ�ɽ���ȫ������
#define ORDER_TYPE_NODEBRIS 3 //�粻��һ����ȫ�ɽ��򳷵����ܳɽ�����
#define ORDER_TYPE_MARKET	4 //�м۵�

// ί��״̬����
#define ORDERSTATUS_P1  1//ȫ���ҵ�
#define ORDERSTATUS_P2  2//ȫ������
#define ORDERSTATUS_P3  3//���ֳ���, ���ֳɽ�
#define ORDERSTATUS_P4  4//���ֹҵ�, ���ֳɽ�
#define ORDERSTATUS_P5  5//��ȫ�ɽ�
#define ORDERSTATUS_P6  6//�µ�ʧ��

//����ԭ��
#define CANCELORDER_REASON_USER		1 //�ͻ��˷��𳷵�
#define CANCELORDER_REASON_ORDER	2 //����ί��ʱ�ĳ����߼�
#define CANCELORDER_REASON_ADMIN	3 //����������

//�������������
#define ERROR_NOERROR				0	//û�д���
#define ERROR_PERMISSION_DENIED		1	//Ȩ�޲���
#define ERROR_INCORRECT_PASSWD		2	//�������
#define ERROR_ACCOUNT_NOTFOUND		3	//�û�������
#define ERROR_ACCOUNT_FROZEN		5	//�˻�������
#define ERROR_ACCOUNT_POOR			6	//�û��ʽ���
#define ERROR_VOLUME_INCORRECT		7	//ί�е�����������
#define ERROR_PRICE_INCORRECT		8	//ί�еļ۸񲻺���
#define ERROR_INSPECTOR_REJECT		9	//�������ܾ�
#define ERROR_CODE_NOTFOUND			10	//���벻����
#define ERROR_CODE_PUNY				11	//����̫��

//�ʽ�仯ԭ���ʶ
#define BALANCE_REASON_DEPOSIT     1	//�û�������ֵ
#define BALANCE_REASON_ADMIN       2	//admin�޸��û��ʽ�
#define BALANCE_REASON_CANCLEORDER 3	//��������
#define BALANCE_REASON_ORDERFEE    4	//ί�������ѿ۳�
#define BALANCE_REASON_ORDER       5	//ί�ж����ʲ�
#define BALANCE_REASON_WITHDRAWAL  6	//����۳�
#define BALANCE_REASON_REWARD      7	//ϵͳ����
#define BALANCE_REASON_TAKE        8	//���׳ɹ���ñ���
#define BALANCE_REASON_OTHER       9	//����,�������׷��,ͨ���жϴ��ڴ�ֵ��ʾδ֪ԭ����߷�����API�汾�ȿͻ��˸�

//����ԭ��
#define CANCEL_ORDER_SUCCESS        1   //�����ɹ�
#define CANCEL_ORDER_IDERROR       -1   //������ί��ID��ʽ����ȷ
#define CANCEL_TRADERID_NOFOUND    -2   //�������û�������
#define CANCEL_ORDRE_NOEXIST       -3   //������ί��ID������
#define CANCEL_ORDER_FINISHED      -4   //������ί��ID�ѳɽ�
#define CANCEL_EXCEPTION	       -5   //�����쳣(�ڳ����ڳɽ�֮��)

//ȫ����ϢID
#define CODE_SYS_UNKNOW_ERROR		0 	//������������δ֪��Ϣ
#define CODE_SYS_READY				1 	//����׼������,���Խ���ָ����
#define CODE_SYS_WIIL_STOPWORK		2	//���񼴽�ֹͣ����ָ��,�µ�ָ����ؾܾ���Ϣ
#define CODE_SYS_WILL_FOUT			3 	//���ӽ�Ҫǿ�жϿ�, ֮���ָ��������κδ���ͻص�
#define CODE_SYS_WIIL_SHUTDWON		4	//���񼴽�����ά���׶�,��Ϣ�и���һ����Լʱ��

#endif