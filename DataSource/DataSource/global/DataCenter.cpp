#include "..\\stdafx.h"
#include "..\\owsock\\BaseService.h"
#include "..\\config\\IPConfig.h"
#include "..\\servers\\ConnectProxy.h"
#include "DataCenter.h"


// 初始化静态对象
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

//构造函数
DataCenter::DataCenter()
{
}

//析构函数
DataCenter::~DataCenter()
{
}

//启动所有服务
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
	printf("Router线程启动!\n");
	int result = m_connectProxy->StartServer(0, 13350);
	printf("主服务启动，端口号13336!返回值%d\n",result);
	m_connectProxy->StartSendMsg();
	printf("发送消息线程启动!\n");
	return 1;
}

//获取本程序运行路径
string DataCenter::GetAppPath()
{
	return "";
}

//获取本程序运行路径
String DataCenter::GetAppPathW()
{
	return L"";
}

//获取路由器
Router* DataCenter::GetRouter()
{
	return m_router;
}

//获取连接控制器
ConnectProxy* DataCenter::GetConnectProxy()
{
	return m_connectProxy;
}

//获取查询服务
TraderQueryService* DataCenter::GetTraderQueryService()
{
	return m_traderQueryService;
}

//获取插入服务
TraderUpdateService* DataCenter::GetTraderUpdateService()
{
	return m_traderUpdateService;
}

//获取用户数据管理对象
TraderDataManager* DataCenter::GetTraderDataManager()
{
	return m_traderDataManager;
}

//获取管理数据库对象
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