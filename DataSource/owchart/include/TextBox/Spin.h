/*************************************************************************************\
*                                                                                     *
* Spin.h -      Numeric up down functions, types, and definitions                     *
*                                                                                     *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                               *
*                                                                                     *
*               Copyright (c) 2016-2016, Lord's numeric up down. All rights reserved. *
*               Checked 2016/9/25 by Lord.                                            *
*                                                                                     *
**************************************************************************************/

#ifndef __SPIN_H__
#define __SPIN_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "TextBox.h"
#include "..\\Button\\Button.h"

namespace OwLib
{
	class  SpinA : public TextBoxA
	{
	private:
		int m_timerID;
		int m_tick;
	protected:
		bool m_autoFormat;
		int m_digit;
		ButtonA *m_downButton;
		ControlMouseEvent m_downButtonMouseDownEvent;
		ControlMouseEvent m_downButtonMouseUpEvent;
		bool m_isAdding;
		bool m_isReducing;
		double m_maximum;
		double m_minimum;
		bool m_showThousands;
		double m_step;
		ButtonA *m_upButton;
		ControlMouseEvent m_upButtonMouseDownEvent;
		ControlMouseEvent m_upButtonMouseUpEvent;
		static void DownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void DownButtonMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void UpButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void UpButtonMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
	public:
		SpinA();
		virtual ~SpinA();
		virtual bool AutoFormat();
		virtual void SetAutoFormat(bool autoFormat);
		virtual int GetDigit();
		virtual void SetDigit(int digit);
		virtual ButtonA* GetDownButton();
		virtual bool IsAdding();
		virtual void SetIsAdding(bool isAdding);
		virtual bool IsReducing();
		virtual void SetIsReducing(bool isReducing);
		virtual double GetMaximum();
		virtual void SetMaximum(double maximum);
		virtual double GetMinimum();
		virtual void SetMinimum(double minimum);
		virtual bool ShowThousands();
		virtual void SetShowThousands(bool showThousands);
		virtual double GetStep();
		virtual void SetStep(double step);
		virtual void SetText(const wstring& text);
		virtual ButtonA* GetUpButton();
		virtual double GetValue();
		virtual void SetValue(double value);
	public:
		void Add();
		wstring FormatNum(wstring inputText);
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		wstring GetValueByDigit(double value, int digit);
		virtual void OnChar(wchar_t ch);
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaste();
		virtual void OnTimer(int timerID);
		virtual void OnValueChanged();
		void Reduce();
		virtual void SetProperty(const wstring& name, const wstring& value);
		void SetRegion();
		virtual void Update();
	};
}

#endif