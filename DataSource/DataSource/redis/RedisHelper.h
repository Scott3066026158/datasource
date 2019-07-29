#ifndef __REDISHELPER_H__
#define __REDISHELPER_H__

#pragma warning(disable:4018)
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")

//#define _XKEYCHECK_H
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct redisContext;

class CLock;

/*Redis数据库帮助类*/
class RedisHelper
{
public:
	RedisHelper();
	~RedisHelper();
public:
	//CLock *m_lock;
	CRITICAL_SECTION cs;
public:
	/*初始化, 其中auth是可选的*/
	/* -1 : 权限验证没有通过*/
	/* -2 : 无法进行权限验证*/
	/* -3 : 连接reids错误*/
	/* -4 : 无法与redis建立连接*/
	int Init(const char *ip, int port, const char *auth);

public:
	/*int DeleteKeys(const char *keys);
	int Exists(const char *keys);
	int GetKeys(const char *pattern);*/

public:
	int SetDoubleValue(const char *key, double val);
	int GetHashTableKey(const char* hash_name, vector<string> *ref);
	int GetHashTableValue(const char* hash_name, vector<string> *ref);
	int SetHashString(const char* hash_name, const char *key, const char *val);
	int SetIntValue(const char *key, int val);
	int SetValue(const char *key, const char *val);
	int SetValueU(const char *key, const unsigned char *val);

public:
	int GetDoubleValue(const char *key, double *ref);
	int GetHashStringValue(const char* hash_name, const char *key, string *ref);
	int GetIntValue(const char *key, int *ref);
	int GetValue(const char *key, string *ref);

public:
	int PushBack(const char *key, const char *value);
	int PushFront(const char *key, const char *value);
	int PopBack(const char *key, const char *value);
	int PopFront(const char *key, const char *value);
	int GetListSize(const char *key, int *ref);
	int GetListRange(const char *key, const char *param, const char *value);
	int DeleteValue(const char *key, const char *param, int *ref);
	int DeleteHashString(const char* hash_name, const char *key);

public:
	__int64 Increase(const char *key);
	int Delete(const char *key);

public:
	/*注意,此方法会停止远程的redis服务, 导致其他使用redis的程序也无法连接redis*/
	/*如果你不知道这是在干嘛,请勿调用此方法*/
	/*save参数在正常情况下总是填写true*/
	int Showdown(bool save);

private:
	redisContext *m_context;
};

#endif //__REDISHELPER_H__