//
// Created by Joel on 9/4/18.
//

#include "MysqlHelper.h"
#include "..\\api\\CStr.h"

void MysqlHelper::FreeResultSet(MysqlHelper_Result_obj &ref)
{
    MysqlHelper_Result_obj::iterator iter = ref.begin();
    while (iter != ref.end())
    {
        map<string, string> *mp = *iter;
        mp->clear();
        delete mp;
        ++iter;
    }
    ref.clear();
}

MysqlHelper::MysqlHelper()
{
	const char * host = "127.0.0.1";  //因为是作为本机测试，所以填写的是本地IP
    const char * user = "root";       //这里改为你的用户名，即连接MySQL的用户名
    const char * passwd = "root"; //这里改为你的用户密码
    const char * db = "bitamex";      //这里改为你要连接的数据库的名字
    unsigned int port = 3306;           //这是MySQL的服务器的端口，如果你没有修改过的话就是3306。
	bool isConnect = Connect(host, port, user, passwd, db);
	if(isConnect)
	{
		printf ("数据库连接成功\n");
		//Exec("DROP TABLE traderinfo");
		//Exec("CREATE TABLE traderinfo (code VARCHAR(40),transID VARCHAR(40),m_orderID VARCHAR(40),traderID VARCHAR(40),volume double,price double,m_timestamp double,direction int,isFinish int);");
	}
	else
	{
		printf ("数据库连接失败\n");
	}
    m_lastActiveTime = 0;
}

MysqlHelper::~MysqlHelper()
{
    mysql_close (&m_mysql);
    m_lastActiveTime = 0;
}

string MysqlHelper::GetName()
{
    return string(m_name);
}

unsigned long long MysqlHelper::GetLasetActiveTime()
{
    return m_lastActiveTime;
}

bool MysqlHelper::Connect(const char *ip, int port, const char *username, const char *pwd, const char *db)
{
    m_contentLock.Lock();
    mysql_init (&m_mysql);
    MYSQL *connRet = mysql_real_connect(&m_mysql, ip, username, pwd, db, (unsigned int)port, 0, 0);
    if(!connRet)
    {
        /*const char *error_msg = */mysql_error(&m_mysql);
        m_contentLock.UnLock();
        return false;
    }
    m_mysql.reconnect = 1;//auto reconnect
    //mysql_query(&m_mysql,"SET NAMES UTF8");
    m_contentLock.UnLock();
   // m_lastActiveTime = DateUtil::NowMilliseconds ();
    return true;
}

int MysqlHelper::Exec(const char *sql)
{
    m_contentLock.Lock();
    //m_lastActiveTime = DateUtil::NowMilliseconds ();
    if(mysql_query(&m_mysql, sql))
    { 
        printf ("sql error: %s\n", mysql_error (&m_mysql));
        m_contentLock.UnLock();
        return 0;
    }
    int aff_rows = (int)mysql_affected_rows(&m_mysql);
    m_contentLock.UnLock();
    return aff_rows;
}

bool MysqlHelper::ExecTransaction(char **sqls, int len)
{
    bool success = true;
    m_contentLock.Lock();
   // m_lastActiveTime = DateUtil::NowMilliseconds ();
    my_bool error = mysql_autocommit(&m_mysql, 0);
    if (!error)
    {
        for (int i = 0; i < len; ++i)
        {
            const char *sql = sqls[i];
            int isError = mysql_query(&m_mysql, sql);
            if (isError)
            {
                mysql_rollback(&m_mysql);
                success = false;
                break;
            }
        }
        if (success)
        {
            error = mysql_commit(&m_mysql);
            if (error)
            {
                success = false;
            }
        }
    }
    mysql_autocommit(&m_mysql, 1);
    m_contentLock.UnLock();
    return success;
}

bool MysqlHelper::Query(const char *sql,  MysqlHelper_Result ret)
{
    ret->clear();
    m_contentLock.Lock();
   // m_lastActiveTime = DateUtil::NowMilliseconds ();
    int ret_code = mysql_query(&m_mysql, sql);
    if(ret_code == 0)
    {
        MYSQL_RES *res = mysql_store_result(&m_mysql);
        if(res)
        {
            my_ulonglong row_count = mysql_affected_rows(&m_mysql);
            unsigned int column_count = mysql_field_count(&m_mysql);
            if(row_count > 0)
            {
                ret->reserve((int)row_count);
                for(my_ulonglong i = 0; i < row_count; ++i)
                {
                    ret->push_back(new map<string, string>);
                }
                vector<string> colNames;
                MYSQL_FIELD *file = mysql_fetch_field(res);
                while(file != 0)
                {
                    char *name = file->name;
                    colNames.push_back(name);
                    file = mysql_fetch_field(res);
                }

                int index = 0;
                MYSQL_ROW column = mysql_fetch_row(res);
                while(column)
                {
                    for(unsigned int i = 0; i < column_count; ++i)
                    {
                        ret->at(index)->insert(make_pair(colNames[i], column[i]));
                    }
                    ++index;
                    column = mysql_fetch_row(res);
                }
                colNames.clear();
            }
            mysql_free_result(res);
            m_contentLock.UnLock();
            return true;
        }
        else
        {
            /*const char *error_msg = */mysql_error(&m_mysql);
        }
    }
    else
    {
        /*const char *error_msg = */mysql_error(&m_mysql);
    }
    m_contentLock.UnLock();
    return false;
}


//判断数据库中是否存在相应表，不存在则创建表
bool MysqlHelper::CreatedbTable(const char *sql)
{
    if (0 == mysql_query(&m_mysql,sql))
    {
        return true;
    }
    return false;
}

//插入数据
bool MysqlHelper::InsertData(const char *sql, char *name)
{
	/*char buf[1024] = {0};
	sprintf(buf,"select * from %s", name);
	if(!CreatedbTable(buf))
	{
		char buf2[1024] = {0};
		sprintf(buf2,"CREATE TABLE %s (flag VARCHAR(40),traderID VARCHAR(40),errorCode int,tradePair VARCHAR(40),orderID VARCHAR(40) PRIMARY KEY,targetFee VARCHAR(40),price double,volume double,orderFee double,timestamp double,isFeeTartget int,isDealFeeDemand int,orderWay int,dir int,tradedVolume double,openedVolume double,orderState int,orderStatus VARCHAR(40));", name);
		string sql2 = buf2;
		Exec(sql2.c_str());
	}*/
	printf(sql);
	int a = mysql_query(&m_mysql, sql);
	if(a)        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(&m_mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		char buf[1024] = {0};
		sprintf(buf,"select * from %s", name);
		const char* sql2 = buf;
		vector<vector<string>> rowcount;
		QueryDatabase(sql2, rowcount);
		return true;
	}
	
}



bool MysqlHelper::QueryDatabase(const char *sql, vector<vector<string>> &rowcount)
 {
	MYSQL_ROW column;
	char *field[32];
	vector<string> fields;
    //返回0 查询成功，返回1查询失败
    if(mysql_query(&m_mysql, sql))
    {
        printf("Query failed (%s)\n",mysql_error(&m_mysql));
        return false;
    }
    else
    {
        printf("query success\n");
    }
    MYSQL_RES *res=mysql_store_result(&m_mysql);
    //打印数据行数
    //printf("number of dataline returned: %d\n",mysql_affected_rows(&m_mysql));
	MYSQL_FIELD *fd;
    for(int i=0;fd = mysql_fetch_field(res);i++)   //在已知字段数量的情况下获取字段名
    {
        field[i]=fd->name;
    }
	int col_num = mysql_num_fields(res);
    //打印获取的数据
	//column = mysql_fetch_row(res);
    while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行
    {
		for (int i = 0; i < col_num; i++) {
			fields.push_back(column[i]);
		}
		rowcount.push_back(fields);
		fields.clear();
    }
	mysql_free_result(res);
    return true;
}