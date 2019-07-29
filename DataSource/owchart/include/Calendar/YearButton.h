/*****************************************************************************\
*                                                                             *
* YearButton.h -  Year button functions, types, and definitions               *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's Calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/


#ifndef __YEARBUTTON_H__
#define __YEARBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Calendar.h"

namespace OwLib
{
	class  CalendarA;

	class  YearButton:public ButtonA
	{
	protected:
		RECT m_bounds;
		CalendarA *m_calendar;
		bool m_visible;
		int m_year;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		YearButton(CalendarA *calendar);
		virtual ~YearButton();
		virtual RECT GetBounds();
		virtual void SetBounds(const RECT& bounds);
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetYear();
		virtual void SetYear(int year);
	public:
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintBackGround(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif