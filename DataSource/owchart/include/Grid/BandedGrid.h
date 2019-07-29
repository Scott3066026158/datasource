/*****************************************************************************\
*                                                                             *
* BandedGrid.h -  Banded grid functions, types, and definitions               *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/12/31 by Lord.                               *
*                                                                             *
*******************************************************************************/

#ifndef __BANDEDGRID_H__
#define __BANDEDGRID_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridEnums.h"
#include "BandedGridColumn.h"
#include "GridBand.h"
#include "Grid.h"

namespace OwLib
{
	class  BandedGridColumn;
	class  GridBand;

	class  BandedGridA : public GridA
	{
	protected:
		int GetAllVisibleBandsWidth();
	public:
		vector<GridBand*> m_bands;
		BandedGridA();
		virtual ~BandedGridA();
	public:
		void AddBand(GridBand *band);
		virtual void AddColumn(GridColumn *column);
		void ClearBands();
		virtual void ClearColumns();
		vector<GridBand*> GetBands();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		void InsertBand(int index, GridBand *band);
		virtual void OnSetEmptyClipRegion();
		void RemoveBand(GridBand *band);
		virtual void RemoveColumn(GridColumn *column);
		virtual void ResetHeaderLayout();
		virtual void Update();
	};
}

#endif