/*****************************************************************************\
*                                                                             *
* GridCell.h -  Grid cell functions, types, and definitions                   *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDCELL_H__
#define __GRIDCELL_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CProperty.h"
#include "GridColumn.h"
#include "GridRow.h"
#include "Grid.h"

namespace OwLib
{
	class  GridColumn;
	class  GridRow;
	class  GridA;

	class  GridCellStyle
	{
	protected:
		HorizontalAlignA m_align;
		bool m_autoEllipsis;
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
	public:
		GridCellStyle();
		virtual ~GridCellStyle();
		virtual HorizontalAlignA GetAlign();
		virtual void SetAlign(HorizontalAlignA align);
		virtual bool AutoEllipsis();
		virtual void SetAutoEllipsis(bool autoEllipsis);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
	public:
		void Copy(GridCellStyle *style);
	};

	class  GridCell : public CProperty
	{
	protected:
		bool m_allowEdit;
		int m_colSpan;
		GridColumn *m_column;
		GridA *m_grid;
		wstring m_name;
		GridRow *m_row;
		int m_rowSpan;
		GridCellStyle *m_style;
		void *m_tag;
	public:
		GridCell();
		virtual ~GridCell();
		virtual bool AllowEdit();
		virtual void SetAllowEdit(bool allowEdit);
		virtual int GetColSpan();
		virtual void SetColSpan(int colSpan);
		virtual GridColumn* GetColumn();
		virtual void SetColumn(GridColumn *column);
		virtual GridA* GetGrid();
		virtual void SetGrid(GridA *grid);
		virtual wstring GetName();
		virtual void SetName(const wstring& name);
		virtual GridRow* GetRow();
		virtual void SetRow(GridRow *row);
		virtual int GetRowSpan();
		virtual void SetRowSpan(int rowSpan);
		virtual GridCellStyle* GetStyle();
		virtual void SetStyle(GridCellStyle *style);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual wstring GetText();
		virtual void SetText(const wstring& text);
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetPaintText();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual wstring GetString();
		virtual void OnAdd();
		virtual void OnPaint(CPaint *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnRemove();
        virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
		virtual void SetProperty(const wstring& name, const wstring& value);
        virtual void SetString(const wstring& value);
	};

	class  GridControlCell : public GridCell
	{
	protected:
		ControlA *m_control;
		ControlMouseEvent m_mouseDownEvent;
		ControlMouseEvent m_mouseMoveEvent;
		ControlMouseEvent m_mouseUpEvent;
		ControlMouseEvent m_mouseWheelEvent;
	protected:
		static void ControlMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void ControlMouseMove(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void ControlMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void ControlMouseWheel(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
	public:
		GridControlCell();
		virtual ~GridControlCell();
		ControlA* GetControl();
		void SetControl(ControlA *control);
		virtual wstring GetString();
		virtual wstring GetPaintText();
		virtual void OnAdd();
		virtual void OnControlMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnControlMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnControlMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnControlMouseWheel(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaint(CPaint *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnPaintControl(CPaint *paint, const RECT& rect, const RECT& clipRect);
		virtual void OnRemove();
		virtual void SetString(const wstring& value);
	};
}

#endif