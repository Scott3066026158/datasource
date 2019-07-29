//
// Created by Joel on 9/4/18.
//

#ifndef GINEX_MYSQLHELPERPOOL_H
#define GINEX_MYSQLHELPERPOOL_H

#include "MysqlHelper.h"

#include "..\\stdafx.h"

//In general, the connection expiration time of mysql is 8 hours
//but here the expiration time is set to 1 hour for security and resource allocation.
// eight hour of ms hex is 0x1b77400
// an hour of ms hex is 0x36ee80
#define MYSQL_MAX_ACTIVE_LIMIT 0x36ee80

struct _mysqlPoolOptions
{
    string ip;
    string username;
    string passwd;
    string db;
    int port;
    int minSize;
    int maxSize;
    int maxWaitingSize;
    int increaseStep;

    _mysqlPoolOptions()
    {
        // this code generated by GinTechCoin Auto Coder
        // don't modify them
        port = 0;
        minSize = 0;
        maxSize = 0;
        maxWaitingSize = 0;
        increaseStep = 0;
    }

    _mysqlPoolOptions(const _mysqlPoolOptions& in)
    {
        // this code generated by GinTechCoin Auto Coder
        // don't modify them
        ip = in.ip;
        username = in.username;
        passwd = in.passwd;
        db = in.db;
        port = in.port;
        minSize = in.minSize;
        maxSize = in.maxSize;
        maxWaitingSize = in.maxWaitingSize;
        increaseStep = in.increaseStep;
    }

};

typedef  _mysqlPoolOptions MysqlPoolInitOptions;

class MysqlHelperPool
{
    typedef struct
    {
        MysqlHelper *m_helper;
        bool m_working;
    }MysqlHelperInfo;

    inline void FreeHsInfo(MysqlHelperInfo *info)
    {
        delete (info->m_helper);
        delete (info);
        info = 0;
    }

public:
    MysqlHelperPool();
    ~MysqlHelperPool();

public:
    int             Init(const MysqlPoolInitOptions &options);
    MysqlHelper     *GetHelper(bool waiting = true, unsigned long timout = 0);
    void            ReleaseHelper(MysqlHelper *);

private:
    MysqlHelper* Increase();

private:
    //the helers currently in use
    vector<MysqlHelperInfo*> m_busyHelpers;
    CLock m_busyHelpersLock;

    //helpers watting for use
    vector<MysqlHelperInfo*> m_idleHelpers;
    CLock m_idleHelpersLock;

private:
    MysqlPoolInitOptions *m_options;
    CLock m_waitLock;
};


#endif //GINEX_MYSQLHELPERPOOL_H
