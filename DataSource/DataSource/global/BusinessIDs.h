#pragma once
#ifndef __BusinessIDs_H__
#define __BusinessIDs_H__

#define BTSP_SERVICE_ID			55 //BTSP的ServiceID
#define GINEX_SERVICE_ID		2 //GINEX的ServiceID
#define DATASOURCE_SERVICE_ID	57 //DataSource的ServiceID

#define QRY_ALL_ORDERS		500		//查询所有委托
#define QRY_ALL_TRADES		501		//查询所有成交
#define QRY_ALL_WITHDRAWALS 502		//查询所有提现
#define QRY_ALL_POSITIONS	503		//查询所有持仓
#define QRY_ALL_CANCEL		504		//查询所有撤单
#define QRY_RECHARGE_ADDR	505		//查询充值地址

//基本指令//指令回调和请求指令一致
#define API_TD_LOGIN			205  //登录请求
#define API_TD_ORDER			206  //委托请求
#define API_TD_CANCEL_ORDER 	207  //撤单请求
#define API_TD_POSITION			208  //资金请求
#define API_TD_DEPOSIT			209  //地址请求
#define API_TD_WITHDRAWAL		210  //出金请求

#define RTN_TD_ORDER			211		//返回所有委托
#define RTN_TD_CANCEL_ORDER		212		//返回所有撤单
#define RTN_TD_WITHDRAWAL		213		//返回所有出金

//服务器通知指令
#define API_TD_NOTIFY_ORDER				301 //委托回报
#define API_TD_NOTIFY_ORDER_DEAL		302 //成交回报
#define API_TD_NOTIFY_ORDER_CANCEL		303 //撤单回报
#define API_TD_NOTIFY_USER_FUND			306 //资金变化回报
#define API_TD_NOTIFY_POSITION			307 //资金变化推送(DataSource-->Client)
#define API_TD_TESTRECHAR		999			//充值接口

#define SUCCESS 1 //成功
#define FAIL	0 //失败

#define SERVICE_ID_MD 1 //行情服务的ID
#define SERVICE_ID_TD 2 //交易服务的ID

#define DIR_SELL				83	 //委托方向卖
#define DIR_BUY					66	 //委托方向买


//服务器通知指令
#define API_TD_NOTIFY_ORDER				301 //委托回报
#define API_TD_NOTIFY_ORDER_DEAL		302 //委托成交通知
#define API_TD_NOTIFY_ORDER_CANCEL		303 //委托撤销
#define API_TD_NOTIFY_USER_LOGIN		305 //用户登录
#define API_TD_NOTIFY_USER_FUND			306 //用户资金变化
#define API_TD_NOTIFY_USER_WITHDRAWAL	307 //用户出金成功

//查询指令//指令回调和请求指令一致
#define API_TD_FIND_FUNDS		402			//资金变化记录
#define API_TD_FIND_STATUS		403			//委托状态
#define API_TD_FIND_ORDERS		405			//历史委托

#define API_TD_TESTRECHAR		999			//充值接口

//委托类别
#define ORDER_TYPE_SIMPLE	1 //普通委托
#define ORDER_TYPE_TRY		2 //如不能一次完全成交则全部撤单
#define ORDER_TYPE_NODEBRIS 3 //如不能一次完全成交则撤掉不能成交部分
#define ORDER_TYPE_MARKET	4 //市价单

// 委托状态代码
#define ORDERSTATUS_P1  1//全部挂单
#define ORDERSTATUS_P2  2//全部撤单
#define ORDERSTATUS_P3  3//部分撤单, 部分成交
#define ORDERSTATUS_P4  4//部分挂单, 部分成交
#define ORDERSTATUS_P5  5//完全成交
#define ORDERSTATUS_P6  6//下单失败

//撤单原因
#define CANCELORDER_REASON_USER		1 //客户端发起撤单
#define CANCELORDER_REASON_ORDER	2 //触发委托时的撤单逻辑
#define CANCELORDER_REASON_ADMIN	3 //监视器撤单

//交易所错误代码
#define ERROR_NOERROR				0	//没有错误
#define ERROR_PERMISSION_DENIED		1	//权限不足
#define ERROR_INCORRECT_PASSWD		2	//密码错误
#define ERROR_ACCOUNT_NOTFOUND		3	//用户不存在
#define ERROR_ACCOUNT_FROZEN		5	//账户被冻结
#define ERROR_ACCOUNT_POOR			6	//用户资金不足
#define ERROR_VOLUME_INCORRECT		7	//委托的手数不合理
#define ERROR_PRICE_INCORRECT		8	//委托的价格不合理
#define ERROR_INSPECTOR_REJECT		9	//监视器拒绝
#define ERROR_CODE_NOTFOUND			10	//代码不存在
#define ERROR_CODE_PUNY				11	//出金太少

//资金变化原因标识
#define BALANCE_REASON_DEPOSIT     1	//用户主动充值
#define BALANCE_REASON_ADMIN       2	//admin修改用户资金
#define BALANCE_REASON_CANCLEORDER 3	//撤单返还
#define BALANCE_REASON_ORDERFEE    4	//委托手续费扣除
#define BALANCE_REASON_ORDER       5	//委托冻结资产
#define BALANCE_REASON_WITHDRAWAL  6	//出金扣除
#define BALANCE_REASON_REWARD      7	//系统奖励
#define BALANCE_REASON_TAKE        8	//交易成功获得币种
#define BALANCE_REASON_OTHER       9	//保留,有新情况追加,通常判断大于此值表示未知原因或者服务器API版本比客户端高

//撤单原因
#define CANCEL_ORDER_SUCCESS        1   //撤单成功
#define CANCEL_ORDER_IDERROR       -1   //撤单的委托ID格式不正确
#define CANCEL_TRADERID_NOFOUND    -2   //撤单的用户不存在
#define CANCEL_ORDRE_NOEXIST       -3   //撤单的委托ID不存在
#define CANCEL_ORDER_FINISHED      -4   //撤单的委托ID已成交
#define CANCEL_EXCEPTION	       -5   //撤单异常(在撤单在成交之后)

//全局信息ID
#define CODE_SYS_UNKNOW_ERROR		0 	//服务器返回了未知消息
#define CODE_SYS_READY				1 	//服务准备就绪,可以接受指令了
#define CODE_SYS_WIIL_STOPWORK		2	//服务即将停止接收指令,新的指令将返回拒绝消息
#define CODE_SYS_WILL_FOUT			3 	//连接将要强行断开, 之后的指令将不会有任何处理和回调
#define CODE_SYS_WIIL_SHUTDWON		4	//服务即将进入维护阶段,消息中附带一个大约时间

#endif