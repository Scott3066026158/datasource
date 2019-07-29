/********************************************************************************\
*                                                                                *
* DatePicker.h -  Date picker functions, types, and definitions                  *
*                                                                                *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                          *
*                                                                                *
*               Copyright (c) 2016-2016, Lord's date picker. All rights reserved.*
*               Checked 2016/9/25 by Lord.                                       *
*                                                                                *
*********************************************************************************/

#ifndef __DATEPICKER_H__
#define __DATEPICKER_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "TextBox.h"
#include "..\\Button\\Button.h"
#include "..\\Menu\\Menu.h"
#include "..\\Menu\\MenuItem.h"
#include "..\\Calendar\\Calendar.h"

namespace OwLib
{
	class DatePickerA : public TextBoxA
	{
	private:
		CalendarA *m_calendar;
		ButtonA *m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		ControlEvent m_selectedDayChangedEvent;
		MenuA *m_dropDownMenu;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void SelectedDayChanged(void *sender, void *pInvoke);
	public:
		DatePickerA();
		virtual ~DatePickerA();
		CalendarA* GetCalendar();
		ButtonA* GetDropDownButton();
		MenuA* GetDropDownMenu();
	public:
		virtual String GetControlType();
		virtual void OnDropDownOpening();
		virtual void OnLoad();
		virtual void OnValueChanged();
		virtual void Update();
	};
}

#endif