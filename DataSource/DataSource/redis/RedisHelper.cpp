#include <vector>
#include <map>
#include <stdlib.h>
#include <stdio.h>

#include "win32fixes.h"
//#include "../redis/fmacros.h"
#include "hiredis.h"

#include "RedisHelper.h"

using namespace std;


bool RegistSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return false;
	}
	return true;
}

RedisHelper::RedisHelper()
{
	m_context = 0;
	::InitializeCriticalSection(&cs);
}

RedisHelper::~RedisHelper()
{
	if (m_context)
	{
		redisFree((redisContext*)m_context);
	}
	::LeaveCriticalSection(&cs);
}

int RedisHelper::Init(const char *ip, int port, const char *auth)
{
	//============================================
	//这个注册一定要加上
	//如果在这代码执行之前没有启动过socket
	//那么redis内部连接的时候总是返回socket error
	if(!RegistSocket()){return -999;}
	//============================================

	if (m_context)
	{
		redisFree(m_context);
	}
	struct timeval t = { 1, 500000 };
	//
	int status = 1;
	redisContext *temp0 = redisConnectWithTimeout(ip, port, t);
	if (temp0)
	{
		if (temp0->err == 0)
		{
			if (auth)
			{
				void *rpy = redisCommand(temp0, "AUTH %s", auth);
				if (rpy)
				{
					redisReply *reply_redis = (redisReply*)rpy;
					if (reply_redis->type != REDIS_REPLY_STATUS || reply_redis->len != 2)
					{
						status = -1;
					}
					freeReplyObject(rpy);
				}
				else
				{
					status = -2;
				}
			}
		}
		else
		{
			status = -3;
		}
	}
	else
	{
		return -4;
	}
	if (status == 1)
	{
		m_context = temp0;
	}
	else
	{
		redisFree(temp0);
	}
	return status;
}

int RedisHelper::SetValue(const char *key, const char *val)
{
	void *reply_void = redisCommand(m_context, "SET %s %s", key, val);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			return 1;
		}
	}
	return 0;
}

int RedisHelper::SetValueU(const char * key, const unsigned char *val)
{
	void *reply_void = redisCommand(m_context, "SET %s %s", key, val);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			return 1;
		}
	}
	return 0;
}

int RedisHelper::SetIntValue(const char *key, int val)
{
	char buf[1024] = {0};
	std::sprintf(buf,"%d",val);
	void *reply_void = redisCommand(m_context, "SET %s %s", key, buf);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			freeReplyObject(reply_void);
			return 1;
		}
		freeReplyObject(reply_void);
	}
	return 0;
}

int RedisHelper::SetDoubleValue(const char *key, double val)
{
	char buf[1024] = {0};
	std::sprintf(buf,"%f",val);
	void *reply_void = redisCommand(m_context, "SET %s %s", key, buf);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			freeReplyObject(reply_void);
			return 1;
		}
		freeReplyObject(reply_void);
	}
	return 0;
}

//设置hashTable对应key值的value
int RedisHelper::SetHashString(const char* hash_name, const char *key, const char *val)
{
	::EnterCriticalSection(&cs);
	void *reply_void = redisCommand(m_context, "HSET %s %s %s", hash_name, key, val);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			freeReplyObject(reply_void);
			::LeaveCriticalSection(&cs);
			return 1;
		}
		freeReplyObject(reply_void);
	}
	::LeaveCriticalSection(&cs);
	return 0;
}

int RedisHelper::DeleteHashString(const char* hash_name, const char *key)
{
	::EnterCriticalSection(&cs);
	void *reply_void = redisCommand(m_context, "HDEL %s %s", hash_name, key);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		if (reply_redis->type != REDIS_REPLY_ERROR)
		{
			freeReplyObject(reply_void);
			::LeaveCriticalSection(&cs);
			return 1;
		}
		freeReplyObject(reply_void);
	}
	::LeaveCriticalSection(&cs);
	return 0;
}

int RedisHelper::GetValue(const char *key, string *ref)
{
	void *reply_void = redisCommand(m_context, "GET %s", key);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_STRING)
		{
			*ref = reply_redis->str;
			status = 1;
		}
		else if (retType == REDIS_REPLY_INTEGER)
		{
			char temp0[50] = { '\0' };
			//linux %lld
			//win32 %I64d
			sprintf_s(temp0, 49, "%I64d", reply_redis->integer);
			*ref = temp0;
			status = 2;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		return status;
	}
	return 0;
}

int RedisHelper::GetIntValue(const char *key, int *ref)
{
	void *reply_void = redisCommand(m_context, "GET %s", key);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_INTEGER)
		{
			*ref = (int)reply_redis->integer;
			status = 1;
		}
		else if (retType == REDIS_REPLY_STRING)
		{
			*ref = atoi(reply_redis->str);
			status = 2;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		return status;
	}
	return 0;
}

int RedisHelper::GetDoubleValue(const char *key, double *ref)
{
	void *reply_void = redisCommand(m_context, "GET %s", key);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_STRING)
		{
			*ref = atof(reply_redis->str);
			status = 1;
		}
		else if (retType == REDIS_REPLY_INTEGER)
		{
			*ref = (double)reply_redis->integer;
			status = 2;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		return status;
	}
	return 0;
}

/*int RedisHelper::GetValueByHashAndKey(onst char* hash_name, onst char* key, const string *value)
{
	vector<string> keys;
	GetHashTableKey(hash_name, &keys);
	int size = keys.size();
	if(size > 0)
	{
		
	}
	string mykey;
	for(keys)
	{
		mykey = "";
	}
	GetHashStringValue(hash_name, mykey.c_str(), value)
	return state;
}*/
//查询指定hash表中所有的key
int RedisHelper::GetHashTableKey(const char* hash_name, vector<string> *ref)
{
	void *reply_void = redisCommand(m_context, "HKEYS %s", hash_name);
	if(reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_ARRAY)
		{
			int len = reply_redis->elements;
			for(int i = 0; i < len; i++)
			{
				ref->push_back(reply_redis->element[i]->str);
			}
			status = 1;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		::LeaveCriticalSection(&cs);
		return status;
	}
	::LeaveCriticalSection(&cs);
	return 0;

}

//查询指定hash表中所有的value
int RedisHelper::GetHashTableValue(const char* hash_name,vector<string> *ref)
{
	::EnterCriticalSection(&cs);
	void *reply_void = redisCommand(m_context, "HVALS %s", hash_name);
	if(reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_ARRAY)
		{
			int len = reply_redis->elements;
			for(int i = 0; i < len; i++)
			{
				ref->push_back(reply_redis->element[i]->str);
			}
			status = 1;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		::LeaveCriticalSection(&cs);
		return status;
	}
	::LeaveCriticalSection(&cs);
	return 0;

}

//获取hash表中某一个特定的field的value
int RedisHelper::GetHashStringValue(const char* hash_name, const char *key, string *ref)
{
	::EnterCriticalSection(&cs);
	void *reply_void = redisCommand(m_context, "HGET %s %s", hash_name, key);
	if(reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		int status = 0;
		if (retType == REDIS_REPLY_STRING)
		{
			*ref = reply_redis->str;
			status = 1;
		}
		else if (retType == REDIS_REPLY_INTEGER)
		{
			char temp0[50] = { '\0' };
			sprintf_s(temp0, 49, "%I64d", reply_redis->integer);
			*ref = temp0;
			status = 2;
		}
		else if (retType == REDIS_REPLY_ERROR)
		{
			status = -1;
		}
		else
		{
			status = -2;
		}
		freeReplyObject(reply_void);
		::LeaveCriticalSection(&cs);
		return status;
	}
	::LeaveCriticalSection(&cs);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

int RedisHelper::PushBack(const char *key, const char *value)
{
	return 0;
}

int RedisHelper::PushFront(const char *key, const char *value)
{
	return 0;
}

int RedisHelper::PopBack(const char *key, const char *value)
{
	return 0;
}

int RedisHelper::PopFront(const char *key, const char *value)
{
	return 0;
}

int RedisHelper::GetListSize(const char *key, int *ref)
{
	return 0;
}

int RedisHelper::GetListRange(const char *key, const char *param, const char *value)
{
	return 0;
}

int RedisHelper::DeleteValue(const char *key, const char *param, int *ref)
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

__int64 RedisHelper::Increase(const char *key)
{
	
	::EnterCriticalSection(&cs);
	//static int tommic = 0;
	//int temp0 = ++tommic;
	//printf("start = redis -> %d \n", temp0);
	void *reply_void = redisCommand(m_context, "INCR %s", key);
	//printf("end call = redis -> %d \n", temp0);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		if (retType == REDIS_REPLY_INTEGER)
		{
			__int64 ret = reply_redis->integer;
			freeReplyObject(reply_void);
			//printf("end = redis -> %d \n", temp0);
			::LeaveCriticalSection(&cs);
			return ret;
		}
		freeReplyObject(reply_void);
		//printf("end = redis -> %d \n", temp0);
		return -1;
	}
	//printf("end = redis -> %d \n", temp0);
	::LeaveCriticalSection(&cs);
	return 0;
}

int RedisHelper::Delete(const char *key)
{
	void *reply_void = redisCommand(m_context, "DEL %s", key);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		if (retType == REDIS_REPLY_INTEGER)
		{
			int status = (int)(reply_redis->integer);
			freeReplyObject(reply_void);
			return status;
		}
		return -1;
	}
	return 0;
}

int RedisHelper::Showdown(bool save)
{
	static const char *shutdown_save = "shutdown save";
	static const char *shutdown_nosave = "shutdown nosave";
	//这里,如果命令执行成功,应该返回空指针
	void *reply_void  = redisCommand(m_context, save ? shutdown_save : shutdown_nosave);
	if (reply_void)
	{
		redisReply *reply_redis = (redisReply*)reply_void;
		int retType = reply_redis->type;
		if (retType == REDIS_REPLY_INTEGER)
		{
			int status = (int)(reply_redis->integer);
			freeReplyObject(reply_void);
			return status;
		}
		return -1;
	}

	return 0;
}
