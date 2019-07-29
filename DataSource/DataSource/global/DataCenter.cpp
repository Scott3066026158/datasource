#include "..\\stdafx.h"
#include "..\\owsock\\BaseService.h"
#include "..\\config\\IPConfig.h"
#include "..\\servers\\ConnectProxy.h"
#include "DataCenter.h"


// ��ʼ����̬����
ConnectProxy *DataCenter::m_connectProxy = 0;
Router *DataCenter::m_router = 0;
HttpRouter *DataCenter::m_httpRouter = 0;
TraderQueryService *DataCenter::m_traderQueryService = 0;
TraderUpdateService *DataCenter::m_traderUpdateService = 0;
TraderDataManager *DataCenter::m_traderDataManager = 0;
IPConfig *DataCenter::m_ipConfig = 0;
String DataCenter::m_logPath = L"";

RedisDataManager* DataCenter::m_redisDataManager = 0;
RedisHelper* DataCenter::m_redisHelper = 0;
MysqlHelper* DataCenter::m_mysqlHelper = 0;
RabbitmqProducter* DataCenter::m_rabbitmqProducter = 0;
HttpGetService* DataCenter::m_httpGetService = 0;
HttpPostService* DataCenter::m_httpPostService = 0;

//���캯��
DataCenter::DataCenter()
{
}

//��������
DataCenter::~DataCenter()
{
}

//�������з���
int DataCenter::StartService()
{
	m_logPath =  DataCenter::GetAppPathW() + L"\\MyLog\\";
	m_traderDataManager = new TraderDataManager();
	m_connectProxy = new ConnectProxy();
	m_ipConfig = new IPConfig();
	
	m_httpGetService = new HttpGetService();
	m_httpPostService = new HttpPostService();
	printf(m_ipConfig->GetPrintString().c_str());
	m_traderQueryService = new TraderQueryService();
	m_traderUpdateService = new TraderUpdateService();
	m_redisHelper = new RedisHelper();
	m_redisDataManager = new RedisDataManager(m_redisHelper);
	m_mysqlHelper = new MysqlHelper();
	m_rabbitmqProducter = new RabbitmqProducter("/",5673,"guest","guest","orderInfos");
	BaseService::AddService(m_connectProxy);
	m_router = new Router();
	m_httpRouter = new HttpRouter();
	printf("Router�߳�����!\n");
	int result = m_connectProxy->StartServer(0, 13350);
	printf("�������������˿ں�13336!����ֵ%d\n",result);
	m_connectProxy->StartSendMsg();
	printf("������Ϣ�߳�����!\n");
	return 1;
}

//��ȡ����������·��
string DataCenter::GetAppPath()
{
	return "";
}

//��ȡ����������·��
String DataCenter::GetAppPathW()
{
	return L"";
}

//��ȡ·����
Router* DataCenter::GetRouter()
{
	return m_router;
}

//��ȡ���ӿ�����
ConnectProxy* DataCenter::GetConnectProxy()
{
	return m_connectProxy;
}

//��ȡ��ѯ����
TraderQueryService* DataCenter::GetTraderQueryService()
{
	return m_traderQueryService;
}

//��ȡ�������
TraderUpdateService* DataCenter::GetTraderUpdateService()
{
	return m_traderUpdateService;
}

//��ȡ�û����ݹ������
TraderDataManager* DataCenter::GetTraderDataManager()
{
	return m_traderDataManager;
}

//��ȡ�������ݿ����
RedisDataManager* DataCenter::GetRedisDataManager()
{
	return m_redisDataManager;
}

RedisHelper* DataCenter::GetRedisHelper()
{
	return m_redisHelper;
}

IPConfig* DataCenter::GetIPConfig()
{
	return m_ipConfig;
}

MysqlHelper* DataCenter::GetMysqlHelper()
{
	return m_mysqlHelper;
}

RabbitmqProducter* DataCenter::GetRabbitmqProducter()
{
	return m_rabbitmqProducter;
}

HttpGetService* DataCenter::GetHttpGetService()
{
	return m_httpGetService;
}

HttpPostService* DataCenter::GetHttpPostService()
{
	return m_httpPostService;
}