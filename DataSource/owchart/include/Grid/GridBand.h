/*****************************************************************************\
*                                                                             *
* GridBand.cs -  Grid band functions, types, and definitions                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/12/31 by Lord.                               *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDBAND_H__
#define __GRIDBAND_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridEnums.h"
#include "BandedGrid.h"
#include "BandedGridColumn.h"
#include "..\\Button\\Button.h"

namespace OwLib
{
	class  BandedGridA;
	class  BandedGridColumn;

	class  GridBand : public ButtonA
	{
	protected:
		bool m_allowResize;
		BandedGridA *m_grid;
		int m_index;
		GridBand *m_parentBand;
	protected:
		int m_beginWidth;
        POINT m_mouseDownPoint;
		int m_resizeState;
	public:
		vector<GridBand*> m_bands;
		vector<BandedGridColumn*> m_columns;
		GridBand();
		virtual ~GridBand();
		virtual bool AllowResize();
		virtual void SetAllowResize(bool allowResize);
		virtual BandedGridA* GetGrid();
		virtual void SetGrid(BandedGridA *grid);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual GridBand* GetParentBand();
		virtual void SetParentBand(GridBand *parentBand);
	public:
		void AddBand(GridBand *band);
		void AddColumn(BandedGridColumn *column);
		void ClearBands();
		void ClearColumns();
		vector<BandedGridColumn*> GetAllChildColumns();
		vector<GridBand*> GetBands();
		vector<BandedGridColumn*> GetColumns();
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertBand(int index, GridBand *band);
		void InsertColumn(int index, BandedGridColumn *column);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void RemoveBand(GridBand *band);
		void RemoveColumn(BandedGridColumn *column);
		virtual void ResetHeaderLayout();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif