#pragma once
#ifndef __RabbitmqProducter_H__
#define __RabbitmqProducter_H__

#include "..\\stdafx.h"
//#include "..\\global\\DataCenter.h"

class RabbitmqProducter{
public:
	char *m_queuename;
	amqp_connection_state_t rabbit_mq_connection;
	amqp_socket_t  *rabbit_mq_socket;
public:
	RabbitmqProducter(char* hostname,
        uint32_t port,
        char* user,
        char* password,
        char* queue_name);
	~RabbitmqProducter();
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool do_watch();
	void node_watcher_worker( int64_t start );

	void init_rabbit_mq (
        char* hostname,
        uint32_t port,
        char* user,
        char* password,
        char* queue_name );
	void on_amqp_error( amqp_rpc_reply_t reply, const char* context );
	void send_to_rabbit_mq(const char* data);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
#endif