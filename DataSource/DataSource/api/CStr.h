/*****************************************************************************\
*                                                                             *
* Str.h -      String functions                                               *
*                                                                             *
*               Version 4.00 ������                                       *
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
	//��������
	static double round(double x); 
public:
	//����ת��
	static void ANSCToUnicode(string& out, const char* inSrc);
	//ѹ���ַ���
	static int Compress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	//�����ַ���
	static void Contact(wchar_t *str, LPCTSTR str1, LPCTSTR str2 = L"", LPCTSTR str3 = L"");
	//CTP����ת����ͨ���Ŵ���
	static String ConvertCTPCodeToTDXCode(const String& code);
	//���ݿ����ת���ɻ������
	static String ConvertDBCodeToCacheCode(const String& code);
	//���ݿ����ת�����ļ�����
	static String ConvertDBCodeToFileCode(const String& code);
	//ת��Ϊǧ��λ
	static String ConvertThousands(double value, int digit);
	//���ݿ����תΪ�ļ���
	static string ConvertDBCodeToFileName(const string& code);
	//���ݿ����תΪ���˴���
	static string ConvertDBCodeToSinaCode(const string& code);
	//���ݿ����תΪ��Ѷ����
	static string ConvertDBCodeToTencentCode(const string& code);
	//���˴���תΪ���ݿ����
	static String ConvertSinaCodeToDBCode(const String& code);
	static double ConvertStrToDouble(const wchar_t *str);
	static String ConvertFloatToStr(float value);
	static String ConvertIntToStr(int value);
	static double ConvertStrToDouble(const String& str);
	static int ConvertStrToInt(const wchar_t *str);
	static String ConvertDoubleToStr(double d);
	//��Ѷ����תΪ���ݿ����
	static String ConvertTencentCodeToDBCode(const String& code);
	//��ѹ���ַ���
	static int DeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//Double���ڵ��ڱȽ�
	static bool DoubleEG(double dest, double source);
	//��ȡ���ݿ��ַ���
	static String GetDBString(const String& strSrc);
	//��ȡΨһ��ʶ
	static string GetGuid();
	//��ȡ��ʽ������
	static void GetFormatDate(double date, wchar_t *str);
	//��ȡ��ʽ������
	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
	//��ȡ�ַ����Ŀռ�
	static int GetStringCapacity(const string& str);
	//��ȡ���ַ����Ŀռ�
	static int GetWStringCapacity(const String& str);
	//��ȡ����ָ��С��λ�����ַ���
	static void GetValueByDigit(double value, int digit, wchar_t *str);
	// GZIPѹ������
	static int GZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	// GZIP��ѹ������
	static int GZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//��ȡ������ֵ
	static double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
	//ͨ��������ֵ��ȡ������ʱ����
	static void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
	//�滻�ַ���
	static string Replace(const string& str, const string& src, const string& dest);
	//�滻���ַ���
	static String Replace(const String& str, const String& src, const String& dest);
	//�ָ��ַ���
	static vector<string> Split(const string& str, const string& pattern);
	//�ָ���ַ���
	static vector<String> Split(const String& str, const String& pattern);
	//ת��Ϊ���ַ���
	static void stringTowstring(String &strDest, const string& strSrc);
	//ת��ΪСд
	static String ToLower(const String& str);
	//ת��ΪСд
	static string ToLower(const string& str);
	//ת��Ϊ��д
	static String ToUpper(const String& str);
	//ת��Ϊ��д
	static string ToUpper(const string& str);
	//����ת��
	static void UnicodeToANSC(string& out, const char* inSrc);
	static string UrlEncode(const std::string& szToEncode);
	static string UrlDecode(const std::string& szToDecode);
	//�������Ƿ����
	static bool ValueEqual(float lhs, float rhs);
	//�������Ƿ����
	static bool ValueEqual(double lhs, double rhs);
	//ת��Ϊխ�ַ���
	static void wstringTostring(string &strDest, const String& strSrc);
	//ת��Ϊխ�ַ���
	static string wstringTostring(const String& strSrc);
};
#endif