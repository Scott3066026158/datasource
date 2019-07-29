/*****************************************************************************\
*                                                                             *
* CStr.h -      wstring functions                                              *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CSTR_H__
#define __CSTR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include <tchar.h>
#include "CPaint.h"
#include "Control.h"

namespace OwLib
{
	class  CStr
	{
	protected:
		static double round(double x); 
	public:
		static void Contact(wchar_t *str, const wchar_t *str1, const wchar_t *str2, const wchar_t *str3);
		static wstring ConvertAnchorToStr(const ANCHOR& anchor);
		static wstring ConvertBoolToStr(bool value);
		static wstring ConvertColorToStr(_int64 color);
		static wstring ConvertContentAlignmentToStr(ContentAlignmentA contentAlignment);
		static wstring ConvertCursorToStr(CursorsA cursor);
		static wstring ConvertDoubleToStr(double value);
		static wstring ConvertDockToStr(DockStyleA dock);
		static wstring ConvertFloatToStr(float value);
		static wstring ConvertFontToStr(FONT *font);
		static wstring ConvertHorizontalAlignToStr(HorizontalAlignA horizontalAlign);
		static wstring ConvertIntToStr(int value);
		static wstring ConvertLayoutStyleToStr(LayoutStyleA layoutStyle);
		static wstring ConvertLongToStr(_int64 value);
		static wstring ConvertPaddingToStr(const PADDING& padding);
		static wstring ConvertPointToStr(const POINT& mp);
		static wstring ConvertRectToStr(const RECT& rect);
		static wstring ConvertSizeToStr(const SIZE& size);
		static ANCHOR ConvertStrToAnchor(const wstring& str);
		static bool ConvertStrToBool(const wstring& str);
		static _int64 ConvertStrToColor(const wstring& str);
		static ContentAlignmentA ConvertStrToContentAlignment(const wstring& str);
		static CursorsA ConvertStrToCursor(const wstring& str);
		static DockStyleA ConvertStrToDock(const wstring& str);
		static double ConvertStrToDouble(const wstring& str);
		static double ConvertStrToDouble(const wchar_t *str);
		static float ConvertStrToFloat(const wstring& str);
		static FONT* ConvertStrToFont(const wstring& str);
		static HorizontalAlignA ConvertStrToHorizontalAlign(const wstring& str);
		static int ConvertStrToInt(const wstring& str);
		static int ConvertStrToInt(const wchar_t *str);
		static LayoutStyleA ConvertStrToLayoutStyle(const wstring& str);
		static _int64 ConvertStrToLong(const wstring& str);
		static _int64 ConvertStrToLong(const wchar_t *str);
		static PADDING ConvertStrToPadding(const wstring& str);
		static POINT ConvertStrToPoint(const wstring& str);
		static RECT ConvertStrToRect(const wstring& str);
		static SIZE ConvertStrToSize(const wstring& str);
		static VerticalAlignA ConvertStrToVerticalAlign(const wstring& str);
		static wstring ConvertVerticalAlignToStr(VerticalAlignA verticalAlign);
		static string GetGuid();
		static void GetFormatDate(double date, wchar_t *str);
		static wstring GetFormatDate(const wstring& format, int year, int month, int day, int hour, int minute, int second);
		static void GetValueByDigit(double value, int digit, wchar_t *str);
		static int HexToDec(const char *str);
		static wstring Replace(const wstring& str, const wstring& src, const wstring& dest);
		static float SafeDoubleToFloat(double value, int digit);
		static vector<wstring> Split(const wstring& str, const wstring& pattern);
		static void stringTowstring(wstring &strDest, const string& strSrc);
		static wstring ToLower(const wstring& str);
		static wstring ToUpper(const wstring& str);
		static void wstringTostring(string &strDest, const wstring& strSrc);
	};
}
#endif