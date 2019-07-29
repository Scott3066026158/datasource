/******************************************************************************\
*                                                                              *
* HttpPostService.cs -  Http post service functions, types, and definitions.   *
*                                                                              *
*               Version 1.00 бя                                                *
*                                                                              *
*               Copyright (c) 2016-2017, Client. All rights reserved.          *
*               Created by Lord.                                               *
*                                                                              *
*******************************************************************************/

#ifndef __HTTPPOSTSERVICE_H__
#define __HTTPPOSTSERVICE_H__
#pragma once
#include "BaseService.h"

struct CMessage;

namespace OwLibCT
{
	class HttpPostService : public BaseService
	{
	private:
		bool m_isSyncSend;
        CLock m_lock;
		string m_url;
		int m_timeout;
	public:
		vector<CMessage*> m_messages;
		HttpPostService();
		virtual ~HttpPostService();
		bool GetIsSyncSend();
        void SetIsSyncSend(bool isSyncSend);
        CLock GetLock();
		int GetTimeout();
		void SetTimeout(int timeout);
		string GetUrl();
		void SetUrl(string url);
	public:		
		static DWORD WINAPI AsynSend(LPVOID lpParam);
	public:
		virtual void OnReceive(CMessage *message);
		String Post(const String& url);
		string Post(const String& url, char *sendDatas, int sendSize);
		String Post(const String& url, const String &data);
		int Send(CMessage *message);
		int SendRequest(CMessage *message);
	};
}
#endif