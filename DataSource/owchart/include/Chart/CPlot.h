/*****************************************************************************\
*                                                                             *
* CPlot.h -     Chart plot functions, types, and definitions                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CPLOT_H__
#define __CPLOT_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "Enums.h"
#include "CDiv.h"

namespace OwLib
{
	class  CDiv;
	class  CPlot
	{
	public:
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual _int64 GetColor();
		virtual void SetColor(_int64 color);
		virtual CDiv* GetDiv();
		virtual void SetDiv(CDiv *div);
		virtual bool DrawGhost();
		virtual void SetDrawGhost(bool drawGhost);
		virtual bool IsEnabled();
		virtual void SetEnabled(bool enabled);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual int GetLineStyle();
		virtual void SetLineStyle(int lineStyle);
		virtual int GetLineWidth();
		virtual void SetLineWidth(int lineWidth);
		virtual wstring GetPlotType();
		virtual void SetPlotType(const wstring& plotType);
		virtual bool IsSelected();
		virtual void SetSelected(bool selected);
		virtual _int64 GetSelectedColor();
		virtual void SetSelectedColor(_int64 selectedColor);
		virtual SelectPoint GetSelectedPoint();
		virtual void SetSelectedPoint(SelectPoint selectedPoint);
		virtual wstring GetText();
		virtual void SetText(const wstring& text);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetZOrder();
		virtual void SetZOrder(int zOrder);
	public:
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveEnd();
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual bool OnSelect();
		virtual void Render(CPaint *paint);
	};
}
#endif