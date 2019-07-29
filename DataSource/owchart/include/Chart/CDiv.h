/*****************************************************************************\
*                                                                             *
* CDiv.h -      Chart div functions, types, and definitions                   *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Modified by Wang Shaoxu.                                      *
*******************************************************************************/

#ifndef __CDIV_H__
#define __CDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "Enums.h"
#include "CrossLine.h"
#include "ScaleGrid.h"
#include "Chart.h"
#include "VScale.h"
#include "SelectArea.h"
#include "CToolTip.h"
#include "TitleBar.h"
#include "HScale.h"
#include "CPlot.h"
#include "BaseShape.h"

namespace OwLib
{
	class  ChartA;
	class  CrossLine;
	class  CToolTip;
	class  CPlot;
	class  BaseShape;
	class  HScale;
	class  VScale;
	class  NativeBase;
	class  TitleBar;
	class  SelectArea;
	class  ScaleGrid;
	class  CDiv : public CProperty
	{
	protected:
		bool m_allowUserPaint;
		_int64 m_backColor;
		_int64 m_borderColor;
		ChartA *m_chart;
		CrossLine *m_crossLine;
		FONT *m_font;
		ScaleGrid *m_hGrid;
		HScale *m_hScale;
		VScale *m_leftVScale;
		POINT m_location;
		vector<CPlot*> m_plots;
		int m_px;
		int m_py;
		VScale *m_rightVScale;
		SelectArea *m_selectArea;
		bool m_selected;
		vector<BaseShape*> m_shapes;
		bool m_showSelect;
		SIZE m_size;
		TitleBar *m_title;
		CToolTip *m_toolTip;
		int m_verticalPercent;
		ScaleGrid *m_vGrid;
		int m_workingAreaHeight;
	public:
		static bool ShapesAsc(BaseShape *x, BaseShape *y);
		static bool ShapesDesc(BaseShape *x, BaseShape *y);
		static bool PlotsAsc(CPlot *x, CPlot *y);
		static bool PlotsDesc(CPlot *x, CPlot *y);
	public:
		CDiv();
		virtual ~CDiv();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual _int64 GetBorderColor();
		virtual void SetBorderColor(_int64 borderColor);
		virtual int GetBottom();
		virtual RECT GetBounds();
		virtual void SetBounds(RECT bounds);
		virtual CrossLine* GetCrossLine();
		virtual void SetCrossLine(CrossLine *crossLine);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual int GetHeight();
		virtual ScaleGrid* GetHGrid();
		virtual void SetHGrid(ScaleGrid *hGrid);
		virtual HScale* GetHScale();
		virtual void SetHScale(HScale *hScale);
		virtual ChartA* GetChart();
		virtual void SetChart(ChartA *chart);
		virtual int GetLeft();
		virtual VScale* GetLeftVScale();
		virtual void SetLeftVScale(VScale *leftVScale);
		virtual POINT GetLocation();
		virtual int GetPx();
		virtual void SetPx(int px);
		virtual int GetPy();
		virtual void SetPy(int py);
		virtual int GetRight();
		virtual VScale* GetRightVScale();
		virtual void SetRightVScale(VScale *rightVScale);
		virtual SelectArea* GetSelectArea();
		virtual void SetSelectArea(SelectArea *selectArea);
		virtual bool IsSelected();
		virtual void SetSelected(bool selected);
		virtual bool IsShowSelect();
		virtual void SetShowSelect(bool showSelect);
		virtual TitleBar* GetTitleBar();
		virtual void SetTitleBar(TitleBar *title);
		virtual CToolTip* GetToolTip();
		virtual void SetToolTip(CToolTip *toolTip);
		virtual int GetTop();
		virtual int GetVerticalPercent();
		virtual void SetVerticalPercent(int verticalPercent);
		virtual ScaleGrid* GetVGrid();
		virtual void SetVGrid(ScaleGrid *vGrid);
		virtual int GetWidth();
		virtual int GetWorkingAreaHeight();
		virtual void SetWorkingAreaHeight(int workingAreaHeight);
	public:
		void AddPlot(CPlot *plot);
		void AddShape(BaseShape *shape);
		bool ContainsShape(BaseShape *shape);
		vector<CPlot*> GetPlots(SORTTYPE sortType);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		vector<BaseShape*> GetShapes(SORTTYPE sortType);
		VScale* GetVScale(AttachVScale attachVScale);
		virtual void OnPaint(CPaint *paint, const RECT& rect);
		void RemovePlot(CPlot *plot);
		void RemoveShape(BaseShape *shape);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif