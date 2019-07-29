#ifndef _RabbitmqCustomer_H
#define _RabbitmqCustomer_H
 
#include "amqp.h"
 
class RabbitmqCustomer
{
public:
    RabbitmqCustomer(const char* hostname, const int port, const char* user, const char* pwd, 
    const char* queuename);
    bool ConnectRabbitmq();
    bool StartConsumer(char *name);
    void CloseConnect();
private:
    amqp_connection_state_t conn;
    char m_hostname[128];
    int  m_port;
    char m_user[128];
    char m_pwd[128];
    char m_vhost[128];
    char m_queuename[128];
};
 
#endif
