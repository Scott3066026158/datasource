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

#ifndef __DATETIMEPICKER_H__
#define __DATETIMEPICKER_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "TextBox.h"
#include "..\\Button\\Button.h"
#include "..\\Menu\\Menu.h"
#include "..\\Menu\\MenuItem.h"
#include "..\\Calendar\\Calendar.h"

namespace OwLib
{
	class  DateTimePickerA : public TextBoxA
	{
	protected:
		CalendarA *m_calendar;
		wstring m_customFormat;
		ButtonA *m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		MenuA *m_dropDownMenu;
		ControlEvent m_selectedTimeChangedEvent;
		bool m_showTime;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void SelectedTimeChanged(void *sender, void *pInvoke);
	public:
		DateTimePickerA();
		virtual ~DateTimePickerA();
		virtual CalendarA* GetCalendar();
		virtual wstring GetCustomFormat();
		virtual void SetCustomFormat(const wstring& customFormat);
		virtual ButtonA* GetDropDownButton();
		virtual MenuA* GetDropDownMenu();
		virtual bool ShowTime();
		virtual void SetShowTime(bool showTime);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnDropDownOpening();
		virtual void OnLoad();
		virtual void OnSelectedTimeChanged();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif