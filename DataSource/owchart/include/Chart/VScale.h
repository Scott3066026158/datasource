/*****************************************************************************\
*                                                                             *
* VScale.h -    Vertical scale functions, types, and definitions              *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/

#ifndef __VSCALE_H__
#define __VSCALE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "Enums.h"
#include "CTable.h"
#include "CrossLineTip.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;
	class  CrossLineTip;

	class  VScale : public CProperty
	{
	protected:
		bool m_allowUserPaint;
		bool m_autoMaxMin;
		int m_baseField;
		CrossLineTip *m_crossLineTip;
		int m_digit;
		FONT *m_font;
		_int64 m_foreColor;
		_int64 m_foreColor2;
		int m_magnitude;
		double m_midValue;
		NumberStyle m_numberStyle;
		int m_paddingBottom;
		int m_paddingTop;
		bool m_reverse;
		_int64 m_scaleColor;
		vector<double> m_scaleSteps;
		VScaleSystem m_system;
		VScaleType m_type;
		double m_visibleMax;
		double m_visibleMin;
	public:
		VScale();
		virtual ~VScale();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual bool AutoMaxMin();
		virtual void SetAutoMaxMin(bool autoMaxMin);
		virtual int GetBaseField();
		virtual void SetBaseField(int baseField);
		virtual CrossLineTip* GetCrossLineTip();
		virtual int GetDigit();
		virtual void SetDigit(int digit);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual _int64 GetForeColor2();
		virtual void SetForeColor2(_int64 foreColor2);
		virtual int GetMagnitude();
		virtual void SetMagnitude(int magnitude);
		virtual double GetMidValue();
		virtual void SetMidValue(double midValue);
		virtual NumberStyle GetNumberStyle();
		virtual void SetNumberStyle(NumberStyle numberStyle);
		virtual int GetPaddingBottom();
		virtual void SetPaddingBottom(int paddingBottom);
		virtual int GetPaddingTop();
		virtual void SetPaddingTop(int paddingTop);
		virtual bool IsReverse();
		virtual void SetReverse(bool reverse);
		virtual _int64 GetScaleColor();
		virtual void SetScaleColor(_int64 scaleColor);
		virtual VScaleSystem GetSystem();
		virtual void SetSystem(VScaleSystem system);
		virtual VScaleType GetType();
		virtual void SetType(VScaleType type);
		virtual double GetVisibleMax();
		virtual void SetVisibleMax(double visibleMax);
		virtual double GetVisibleMin();
		virtual void SetVisibleMin(double visibleMin);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		vector<double> GetScaleSteps();
		virtual void OnPaint(CPaint *paint, CDiv *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
		void SetScaleSteps(vector<double> scaleSteps);
	};
}
#endif