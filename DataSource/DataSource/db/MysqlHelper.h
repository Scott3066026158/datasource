//
// Created by Joel on 9/4/18.
//

#ifndef GINEX_MYSQLHELPER_H
#define GINEX_MYSQLHELPER_H


#include "..\\stdafx.h"
#include "..\api\CLock.h"
#include <mysql.h>
//rows<row<fname, fvalue>>
typedef vector<map<string, string>*> MysqlHelper_Result_obj,*MysqlHelper_Result;

class MysqlHelper
{
public:
    static void FreeResultSet(MysqlHelper_Result_obj &);

public:
    MysqlHelper();
    virtual ~MysqlHelper();

public:
    bool Connect(const char *ip, int port, const char *username, const char *pwd, const char *db);

public:
    string GetName();
    unsigned long long GetLasetActiveTime();

public:
	bool CreatedbTable(const char *sql);
    int Exec(const char *sql);
    bool ExecTransaction(char **sqls, int len);
	bool InsertData(const char *sql, char *name);
	bool QueryDatabase(const char *sql, vector<vector<string>> &rowcount);
    bool Query(const char *sql,  MysqlHelper_Result ret);
private:
    CLock   m_contentLock;
    MYSQL   m_mysql;
	MYSQL   *m_sock;
    string  m_name;
    unsigned long long m_lastActiveTime;
};


#endif //GINEX_MYSQLHELPER_H
