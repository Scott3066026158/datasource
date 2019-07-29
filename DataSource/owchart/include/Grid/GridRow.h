/*****************************************************************************\
*                                                                             *
* GridRow.h -   Grid row functions, types, and definitions                    *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDROW_H__
#define __GRIDROW_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CProperty.h"
#include "GridCell.h"
#include "Grid.h"

namespace OwLib
{
	class  GridCell;
	class  GridA;

	class  GridRowStyle
	{
	protected:
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
		_int64 m_hoveredBackColor;
		_int64 m_hoveredForeColor;
		_int64 m_selectedBackColor;
		_int64 m_selectedForeColor;
	public:
		GridRowStyle();
		virtual ~GridRowStyle();
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual _int64 GetHoveredBackColor();
		virtual void SetHoveredBackColor(_int64 hoveredBackColor);
		virtual _int64 GetHoveredForeColor();
		virtual void SetHoveredForeColor(_int64 hoveredForeColor);
		virtual _int64 GetSelectedBackColor();
		virtual void SetSelectedBackColor(_int64 selectedBackColor);
		virtual _int64 GetSelectedForeColor();
		virtual void SetSelectedForeColor(_int64 selectedForeColor);
	public:
		void Copy(GridRowStyle *style);
	};
	class  GridRow : public CProperty
	{
	protected:
		bool m_allowEdit;
		RECT m_bounds;
		ControlA *m_editButton;
		GridA *m_grid;
		int m_height;
		int m_horizontalOffset;
		int m_index;
		void *m_tag;
		bool m_visible;
		int m_visibleIndex;
	public:
		vector<GridCell*> m_cells;
		int m_editState;
		GridRow();
		virtual ~GridRow();
		virtual bool AllowEdit();
		virtual void SetAllowEdit(bool allowEdit);
		virtual RECT GetBounds();
		virtual void SetBounds(RECT bounds);
		virtual ControlA* GetEditButton();
		virtual void SetEditButton(ControlA *editButton);
		virtual GridA* GetGrid();
		virtual void SetGrid(GridA *grid);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual int GetHorizontalOffset();
		virtual void SetHorizontalOffset(int horizontalOffset);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetVisibleIndex();
		virtual void SetVisibleIndex(int visibleIndex);
	public:
		void AddCell(int columnIndex, GridCell *cell);
		void AddCell(const wstring& columnName, GridCell *cell);
		void ClearCells();
		vector<GridCell*> GetCells();
		GridCell* GetCell(int columnIndex);
		GridCell* GetCell(wstring columnName);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnAdd();
		virtual void OnPaint(CPaint *paint, const RECT& clipRect, bool isAlternate);
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect, bool isAlternate);
		virtual void OnRemove();
		void RemoveCell(int columnIndex);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif