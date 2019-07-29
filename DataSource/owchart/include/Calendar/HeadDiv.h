/*****************************************************************************\
*                                                                             *
* HeadDiv.h -   HeadDiv functions, types, and definitions                     *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __HEADDIV_H__
#define __HEADDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "Calendar.h"
#include "DateTitle.h"

namespace OwLib
{
	class  ArrowButton;
	class  DateTitle;

	class  HeadDiv:public ControlA
	{
	protected:
		CalendarA *m_calendar;
		DateTitle *m_dateTitle;
		ArrowButton *m_lastBtn;
		ArrowButton *m_nextBtn;
		wstring m_weekStrings[7];
	public:
		HeadDiv(CalendarA *calendar);
		virtual ~HeadDiv();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual DateTitle* GetDateTitle();
		virtual void SetDateTitle(DateTitle *dateTitle);
		virtual ArrowButton* GetLastBtn();
		virtual void SetLastBtn(ArrowButton *lastBtn);
		virtual ArrowButton* GetNextBtn();
		virtual void SetNextBtn(ArrowButton *nextBtn);
	public:
		virtual wstring GetControlType();
		virtual void OnLoad();
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void Update();
	};
}

#endif