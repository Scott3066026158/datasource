/*****************************************************************************\
*                                                                             *
* MonthButton.h -  Month button functions, types, and definitions             *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's Calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/


#ifndef __MONTHBUTTON_H__
#define __MONTHBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Calendar.h"

namespace OwLib
{
	class  CalendarA;

	class  MonthButton:public ButtonA
	{
	protected:
		RECT m_bounds;
		CalendarA *m_calendar;
		int m_month;
		bool m_visible;
		int m_year;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		MonthButton(CalendarA *calendar);
		virtual ~MonthButton();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual RECT GetBounds();
		virtual void SetBounds(const RECT& bounds);
		virtual int GetMonth();
		virtual void SetMonth(int month);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetYear();
		virtual void SetYear(int year);
	public:
		virtual wstring GetMonthStr();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintBackGround(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif