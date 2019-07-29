/*****************************************************************************\
*                                                                             *
* DayButton.h -  Day button functions, types, and definitions                 *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __DAYBUTTON_H__
#define __DAYBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "Calendar.h"

namespace OwLib
{
	class  CalendarA;

	class  DayButton
	{
	protected:
		RECT m_bounds;
		CalendarA *m_calendar;
		CDay *m_day;
		bool m_inThisMonth;
		bool m_selected;
		bool m_visible;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		DayButton(CalendarA *calendar);
		virtual ~DayButton();
		virtual RECT GetBounds();
		virtual void SetBounds(const RECT& bounds);
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual CDay* GetDay();
		virtual void SetDay(CDay *day);
		virtual bool InThisMonth();
		virtual void SetThisMonth(bool inThisMonth);
		virtual bool IsSelected();
		virtual void SetSelected(bool selected);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintBackGround(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif