/*****************************************************************************\
*                                                                             *
* TimeDiv.h -  Time div functions, types, and definitions                      *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's Calendar. All rights reserved.*
*                                                                             *
*******************************************************************************/
#ifndef __TIMEDIV_H__
#define __TIMEDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Calendar.h"
#include "..\\TextBox\\Spin.h"

namespace OwLib
{
	class  CalendarA;

	class  TimeDiv 
	{
	protected:
		static void SelectedTimeChanged(void *sender, void *pInvoke);
	protected:
		CalendarA *m_calendar;
		int m_height;
		SpinA *m_spinHour;
		SpinA *m_spinMinute;
		SpinA *m_spinSecond;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		TimeDiv(CalendarA *calendar);
		virtual ~TimeDiv();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual int GetHour();
		virtual void SetHour(int hour);
		virtual int GetMinute();
		virtual void SetMinute(int minute);
		virtual int GetSecond();
		virtual void SetSecond(int second);
	public:
		void OnLoad();
		void OnPaint(CPaint *paint, const RECT& clipRect);
		void OnSelectedTimeChanged();
		void OnTimer();
		void Update();
	};
}
#endif