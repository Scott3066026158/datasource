#include "..\\stdafx.h"
#include "HttpGetService.h"
#include "Binary.h"
#include "..\\api\\CStr.h"
#include "CurlHttp.h"
using namespace OwLib;
namespace OwLibCT
{
    string HttpGetService::Get(const string &url)
    {
		CurlHttp *http = CurlHttp::GetInstance(0);
		return http->Get(url, false, 10000);
    }

    string HttpGetService::Get(const string &url, int time)
    {
		CurlHttp *http = CurlHttp::GetInstance(0);
		return http->Get(url, false, time);
    }
}
