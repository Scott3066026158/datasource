#pragma once
#ifndef __HTTPROUTER_H__
#define __HTTPROUTER_H__

#include "..\\owsock\\HttpPostService.h"
#include "..\\bean\\CBean.h"
#include <vector>
class HttpRouter{
public:
	HttpRouter();
	~HttpRouter();
public:
	static DWORD WINAPI Wan(LPVOID lpParam);
	void ReqBalanceNotice(vector<BalanceNoticeRecord*> msg);
	void ReqOrderInfo(vector<OrderInfo*> msg);
};
#endif