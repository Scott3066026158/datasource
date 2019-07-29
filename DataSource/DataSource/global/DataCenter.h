#pragma once
#ifndef __DataCenter_H__
#define __DataCenter_H__

#include "..\\config\\IPConfig.h"
#include "..\\servers\\ConnectProxy.h"
#include "..\\middle\\Router.h"
#include "..\\middle\\HttpRouter.h"
#include "..\\bean\\TraderBaseInfo.h"
#include "..\\service\\TraderUpdateService.h"
#include "..\\service\\TraderQueryService.h"
#include "TraderDataManager.h"
#include "..\\db\\RedisDataManager.h"
#include "..\\db\\MysqlHelper.h"
#include "..\\rabbitmq\\RabbitmqProducter.h"
#include "..\\owsock\\HttpGetService.h"
#include "..\\owsock\\HttpPostService.h"

using namespace OwLibCT;


class DataCenter
{
public:
	// 连接控制对象
	static ConnectProxy* m_connectProxy;
	// 路由控制对象
	static Router* m_router;
	// HTTP路由控制对象
	static HttpRouter* m_httpRouter;
	//处理查询请求对象
	static TraderQueryService* m_traderQueryService;
	//处理更新数据请求对象
	static TraderUpdateService* m_traderUpdateService;
	//用户数据管理对象
	static TraderDataManager* m_traderDataManager;
	//连接数据库对象
	static RedisDataManager* m_redisDataManager;
	//
	static RedisHelper* m_redisHelper;
	//IP配置文件解析对象
	static IPConfig *m_ipConfig;
	//日志文件根路径
	static String m_logPath;
	//连接mysql对象
	static MysqlHelper* m_mysqlHelper;
	//连接Rabbitmq对象
	static RabbitmqProducter* m_rabbitmqProducter;
private:
	//HttpGet请求对象
	static HttpGetService* m_httpGetService;
	//HttpPost请求对象
	static HttpPostService* m_httpPostService;

public:
	DataCenter();
	~DataCenter();
public:
	//开始启动代理服务 0:失败 1:成功
	static int StartService();
	//获取本程序运行路径
	static string GetAppPath();
	//获取本程序运行路径
	static String GetAppPathW();

	static Router* GetRouter();
	//获取连接控制器
	static ConnectProxy* GetConnectProxy();
	//获取查询服务
	static TraderQueryService* GetTraderQueryService();
	//获取插入服务
	static TraderUpdateService* GetTraderUpdateService();
	//获取用户数据管理对象
	static TraderDataManager* GetTraderDataManager();
	//获取管理数据库
	static RedisDataManager* GetRedisDataManager();
	//获取数据库帮助类
	static RedisHelper* GetRedisHelper();
	//获取IPConfig
	static IPConfig* GetIPConfig();
	//获取mysql数据库连接对象
	static MysqlHelper* GetMysqlHelper();
	//获取rabbitmq连接对象
	static RabbitmqProducter* GetRabbitmqProducter();
	//获取HttpGet请求对象
	static HttpGetService* GetHttpGetService();
	//获取HttpPost请求对象
	static HttpPostService* GetHttpPostService();
};
#endif