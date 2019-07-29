/*****************************************************************************\
*                                                                             *
* GridEnums.h -  Table types                                                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDENUMS_H__
#define __GRIDENUMS_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	typedef enum  GridColumnSortMode
	{
		GridColumnSortMode_Asc,
		GridColumnSortMode_Desc,
		GridColumnSortMode_None
	};

	typedef enum  GridSelectionMode
	{
		GridSelectionMode_SelectCell,
		GridSelectionMode_SelectFullColumn,
		GridSelectionMode_SelectFullRow,
		GridSelectionMode_SelectNone
	};

	typedef enum  GridCellEditMode
	{
        GridCellEditMode_DoubleClick,
        GridCellEditMode_None,
        GridCellEditMode_SingleClick
	};
}

#endif