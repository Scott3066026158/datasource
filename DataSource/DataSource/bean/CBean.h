#pragma once
#ifndef __CBean_H__
#define __CBean_H__

class Address
{
public:
	int errorCode;		//错误代码
	String m_flag;		//预留字段
	String m_traderID;	//交易ID
	String m_coinCode;	//币种代码
	String m_addr;		//币种地址
	String m_memo;		//币种memo
public:
	string toString();
};

class CancelOrder
{
public:  
	String m_flag;        //flag
    String m_traderID;    //用户ID
    String m_orderID;     //委托ID
	String m_cancelID;	  //撤单ID
    int m_status;         //0 失败 1成功//如果失败, 后面不要读取
    String m_tradePair;   //交易对子
    double m_price;       //委托价格
    double m_volume;      //委托手数
    int m_dir;            //方向
public:
	string toString();
};

class LoginInfo
{
public:
	String m_flag;			//flag
	int m_errorCode;		//错误码
	String m_userName;		//用户名
	String m_passWord;		//密码
};

class OrderInfo
{
public:
	//周林返回的字段
	int 	m_errorCode;		//错误代码 不错为0
	String 	m_tradePair;		//交易对子
	String 	m_orderID;			//订单id
	String 	m_targetFee;		//手续费收取目标
	String 	m_flag;				//客户端标识
	String 	m_traderID;			//用户ID
	double 	m_price;			//价格
	double 	m_volume;			//手数
	double 	m_orderFee;			//委托手续费
	double 	m_timestamp;		//时间戳
	int 	m_isFeeTartget;		//是否收取额外指定的手续费
	int 	m_isDealFeeDemand;	//是否需要成交后收取手续费
	int 	m_orderWay;			//委托类型
	int 	m_dir;				//方向
public:
	//自定义字段
    double m_tradedVolume;  //已成交数量
    double m_openedVolume;  //挂单数量
    int m_orderState;		//委托状态
	String m_orderStatus;   //委托状态描述
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
	String m_code;			//合约代码
	double m_frozenVolume;	//冻结手数
	double m_volume;		//可用资金
public:
	string toString();
};

class TraderPosition
{
public:
	String m_flag;		//预留字段
	String m_traderID;	//投资者代码
	int m_count;		//持有币种数量
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
	String m_code;		//交易对子
	String m_transID;	//成交ID
	String m_orderID;	//委托ID
	String m_traderID;	//用户ID
	double m_volume;	//数量
	double m_price;		//价格
	double m_timestamp;	//时间戳
	int direction;		//方向
	int m_isFinish;		//是否完全成交
public:
	string toString();
public:
	string getInsertSqlString();
	string getUpDateSqlString(OrderInfo *order);
};

class WithdrawalApply
{
public:
	//周林返回的字段
	String m_flag;			//flag
	String m_traderID;		//用户ID
	int	   m_errorCode;		//申请成功,申请失败 1,0
	String m_withdrawalID;	//流水号
	String m_coinCode;		//币种
	String m_outAddr;		//出金地址
	String m_memo;			//出金备注
	double m_balance;		//出金金额
	double m_fee;			//出金手续费

	//自定义字段
	String m_withdrawalDate; //提现时间(年月日)
    String m_withdrawalTime; //提现时间(时分秒)
	String m_finishStatus;	//提现进度描述
	double m_progress;		//提现进度百分比
public:
	string toString();
};

class BalanceNoticeRecord
{
public:
	BalanceNoticeRecord();
	~BalanceNoticeRecord();
	//流水号
	String m_notifyID;
	//用户名
	String m_traderID;
	//币种
	String m_coinCode;
	//变化后余额
	double m_balance;
	//变化后冻结余额
	double m_frozenBalance;
	//变化时间,毫秒
	double m_timestamp;
	//变化原因(参考 : 交易标识符 =>资金变化类型)
	int m_reason;
	//与上次相比可用资金的变化
	double m_changeBalance;
	//与上次相比冻结资金的变化量
	double m_changeFrozen;
};

//查询请求参数对象
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