#include "..\\stdafx.h"
#include "HttpPostService.h"
#include "Binary.h"
#include "..\\api\\CStr.h"
#include "CurlHttp.h"
#include "CMessage.h"
using namespace OwLib;

namespace OwLibCT
{
	HttpPostService::HttpPostService()
	{
		m_lock.SetName("HttpPostService_m_lock");
		m_isSyncSend = false;
		m_timeout = 0;
	}

	HttpPostService::~HttpPostService()
	{
	}

	bool HttpPostService::GetIsSyncSend()
    {
        return m_isSyncSend;
    }
    
    void HttpPostService::SetIsSyncSend(bool isSyncSend)
    {
        m_isSyncSend = isSyncSend;
    }
    
    CLock HttpPostService::GetLock()
    {
        return m_lock;
    }
   
	int HttpPostService::GetTimeout()
	{
		return m_timeout;
	}

	void HttpPostService::SetTimeout(int timeout)
	{
		m_timeout = timeout;
	}
   
	string HttpPostService::GetUrl()
	{
		return m_url;
	}

	void HttpPostService::SetUrl(string url)
	{
		m_url = url;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DWORD WINAPI HttpPostService::AsynSend(LPVOID lpParam)
	{
        HttpPostService *postService = (HttpPostService*)lpParam;
        if(!postService)
        {
            return 0;
        }
		vector<CMessage*> messages = postService->m_messages;
		CLock lock = postService->GetLock();
        lock.Lock();
        CMessage *message = messages[0];
        lock.UnLock();
        
        if(!message)
        {
            return 0;
        }
		return postService->SendRequest(message);
	}

	void HttpPostService::OnReceive(CMessage *message)
	{
		BaseService::OnReceive(message);
		SendToListener(message); 	
	}

	String HttpPostService::Post(const String& url)
	{
		string result = Post(url, 0, 0);
		String text;
		CStrA::stringTowstring(text, result);
		return text;
	}

	string HttpPostService::Post(const String& url, char *sendDatas, int sendSize)
	{
		string surl;
        CStrA::wstringTostring(surl, url);
		string result = CurlHttp::GetInstance()->Post(surl.c_str(), sendDatas, sendSize);
		return result;
	}

	String HttpPostService::Post(const String& url, const String &data)
	{
		string sData;
		CStrA::wstringTostring(sData, data);
		string str = Post(url, (char*)sData.c_str(), (int)sData.length() + 1);
		String wResult;
		CStrA::stringTowstring(wResult, str);
		return wResult;
	}

	int HttpPostService::Send(CMessage *message)
	{
		if(!m_isSyncSend)
        {
			m_lock.Lock();
			CMessage *copyMessage = new CMessage(*message);
			m_messages.push_back(copyMessage);
			m_lock.UnLock();
			HANDLE hThread = ::CreateThread(0, 0, AsynSend, this, 0, 0);
			::CloseHandle(hThread);
			return 1;
		}
		else
		{
			return SendRequest(message);
		}
	}

	int HttpPostService::SendRequest(CMessage *message)
	{
		_int64 upFlow = BaseService::GetUpFlow();
		Binary binary;
		char *buffer = 0;
		const char *body = message->m_body;
		int bodyLength = message->m_bodyLength;
		int uncBodyLength = bodyLength;
		if (message->m_compressType == COMPRESSTYPE_GZIP)
		{
			uLong cLen = 128;
			if(uncBodyLength > cLen)
			{
				cLen = uncBodyLength;
			}
			buffer = new char[cLen];
			memset(buffer, '\0', cLen);
			CStrA::GZCompress((Byte*)body, bodyLength, (Byte*)buffer, &cLen);
			body = buffer;
			bodyLength = (int)cLen;
		}

		int len = sizeof(int) * 4 + bodyLength + sizeof(short) * 3 + sizeof(char) * 2;
		binary.Initialize(len, false);
		binary.WriteInt(len);
		binary.WriteShort((short)message->m_groupID);
		binary.WriteShort((short)message->m_serviceID);
		binary.WriteShort((short)message->m_functionID);
		binary.WriteInt(message->m_sessionID);
		binary.WriteInt(message->m_requestID);
		binary.WriteChar((char)message->m_state);
		binary.WriteChar((char)message->m_compressType);
		binary.WriteInt(uncBodyLength);
		binary.Write(body, bodyLength);
		if(buffer)
		{
			delete[] buffer;
			buffer = 0;
		}
		string result = CurlHttp::GetInstance()->Post(GetUrl().c_str(), (char*)binary.GetBytes(), len);
		int ret = (int)result.length();
		upFlow += ret;
		BaseService::SetUpFlow(upFlow);
		BaseService::CallBack(message->m_socketID, 0, result.c_str(), ret);
		delete message;
		message = 0;
		return 0;
	}
}