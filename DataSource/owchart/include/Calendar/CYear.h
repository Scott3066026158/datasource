/*****************************************************************************\
*                                                                             *
* CYear.h -    Year functions, types, and definitions                         *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __CYEAR_H__
#define __CYEAR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CMonth.h"

namespace OwLib
{
	class  CYear
	{
	protected:
		int m_year;
		void CreateMonths();
	public:
		CYear(int year);
		virtual ~CYear();
		map<int,CMonth*> Months;
	};
}

#endif