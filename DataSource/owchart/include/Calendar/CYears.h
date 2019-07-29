/*****************************************************************************\
*                                                                             *
* CYears.h -    Years functions, types, and definitions                       *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __CYEARS_H__
#define __CYEARS_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CYear.h"

namespace OwLib
{
	class  CYears
	{
	public:
		CYears();
		virtual ~CYears();
		map<int,CYear*> Years;
		CYear* GetYear(int year);
	};
}

#endif