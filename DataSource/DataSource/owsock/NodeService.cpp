#include "..\\stdafx.h"
#include "NodeService.h"
#include "Binary.h"


HttpData::HttpData()
{
	m_body = 0;
	m_close = false;
	m_contentLength = 0;
	m_contentType = L"";
	m_method = L"";
	m_parameters.clear();	
	m_resBytes = 0;
	m_resBytesLength = 0;
	m_resStr = L"";	
	m_remoteIP = L"";
    m_remotePort = 0;
	m_socket = 0;
	m_statusCode = 200;
	m_url = L"";
}

HttpData::~HttpData()
{
	m_parameters.clear();
	if(m_body)
	{
		delete m_body;
		m_body = 0;
	}
	if(m_resBytes)
	{
		delete m_resBytes;
		m_resBytes = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

NodeService::NodeService()
{
	m_hSocket = 0;
	m_port = 8080;
}

NodeService::~NodeService()
{
}

int NodeService::GetPort()
{
	return m_port;
}

void NodeService::SetPort(int port)
{
	m_port = port;
}

SOCKET NodeService::GetSocket()
{
	return m_hSocket;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI ReceiveHandle(LPVOID lpParam)
{
	HttpData *data = (HttpData*)lpParam;
	if(!data) return 0;
	SOCKADDR_IN addr = data->m_addr;
	const int bufLen = 102400;
	char buffer[bufLen];
	memset(buffer, '\0', bufLen);
    String parameters = L"";
	int contentLength = 0;
	int copyLen = recv(data->m_socket, buffer, bufLen, 0);
	if(copyLen == 0 || copyLen == SOCKET_ERROR) 
	{
		return 0;
	}		
	strstream os(buffer, copyLen);
	while(true)
	{
		char bufferline[bufLen];
		memset(bufferline, '\0', bufLen);
		os.getline(bufferline, bufLen);
		string requestHeader(bufferline);
		size_t headLen = requestHeader.length();
		if(headLen == 0 || (headLen == 1 && requestHeader[0] == '\r'))
		{
			break;
		}
		int keyLength = 0;
		int begin = 5;
		if(requestHeader.find("GET") == 0)
		{
			int end = (int)requestHeader.find("HTTP/");
			data->m_method = L"GET";
			CStrA::stringTowstring(parameters, requestHeader.substr(begin, end - 6));
		}
		else if(requestHeader.find("POST") == 0)
		{
			int end = (int)requestHeader.find("HTTP/");
			data->m_method = L"POST";
			CStrA::stringTowstring(parameters, requestHeader.substr(begin, end - 6));
		}
		else if(requestHeader.find("Accept:") == 0)
		{
			int acceptIndex = 0;
			keyLength = (int)strlen("Accept:");
			begin = acceptIndex + keyLength;
			CStrA::stringTowstring(data->m_contentType, requestHeader.substr(begin, requestHeader.find(',', begin) - begin));
		}
		else if (requestHeader.find("Host:") == 0)
		{
			int hostIndex = 0;
			keyLength = (int)strlen("Host:");
			begin = hostIndex + keyLength;
			CStrA::stringTowstring(data->m_url, requestHeader.substr(begin, requestHeader.find("\r\n", begin) - begin));
		}
		else if (requestHeader.find("Content-Length:") == 0)
		{
			int contentIndex = 0;
			keyLength = (int)strlen("Content-Length:");
			begin = contentIndex + keyLength;
			string postParamterLength = CStrA::Replace(requestHeader.substr(begin), " ", "");;
			contentLength = atoi(postParamterLength.c_str());
		}
	}		
    if (contentLength > 0)
    {
        int idx = 0, ide = 0;
        data->m_body = new char[contentLength];
        while (idx < contentLength)
        {
			int recvData = os.get();
            if (recvData != -1)
            {
                if (recvData != 0)
                {
                    ide++;
                }
                idx++;
            }
            else
            {
                break;
            }
        }
        if (ide == 0)
        {
            recv(data->m_socket, data->m_body, contentLength, 0);
        }
        else
        {
            for (int i = 0; i < contentLength; i++)
            {
                data->m_body[i] = buffer[copyLen - contentLength + i];
            }
        }
        data->m_contentLength = contentLength;
    }
	if ((int)data->m_method.length() == 0)
    {
		closesocket(data->m_socket);
		delete data;
        return 0;
    }
	int cindex = (int)parameters.find('?');
    if (cindex != -1)
    {
        data->m_url = data->m_url + L"/" + parameters;
		parameters = parameters.substr(cindex + 1);
		vector<String> strParameters = CStrA::Split(parameters, L"&");
		int strsSize = (int)strParameters.size();
        for (int i = 0; i < strsSize; i++)
        {
			vector<String> subStrs = CStrA::Split(strParameters[i], L"=");
			if((int)subStrs.size() > 1)
			{
				string value = "";
				CStrA::wstringTostring(value, subStrs[1]);
				value = CStrA::UrlDecode(value);
				String wValue = L"";
				CStrA::stringTowstring(wValue, value);
				String wPara = CStrA::ToLower(subStrs[0]);
				data->m_parameters.insert(make_pair(wPara, wValue));
			}
        }
    }
    else
    {
        data->m_url += L"/" + parameters;
    }		
	//DataCenter::GetLPManager()->OnReceiveHttp(data);
    if (data->m_close)
    {
		closesocket(data->m_socket);
		delete data;
        return 0;
    }
	int resContentLength = 0;
    if (data->m_resBytes)
    {
        resContentLength = data->m_resBytesLength;
    }
    else
    {
		string str = "";
		CStrA::wstringTostring(str, data->m_resStr);
        resContentLength = (int)str.length();// + 1;
    }
	string retMessage = "";
	char statusCode[10]; 		
	sprintf_s(statusCode, 9, "%d", data->m_statusCode);
	char szContentLength[10]; 		
	sprintf_s(szContentLength, 9, "%d", resContentLength);
	retMessage = retMessage.append("HTTP/1.0 ");
	retMessage = retMessage.append(statusCode);
	retMessage = retMessage.append(" OK\r\n");
	retMessage = retMessage.append("Content-Length:");
	retMessage = retMessage.append(szContentLength);
	retMessage = retMessage.append("\r\n");
	retMessage = retMessage.append("Connection: close\r\n\r\n");
	if (data->m_resBytes)
    {
		int retLength = (int)strlen(retMessage.c_str());
		int ret = send(data->m_socket, retMessage.c_str(), retLength, 0);
		ret = send(data->m_socket, data->m_resBytes, data->m_resBytesLength, 0);
    }
    else
    {
		string str = "";
		CStrA::wstringTostring(str, data->m_resStr);
		retMessage = retMessage.append(str);
		char *buf = new char[(int)retMessage.length() + 1];
		memset(buf, 0, (int)retMessage.length() + 1);
		memcpy(buf, retMessage.c_str(), retMessage.length());
		int ret = send(data->m_socket, buf, (int)retMessage.length() + 1, 0);
		delete[] buf;
		buf = 0;
    }
	closesocket(data->m_socket);
	delete data;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NodeService::Close(int socketID)
{
	SOCKET socket = (SOCKET)socketID;
	int ret = 0;
	if(socket)
	{
		ret = closesocket(socket);
	}
	return ret;
}

int NodeService::Start()
{
	int ret = 0;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_port);
	ret = bind(m_hSocket, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
	if(ret != SOCKET_ERROR)
	{
		ret = listen(m_hSocket, 2);
		if(ret != SOCKET_ERROR)
		{
			while(true)
			{
				SOCKADDR_IN addr;
				int addrlen = sizeof(addr);
				SOCKET socket = accept(m_hSocket, (LPSOCKADDR)&addr, &addrlen);
				if(socket == SOCKET_ERROR)
				{
					::Sleep(1);
					continue;
				}
				HttpData *data = new HttpData;
				data->m_addr = addr;
				data->m_socket = socket;
				HANDLE hThread = ::CreateThread(NULL, 0, ReceiveHandle, (LPVOID)data, 0, 0);
				::CloseHandle(hThread);
			}
		}
	}
	if(m_hSocket)
	{
		ret = closesocket(m_hSocket);
	}
	return ret;
}
