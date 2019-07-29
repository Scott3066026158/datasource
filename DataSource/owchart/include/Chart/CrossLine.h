/*****************************************************************************\
*                                                                             *
* CrossLine.h - Cross line functions, types, and definitions                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/

#ifndef __CROSSLINE_H__
#define __CROSSLINE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Enums.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;
	class  CrossLine : CProperty
	{
	protected:
		bool m_allowUserPaint;
		bool m_allowDoubleClick;
		AttachVScale m_attachVScale;
		_int64 m_lineColor;
	public:
		CrossLine();
		virtual ~CrossLine();
		virtual bool AllowDoubleClick();
		virtual void SetAllowDoubleClick(bool allowDoubleClick);
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual _int64 GetLineColor();
		virtual void SetLineColor(_int64 lineColor);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaint *paint, CDiv *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif