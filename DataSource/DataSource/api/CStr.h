/*****************************************************************************\
*                                                                             *
* Str.h -      String functions                                               *
*                                                                             *
*               Version 4.00 ★★★★★                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Gaia's OwChart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CSTRA_H__
#define __CSTRA_H__
#pragma once
#include "..\\stdafx.h"
#include "objbase.h"
#include "..\\..\\third_party\\zlib\zlib.h"
#include "..\\..\\third_party\\zlib\zconf.h"

class CodeConvert_Win
{
public:
	CodeConvert_Win(const char *input, unsigned int fromCodePage, unsigned int toCodePage);
	virtual ~CodeConvert_Win() {
		delete [] wcharBuf;        
		delete [] charBuf;    
		};    
		const char* ToString() {    
			return charBuf;    
		};
private:    
	  wchar_t *wcharBuf;    
	  char *charBuf;
};

class CStrA
{
private:
	//四舍五入
	static double round(double x); 
public:
	//编码转换
	static void ANSCToUnicode(string& out, const char* inSrc);
	//压缩字符串
	static int Compress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	//连接字符串
	static void Contact(wchar_t *str, LPCTSTR str1, LPCTSTR str2 = L"", LPCTSTR str3 = L"");
	//CTP代码转换成通达信代码
	static String ConvertCTPCodeToTDXCode(const String& code);
	//数据库代码转换成缓存代码
	static String ConvertDBCodeToCacheCode(const String& code);
	//数据库代码转换成文件代码
	static String ConvertDBCodeToFileCode(const String& code);
	//转化为千分位
	static String ConvertThousands(double value, int digit);
	//数据库代码转为文件名
	static string ConvertDBCodeToFileName(const string& code);
	//数据库代码转为新浪代码
	static string ConvertDBCodeToSinaCode(const string& code);
	//数据库代码转为腾讯代码
	static string ConvertDBCodeToTencentCode(const string& code);
	//新浪代码转为数据库代码
	static String ConvertSinaCodeToDBCode(const String& code);
	static double ConvertStrToDouble(const wchar_t *str);
	static String ConvertFloatToStr(float value);
	static String ConvertIntToStr(int value);
	static double ConvertStrToDouble(const String& str);
	static int ConvertStrToInt(const wchar_t *str);
	static String ConvertDoubleToStr(double d);
	//腾讯代码转为数据库代码
	static String ConvertTencentCodeToDBCode(const String& code);
	//解压缩字符串
	static int DeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//Double大于等于比较
	static bool DoubleEG(double dest, double source);
	//获取数据库字符串
	static String GetDBString(const String& strSrc);
	//获取唯一标识
	static string GetGuid();
	//获取格式化日期
	static void GetFormatDate(double date, wchar_t *str);
	//获取格式化日期
	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
	//获取字符串的空间
	static int GetStringCapacity(const string& str);
	//获取宽字符串的空间
	static int GetWStringCapacity(const String& str);
	//获取保留指定小数位数的字符串
	static void GetValueByDigit(double value, int digit, wchar_t *str);
	// GZIP压缩数据
	static int GZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	// GZIP解压缩数据
	static int GZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//获取日期数值
	static double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
	//通过日期数值获取年月日时分秒
	static void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
	//替换字符串
	static string Replace(const string& str, const string& src, const string& dest);
	//替换宽字符串
	static String Replace(const String& str, const String& src, const String& dest);
	//分割字符串
	static vector<string> Split(const string& str, const string& pattern);
	//分割宽字符串
	static vector<String> Split(const String& str, const String& pattern);
	//转化为宽字符串
	static void stringTowstring(String &strDest, const string& strSrc);
	//转换为小写
	static String ToLower(const String& str);
	//转换为小写
	static string ToLower(const string& str);
	//转换为大写
	static String ToUpper(const String& str);
	//转换为大写
	static string ToUpper(const string& str);
	//编码转换
	static void UnicodeToANSC(string& out, const char* inSrc);
	static string UrlEncode(const std::string& szToEncode);
	static string UrlDecode(const std::string& szToDecode);
	//两个数是否相等
	static bool ValueEqual(float lhs, float rhs);
	//两个数是否相等
	static bool ValueEqual(double lhs, double rhs);
	//转化为窄字符串
	static void wstringTostring(string &strDest, const String& strSrc);
	//转化为窄字符串
	static string wstringTostring(const String& strSrc);
};
#endif