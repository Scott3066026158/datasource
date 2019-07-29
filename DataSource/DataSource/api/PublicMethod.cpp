#include "..\\stdafx.h"
#include "..\\api\\CStr.h"
#include "..\\global\\BusinessIDs.h"
#include "PublicMethod.h"

PublicMethod::PublicMethod()
{
}

PublicMethod::~PublicMethod()
{
}

void PublicMethod::isEmpty()
{
}

String PublicMethod::getCurrentTime()
{
	_int64 nowtime = time(0);   
	struct tm *local = localtime(&nowtime);
	wchar_t sz[100] = {0};
	swprintf_s(sz, 99, L"%04d-%02d-%02d %02d:%02d:%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	return sz;
}

void PublicMethod::getCurrentTime(String* yymmdd, String* hhmmss)
{
	_int64 nowtime = time(0);
	wchar_t buff[64] = {0};
	int y = 0, mon = 0, d = 0, h = 0, m = 0, s = 0, msec = 0;
	CStrA::M130(nowtime, &y, &mon, &d, &h, &m, &s, &msec);
	swprintf_s(buff, 63, L"%04d-%02d-%02d", y, mon, d);
	*yymmdd = buff;
	swprintf_s(buff, 63, L"%02d-%02d-%02d", h, m, s);
	*hhmmss = buff;
}

//比较两个double数据是否相等
bool PublicMethod::d_eq(const double& a, const double& b)
{
	if( fabs (a - b) < MIN_DBL_NUMBER)
    {
        return true;
    }
    return false;
}

String PublicMethod::GetOrderStatus(int state)
{
	String result;
	switch(state)
	{
	case ORDERSTATUS_P1:
		result = L"InOrder";
		break;
	case ORDERSTATUS_P2:
		result = L"Canceled";
		break;
	case ORDERSTATUS_P3:
		result = L"PairCancel";
		break;
	case ORDERSTATUS_P4:
		result = L"PartTraded";
		break;
	case ORDERSTATUS_P5:
		result = L"Traded";
		break;
	case ORDERSTATUS_P6:
		result = L"Faild";
		break;
	default:
		result = L"Faild";
		break;
	}
	return result;
}