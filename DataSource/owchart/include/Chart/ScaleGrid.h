/*****************************************************************************\
*                                                                             *
* ScaleGrid.h -     Scale grid functions, types, and definitions              *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/

#ifndef __SCALEGRID_H__
#define __SCALEGRID_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;

	class  ScaleGrid : public CProperty
	{
	protected:
		bool m_allowUserPaint;
		int m_distance;
		_int64 m_gridColor;
		int m_lineStyle;
		bool m_visible;
	public:
		ScaleGrid();
		virtual ~ScaleGrid();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual int GetDistance();
		virtual void SetDistance(int distance);
		virtual _int64 GetGridColor();
		virtual void SetGridColor(_int64 gridColor);
		virtual int GetLineStyle();
		virtual void SetLineStyle(int lineStyle);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaint *paint, CDiv *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif