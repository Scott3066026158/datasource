/*****************************************************************************\
*                                                                             *
* ArrowButton.h -  Arrow button functions, types, and definitions             *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __ARROWBUTTON_H__
#define __ARROWBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Calendar.h"
#include "YearDiv.h"

namespace OwLib
{
	class  CalendarA;

	class  ArrowButton:public ButtonA
	{
	protected:
		CalendarA *m_calendar;
		bool m_toLast;
	public:
		ArrowButton(CalendarA *calendar);
		virtual ~ArrowButton();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual bool IsToLast();
		virtual void SetToLast(bool toLast);
	public:
		virtual wstring GetControlType();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif