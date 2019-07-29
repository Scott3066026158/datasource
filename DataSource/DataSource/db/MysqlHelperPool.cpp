//
// Created by Joel on 9/4/18.
//

#include "MysqlHelperPool.h"

#include "..\\stdafx.h"

MysqlHelperPool::MysqlHelperPool()
{

}

MysqlHelperPool::~MysqlHelperPool()
{
    m_idleHelpersLock.Lock();
    vector<MysqlHelperInfo*>::iterator iter = m_idleHelpers.begin();
    while(iter != m_idleHelpers.end())
    {
        FreeHsInfo(*iter);
        ++iter;
    }
    m_idleHelpers.clear();
    m_idleHelpersLock.UnLock();
}

int MysqlHelperPool::Init(const MysqlPoolInitOptions &options)
{
    m_options = new MysqlPoolInitOptions(options);

    if(m_options->maxSize <= 0 &&
        m_options->minSize <= 0 &&
        m_options->increaseStep <=0 &&
        m_options->port <= 0 &&
        m_options->maxWaitingSize <= 0)
    {
        return false;
    }

    MysqlHelper *temp0 = new MysqlHelper();

    if(temp0->Connect(m_options->ip.c_str (),
                      m_options->port,
                      m_options->username.c_str (),
                      m_options->passwd.c_str (),
                      m_options->db.c_str ()))
    {
        MysqlHelperInfo *info = new MysqlHelperInfo;
        info->m_helper = temp0;
        info->m_working = false;
        m_idleHelpers.push_back(info);
        //
        int iSize = m_options->minSize - 1;
        for(int i = 0; i < iSize; ++i)
        {
            MysqlHelper *temp = new MysqlHelper();
            if(temp->Connect(m_options->ip.c_str (),
                             m_options->port,
                             m_options->username.c_str (),
                             m_options->passwd.c_str (),
                             m_options->db.c_str ()))
            {
                MysqlHelperInfo *temp1 = new MysqlHelperInfo;
                temp1->m_helper = temp;
                temp1->m_working = false;
                m_idleHelpers.push_back(temp1);
            }
        }
    }

    return (int)m_idleHelpers.size();
}

MysqlHelper* MysqlHelperPool::Increase()
{
    size_t totalAlloctedSize = m_idleHelpers.size() + m_busyHelpers.size ();
    int incrStep = m_options->increaseStep;
    size_t incrSize = 0;
    int sizeOfIncred = totalAlloctedSize + incrStep;

    if(sizeOfIncred <= m_options->maxSize)
    {
        incrSize = incrStep;
    }
    else
    {
        incrSize = m_options->maxSize - totalAlloctedSize;
    }

    size_t successedSize = 0;
    for(size_t i = 0; i < incrSize; ++i)
    {
        MysqlHelper *temp = new MysqlHelper();
        if(temp->Connect(m_options->ip.c_str (),
                         m_options->port,
                         m_options->username.c_str (),
                         m_options->passwd.c_str (),
                         m_options->db.c_str ()))
        {
            ++successedSize;
            MysqlHelperInfo *temp1 = new MysqlHelperInfo;
            temp1->m_helper = temp;
            temp1->m_working = false;
            m_idleHelpers.push_back(temp1);
        }
        else
        {
            break;
        }
    }
    if(successedSize > 0)
    {
        MysqlHelperInfo *result = m_idleHelpers[m_idleHelpers.size() - 1];
        m_idleHelpers.pop_back ();
        result->m_working = true;
        m_busyHelpers.push_back (result);
        return result->m_helper;
    }
    return 0;
}

MysqlHelper *MysqlHelperPool::GetHelper(bool waiting/* = true*/, unsigned long timout/* = INFINITE*/)
{
    MysqlHelper *helper = 0;
   /* m_idleHelpersLock.Lock();
    vector<MysqlHelperInfo*>::iterator iter = m_idleHelpers.begin ();
    while (iter != m_idleHelpers.end())
    {
        MysqlHelperInfo *info = *iter;
        if(!(info->m_working))
        {
            iter = m_idleHelpers.erase (iter);
            MysqlHelper *mysqlHelper = info->m_helper;
            unsigned long long lastActiveTime = mysqlHelper->GetLasetActiveTime ();
            unsigned long long now = DateUtil::NowMilliseconds ();
            if((now - lastActiveTime) >= MYSQL_MAX_ACTIVE_LIMIT)
            {
                FreeHsInfo(info);
                continue;
            }

            m_busyHelpersLock.Lock ();
            m_busyHelpers.push_back (info);
            m_busyHelpersLock.UnLock ();

            helper = info->m_helper;
            info->m_working = true;
        }
        break;
    }
    if(!helper)
    {
        helper = Increase();
    }
    m_idleHelpersLock.UnLock();
    if(!helper && waiting && timout > 0)
    {
        MysqlHelperInfo *info = 0;
        if(m_waitLock.WaitLock (timout))
        {
            unsigned long wt = 0;
            while(true)
            {
                Sleep (1);
                m_idleHelpersLock.Lock ();
                if(!m_idleHelpers.empty ())
                {
                    info = m_idleHelpers[m_idleHelpers.size () - 1];
                    m_idleHelpers.pop_back ();
                }
                m_idleHelpersLock.UnLock ();
                if(info)
                {
                    break;
                }
                ++wt;
                if(wt == timout)
                {
                    break;
                }
            }
            m_waitLock.UnLock ();
        }
        if(info)
        {
            info->m_working = true;
            m_busyHelpersLock.Lock ();
            m_busyHelpers.push_back (info);
            m_busyHelpersLock.UnLock ();
            helper = info->m_helper;
        }
    }*/
    return helper;
}

void MysqlHelperPool::ReleaseHelper(MysqlHelper *ptr)
{
    if(ptr)
    {
        MysqlHelperInfo *busyInfo = 0;
        m_busyHelpersLock.Lock();
        vector<MysqlHelperInfo*>::iterator iter = m_busyHelpers.begin();
        while(iter != m_busyHelpers.end())
        {
            MysqlHelperInfo *info = *iter;
            if(info->m_helper->GetName() == ptr->GetName())
            {
                info->m_working = false;
                m_busyHelpers.erase (iter);
                busyInfo = info;
                break;
            }
            ++iter;
        }
        m_busyHelpersLock.UnLock();

        if(busyInfo)
        {
            m_idleHelpersLock.Lock ();
            m_idleHelpers.push_back (busyInfo);
            m_idleHelpersLock.UnLock ();
        }
    }
}