#pragma once

// ������뽫λ������ָ��ƽ̨֮ǰ��ƽ̨��ΪĿ�꣬���޸����ж��塣
// �йز�ͬƽ̨��Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ����ֵ����Ϊ�ʵ���ֵ����ָ���� Windows Me ����߰汾��ΪĿ�ꡣ
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream> 
#include <map>
#include <vector>
#include <string>
#include <float.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <strstream> 
#include <list>
#include <set>
#include <deque>
#include <sstream>
#include "winsock2.h"
#include <string>
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <amqp_framing.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib, "..\\libs\\libmysql.lib")
#pragma comment(lib, "..\\libs\\mysqlclient.lib")
#pragma comment(lib, "..\\libs\\librabbitmq.4.lib")
#pragma comment(lib, "..\\libs\\libcurl_a.lib")
#pragma comment(lib, "..\\libs\\lib_json.lib")
#include "..\\owchart\\include\\Base\\CLib.h"




using namespace std; 


#define SECURITY_WIN32
#define SECURITY_KERNEL
typedef  std::wstring String;