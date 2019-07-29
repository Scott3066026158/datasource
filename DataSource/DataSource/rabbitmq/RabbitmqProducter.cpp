#include "RabbitmqProducter.h"
//#include "..\\global\\DataCenter.h"


RabbitmqProducter::RabbitmqProducter(char* hostname,
        uint32_t port,
        char* user,
        char* password,
        char* queue_name)
{
	init_rabbit_mq(hostname,port,user,password,queue_name);
}

RabbitmqProducter::~RabbitmqProducter()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RabbitmqProducter::init_rabbit_mq (
        char* hostname,
        uint32_t port,
        char* user,
        char* password,
        char* queue_name)
{
	m_queuename = queue_name;
    rabbit_mq_connection = amqp_new_connection();
    rabbit_mq_socket = amqp_tcp_socket_new(rabbit_mq_connection);
    if(!rabbit_mq_socket) {
        cout << "failed creating rabbitmq socket";
    }

    auto status = amqp_socket_open(rabbit_mq_socket, "192.168.86.128", port);
    if(status != AMQP_STATUS_OK) {
       cout << "failed opening connection socket";
    }

    auto reply = amqp_login(rabbit_mq_connection, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user, password);
    on_amqp_error(reply, "login");

    amqp_channel_open(rabbit_mq_connection, 1);
    reply = amqp_get_rpc_reply(rabbit_mq_connection);
    on_amqp_error(reply, "Opening channel");
	amqp_queue_declare(rabbit_mq_connection,1,amqp_cstring_bytes(queue_name),0,1,0,0,amqp_empty_table);
    /*amqp_exchange_declare(rabbit_mq_connection, 1,
            amqp_cstring_bytes(exchange_name), amqp_cstring_bytes(exchange_type),
            0, 1, 0, 0, amqp_empty_table);*/
}

void RabbitmqProducter::send_to_rabbit_mq(const char* data)
{
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("application/json");
    props.delivery_mode = 2; /* persistent delivery mode */

    auto res = amqp_basic_publish( rabbit_mq_connection, 1,
									amqp_cstring_bytes(""),
                                   amqp_cstring_bytes(m_queuename), false, false,
                                   &props,
                                   amqp_cstring_bytes(data) );
    if(res != AMQP_STATUS_OK) {
        cout << "publish block json to rabbitMQ error:" << res;
    }
}

void RabbitmqProducter::on_amqp_error( amqp_rpc_reply_t reply, const char* context )
{
    switch (reply.reply_type)
    {
        case AMQP_RESPONSE_NORMAL:
            return;
        case AMQP_RESPONSE_NONE:
            cout << context << ":" << "missing RPC reply type!";
            break;
        case AMQP_RESPONSE_LIBRARY_EXCEPTION:
            cout << context << ":" << amqp_error_string2(reply.library_error);
            break;
        case AMQP_RESPONSE_SERVER_EXCEPTION:
            switch (reply.reply.id)
            {
                case AMQP_CONNECTION_CLOSE_METHOD:
                {
                    auto *m = (amqp_connection_close_t *)reply.reply.decoded;
                    fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
                            context, m->reply_code, (int)m->reply_text.len,
                            (char *)m->reply_text.bytes);
                    break;
                }
                case AMQP_CHANNEL_CLOSE_METHOD:
                {
                    auto *m = (amqp_channel_close_t *)reply.reply.decoded;
                    fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
                            context, m->reply_code, (int)m->reply_text.len,
                            (char *)m->reply_text.bytes);
                    break;
                }
                default:
                    fprintf(stderr, "%s: unknown server error, method id 0x%08X\n",
                            context, reply.reply.id);
            }
            break;
    }
}