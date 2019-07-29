/*****************************************************************************\
*                                                                             *
* Calendar.h -   Calendar functions, types, and definitions                   *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __CALENDAR_H__
#define __CALENDAR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "CYears.h"
#include "CMonth.h"
#include "ArrowButton.h"
#include "DateTitle.h"
#include "DayButton.h"
#include "DayDiv.h"
#include "HeadDiv.h"
#include "MonthButton.h"
#include "MonthDiv.h"
#include "TimeDiv.h"
#include "YearButton.h"
#include "YearDiv.h"

namespace OwLib
{
	class  ArrowButton;
	class  DateTitle;
	class  DayButton;
	class  DayDiv;
	class  HeadDiv;
	class  MonthButton;
	class  MonthDiv;
	class  TimeDiv;
	class  YearButton;
	class  YearDiv;

	typedef enum  CalendarMode
	{
		CalendarMode_Day,
		CalendarMode_Month,
		CalendarMode_Year
	};

	class  CalendarA : public ControlA
	{
	private:
		int m_timerID;;
	protected:
		DayDiv *m_dayDiv;
		HeadDiv *m_headDiv;
		CalendarMode m_mode;
		int m_month;
		MonthDiv *m_monthDiv;
		CDay *m_selectedDay;
		TimeDiv *m_timeDiv;
		bool m_useAnimation;
		int m_year;
		YearDiv *m_yearDiv;
		CYears *m_years;
	public:
		CalendarA();
		virtual ~CalendarA();
		virtual DayDiv* GetDayDiv();
		virtual void SetDayDiv(DayDiv *dayDiv);
		virtual HeadDiv* GetHeadDiv();
		virtual void SetHeadDiv(HeadDiv *headDiv);
		virtual CalendarMode GetMode();
		virtual void SetMode(CalendarMode mode);
		virtual CMonth* GetMonth();
		virtual void SetMonth(CMonth *month);
		virtual MonthDiv* GetMonthDiv();
		virtual void SetMonthDiv(MonthDiv *monthDiv);
		virtual CDay* GetSelectedDay();
		virtual void SetSelectedDay(CDay *day);
		virtual TimeDiv* GetTimeDiv();
		virtual void SetTimeDiv(TimeDiv *timeDiv);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
		virtual YearDiv* GetYearDiv();
		virtual void SetYearDiv(YearDiv *yearDiv);
		virtual CYears* GetYears();
		virtual void SetYears(CYears *years);
	public:
		int DayOfWeek(int y, int m, int d);
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		CMonth* GetLastMonth(int year, int month);
		CMonth* GetNextMonth(int year, int month);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void GoLastMonth();
		void GoNextMonth();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnLoad();
		virtual void OnKeyDown(char key);
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
		virtual void OnSelectedTimeChanged();
		virtual void OnTimer(int timerID);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}
#endif