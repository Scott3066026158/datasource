/*****************************************************************************\
*                                                                             *
* GridColumn.h -  Grid column functions, types, and definitions               *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDCOLUMN_H__
#define __GRIDCOLUMN_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridEnums.h"
#include "Grid.h"
#include "..\\Button\\Button.h"

namespace OwLib
{
	class  GridA;

	class  GridColumn : public ButtonA
	{
	protected:
		bool m_allowSort;
		bool m_allowResize;
		HorizontalAlignA m_cellAlign;
		wstring m_columnType;
		bool m_frozen;
		GridA *m_grid;
		RECT m_headerRect;
		int m_index;
		GridColumnSortMode m_sortMode;
	protected:
		int m_beginWidth;
        POINT m_mouseDownPoint;
		int m_resizeState;
	public:
		GridColumn();
		GridColumn(const wstring& text);
		virtual ~GridColumn();
		virtual bool AllowResize();
		virtual void SetAllowResize(bool allowResize);
		virtual bool AllowSort();
		virtual void SetAllowSort(bool allowSort);
		virtual HorizontalAlignA GetCellAlign();
		virtual void SetCellAlign(HorizontalAlignA cellAlign);
		virtual wstring GetColumnType();
		virtual void SetColumnType(wstring columnType);
		virtual bool IsFrozen();
		virtual void SetFrozen(bool frozen);
		virtual GridA* GetGrid();
		virtual void SetGrid(GridA *grid);
		virtual RECT GetHeaderRect();
		virtual void SetHeaderRect(RECT headerRect);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual GridColumnSortMode GetSortMode();
		virtual void SetSortMode(GridColumnSortMode sortMode);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual bool OnDragBegin();
		virtual void OnDragging();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif