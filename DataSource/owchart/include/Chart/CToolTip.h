/*****************************************************************************\
*                                                                             *
* CToolTip.h -  Tooltip functions, types, and definitions                     *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/


#ifndef __CTOOLTIP_H__
#define __CTOOLTIP_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;

	class  CToolTip : public CProperty
	{
	protected:
		bool m_allowUserPaint;
		_int64 m_backColor;
		_int64 m_borderColor;
		FONT *m_font;
		_int64 m_foreColor;
	public:
		CToolTip();
		virtual ~CToolTip();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual _int64 GetBorderColor();
		virtual void SetBorderColor(_int64 borderColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaint *paint, CDiv *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif