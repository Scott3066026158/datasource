/*****************************************************************************\
*                                                                             *
* CDay.h -  Day functions, types, and definitions                             *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __CDAY_H__
#define __CDAY_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	class  CDay
	{
	protected:
		int m_day;
		int m_month;
		int m_year;
	public:
		CDay(int year, int month, int day);
		virtual ~CDay();
		int GetDay();
		int GetMonth();
		int GetYear();
	};
}
#endif