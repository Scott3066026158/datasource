#include "..\\stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
 
#include "amqp_tcp_socket.h"
#include "amqp.h"
#include "amqp_framing.h"
#include "RabbitmqCustomer.h"
#include "..\\global\\DataCenter.h"
 
/*
* 构造函数
* hostname,port,user,pwd,vhost
*/

RabbitmqCustomer::RabbitmqCustomer(const char* hostname, const int port, const char* user, 
const char* pwd, const char* queuename)
{
    if((hostname != NULL) || (port != 0) || (user != NULL) 
    || (pwd != NULL) || (queuename != NULL))
    {
        strcpy(this->m_hostname, hostname);
        this->m_port = port;
        strcpy(this->m_user, user);
        strcpy(this->m_pwd, pwd);
        strcpy(this->m_queuename, queuename);
    }
}
 
bool RabbitmqCustomer::ConnectRabbitmq()
{
    amqp_socket_t *socket ;
    amqp_rpc_reply_t reply ;
    int status;
 
    conn = amqp_new_connection();
    socket = amqp_tcp_socket_new(conn);
    if(!socket)
    {
        printf("amqp new socket error\n");
        return 0;
    }
    status = amqp_socket_open(socket, m_hostname, m_port);
    if(status)
    {
        printf("amqp open socket error\n");
        return 0;
    }
    reply = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, m_user, m_pwd);
    if (reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION)
    {
        printf("amqp login error\n");
        return 0;
    }
    amqp_channel_open(conn, 1);
    reply = amqp_get_rpc_reply(conn);
    if(reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION)
    {
        printf("ConnectRabbitmq::amqp get rpc_reply error\n");
        return 0;
    }
}
 
bool RabbitmqCustomer::StartConsumer(char *name)
{
    amqp_rpc_reply_t reply ;
    //自动回复ACK
    amqp_basic_consume(conn, 1, amqp_cstring_bytes(m_queuename), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    reply = amqp_get_rpc_reply(conn);
    if(reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION)
    {
        printf("StartConsumer::amqp get rpc_reply error\n");
        return false;
    }
    {
        for (;;) 
        {
            amqp_rpc_reply_t res;
            amqp_envelope_t envelope;
 
            amqp_maybe_release_buffers(conn);
			printf("5200");
            res = amqp_consume_message(conn, &envelope, NULL, 0);
			printf("5201");
            if (AMQP_RESPONSE_NORMAL != res.reply_type) { 
                break;
            }
 
            printf("Delivery %u, exchange %.*s routingkey %.*s\n",
                    (unsigned) envelope.delivery_tag,
                    (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
                    (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);
 
            if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
                printf("Content-type: %.*s\n",
                    (int) envelope.message.properties.content_type.len,
                    (char *) envelope.message.properties.content_type.bytes);
            }
            printf("----\n");
 
            //amqp_dump(envelope.message.body.bytes, envelope.message.body.len);
                 printf("Content %.*s\n",
                    (int) envelope.message.body.len,
                    (char *) envelope.message.body.bytes);
	
			size_t size = (size_t)(envelope.message.body.len);
			string result((char*)(envelope.message.body.bytes), size);

			DataCenter::GetMysqlHelper()->InsertData(result.c_str(), name);
            amqp_destroy_envelope(&envelope);
        }
    }
}
 
void RabbitmqCustomer::CloseConnect()
{
    amqp_rpc_reply_t reply ;
    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
}

