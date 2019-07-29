/*****************************************************************************\
*                                                                             *
* CrossLineTip.h - Cross line tip functions, types, and definitions           *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/

#ifndef __CROSSLINETIP_H__
#define __CROSSLINETIP_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;

	class  CrossLineTip
	{
	protected:
		bool m_allowUserPaint;
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
		bool m_visible;
	public:
		CrossLineTip();
		virtual ~CrossLineTip();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void OnPaint(CPaint *paint, CDiv *div, const RECT& rect);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif