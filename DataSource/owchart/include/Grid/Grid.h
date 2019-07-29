/*****************************************************************************\
*                                                                             *
* Grid.h -    Grid functions, types, and definitions                          *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRID_H__
#define __GRID_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridColumn.h"
#include "GridRow.h"
#include "GridCell.h"
#include "..\\ScrollBar\\HScrollBar.h"
#include "..\\ScrollBar\\VScrollBar.h"
#include "..\\Layout\\Div.h"
#include "..\\TextBox\\TextBox.h"

namespace OwLib
{
	class  GridCell;
	class  GridColumn;
	class  GridRow;
	class  GridRowStyle;
	
	typedef  void (*GridCellEvent) (void*, GridCell*, void*);

	typedef  void (*GridCellMouseEvent)(void*, GridCell*, const POINT&, MouseButtonsA, int, int, void*);

	class  GridRowCompare
	{
	public:
		int m_columnIndex;
		int m_type;
	public:
		GridRowCompare();
		virtual ~GridRowCompare();
		bool operator()(GridRow *x, GridRow *y);
	};

	class  GridA;

	class  GridSort
	{
	public:
		GridSort();
		virtual ~GridSort();
	public:
		virtual void SortColumn(GridA *grid, GridColumn *column, GridColumnSortMode sortMode);
	};

	class  GridA:public DivA
	{
	private:
		int m_timerID;
	protected:
		ControlEvent m_editTextBoxLostFocusEvent;
		ControlKeyEvent m_editTextBoxKeyDownEvent;
	protected:
		bool m_allowDragRow;
		bool m_allowHoveredRow;
		GridRowStyle *m_alternateRowStyle;
		GridCellEditMode m_cellEditMode;
		GridCell *m_editingCell;
		TextBoxA *m_editTextBox;
		_int64 m_gridLineColor;
		bool m_hasUnVisibleRow;
		bool m_headerVisible;
		int m_headerHeight;
		int m_horizontalOffset;
		GridCell *m_hoveredCell;
		GridRow *m_hoveredRow;
		POINT m_mouseDownPoint;
		bool m_multiSelect;
		GridRowStyle *m_rowStyle;
		GridSelectionMode m_selectionMode;
		GridSort *m_sort;
		bool m_useAnimation;
		int m_verticalOffset;
		void CallCellEvents(int eventID, GridCell *cell);
		void CallCellMouseEvents(int eventID, GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void MouseEvent(const POINT& mp, MouseButtonsA button, int clicks, int delta, int state);
		static void EditTextBoxLostFocus(void *sender, void *pInvoke);
		static void EditTextBoxKeyDown(void *sender, char key, void *pInvoke);
	public:
		bool m_lockUpdate;
		vector<GridCell*> m_selectedCells;
		vector<GridColumn*> m_selectedColumns;
		vector<GridRow*> m_selectedRows;
		int GetAllVisibleColumnsWidth();
		int GetAllVisibleRowsHeight();
	public:
		vector<GridRow*> m_animateAddRows;
		vector<GridRow*> m_animateRemoveRows;
		vector<GridColumn*> m_columns;
		GridRow *m_editingRow;
		vector<GridRow*> m_rows;
		GridA();
		virtual ~GridA();
		virtual bool AllowDragRow();
		virtual void SetAllowDragRow(bool allowDragRow);
		virtual bool AllowHoveredRow();
		virtual void SetAllowHoveredRow(bool allowHoveredRow);
		virtual GridRowStyle* GetAlternateRowStyle();
		virtual void SetAlternateRowStyle(GridRowStyle *alternateRowStyle);
		virtual GridCellEditMode GetCellEditMode();
		virtual void SetCellEditMode(GridCellEditMode cellEditMode);
		virtual TextBoxA* GetEditTextBox();
		virtual _int64 GetGridLineColor();
		virtual void SetGridLineColor(_int64 gridLineColor);
		virtual bool IsHeaderVisible();
		virtual void SetHeaderVisible(bool headerVisible);
		virtual int GetHeaderHeight();
		virtual void SetHeaderHeight(int headerHeight);
		virtual int GetHorizontalOffset();
		virtual void SetHorizontalOffset(int horizontalOffset);
		virtual GridCell* GetHoveredCell();
		virtual GridRow* GetHoveredRow();
		virtual bool IsMultiSelect();
		virtual void SetMultiSelect(bool multiSelect);
		virtual GridRowStyle* GetRowStyle();
		virtual void SetRowStyle(GridRowStyle *rowStyle);
		virtual vector<GridCell*> GetSelectedCells();
		virtual void SetSelectedCells(vector<GridCell*> selectedCells);
		virtual vector<GridColumn*> GetSelectedColumns();
		virtual void SetSelectedColumns(vector<GridColumn*> selectedColumns);
		virtual vector<GridRow*> GetSelectedRows();
		virtual void SetSelectedRows(vector<GridRow*> selectedRows);
		virtual GridSelectionMode GetSelectionMode();
		virtual void SetSelectionMode(GridSelectionMode selectionMode);
		virtual GridSort* GetSort();
		virtual void SetSort(GridSort *sort);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
		virtual int GetVerticalOffset();
		virtual void SetVerticalOffset(int verticalOffset);
	public:
		virtual void AddColumn(GridColumn *column);
		void AddRow(GridRow *row);
		void AnimateAddRow(GridRow *row);
		void AnimateRemoveRow(GridRow *row);
		void BeginUpdate();
		void Clear();
		virtual void ClearColumns();
		void ClearRows();
		void EndUpdate();
		GridColumn* GetColumn(int columnIndex);
		GridColumn* GetColumn(const wstring& columnName);
		vector<GridColumn*> GetColumns();
		virtual int GetContentHeight();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		virtual POINT GetDisplayOffset();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		GridRow* GetRow(const POINT& mp);
		GridRow* GetRow(int rowIndex);
		vector<GridRow*> GetRows();
		void GetVisibleRowsIndex(double visiblePercent, int *firstVisibleRowIndex, int *lastVisibleRowIndex);
		void InsertRow(int index, GridRow *row);
		bool IsRowVisible(GridRow *row, double visiblePercent);
		void MoveRow(int oldIndex, int newIndex);
		virtual void OnCellClick(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnCellEditBegin(GridCell *cell);
		virtual void OnCellEditEnd(GridCell *cell);
		virtual void OnCellMouseDown(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnCellMouseEnter(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnCellMouseLeave(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnCellMouseMove(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnCellMouseUp(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnLostFocus();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseLeave(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintEditTextBox(GridCell *cell, CPaint *paint, const RECT& rect, const RECT& clipRect);
		virtual void OnRowEditBegin(GridRow *row);
		virtual void OnRowEditEnd();
		virtual void OnSelectedCellsChanged();
		virtual void OnSelectedColumnsChanged();
		virtual void OnSelectedRowsChanged();
		virtual void OnSetEmptyClipRegion();
		virtual void OnTimer(int timerID);
		virtual void OnVisibleChanged();
		virtual void RemoveColumn(GridColumn *column);
		void RemoveRow(GridRow *row);
		virtual void ResetHeaderLayout();
		GridRow* SelectFrontRow();
		GridRow* SelectNextRow();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void SortColumn(GridA *grid, GridColumn *column, GridColumnSortMode sortMode);
		virtual void Update();
		void UpdateSortColumn();
	};
}

#endif