/*****************************************************************************\
*                                                                             *
* CheckBox.h -  Check box functions, types, and definitions                   *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's button. All rights reserved.  *
*               Checked 2016/10/8 by Lord.                                    *
*                                                                             *
*******************************************************************************/

#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "Button.h"

namespace OwLib
{
	class  CheckBoxA : public ButtonA
	{
	protected:
		HorizontalAlignA m_buttonAlign;
		_int64 m_buttonBackColor;
		_int64 m_buttonBorderColor;
		SIZE m_buttonSize;
		bool m_checked;
		wstring m_checkedBackImage;
		wstring m_checkHoveredBackImage;
		wstring m_checkPushedBackImage;
		wstring m_disableCheckedBackImage;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingButtonBackColor();
		virtual _int64 GetPaintingButtonBorderColor();
		virtual wstring GetPaintingBackImage();
	public:
		CheckBoxA();
		virtual ~CheckBoxA();
		virtual HorizontalAlignA GetButtonAlign();
		virtual void SetButtonAlign(HorizontalAlignA buttonAlign);
		virtual _int64 GetButtonBackColor();
		virtual void SetButtonBackColor(_int64 buttonBackColor);
		virtual _int64 GetButtonBorderColor();
		virtual void SetButtonBorderColor(_int64 buttonBorderColor);
		virtual SIZE GetButtonSize();
		virtual void SetButtonSize(SIZE buttonSize);
		virtual bool IsChecked();
		virtual void SetChecked(bool checked);
		virtual wstring GetCheckedBackImage();
		virtual void SetCheckedBackImage(const wstring& checkedBackImage);
		virtual wstring GetCheckHoveredBackImage();
		virtual void SetCheckHoveredBackImage(const wstring& checkHoveredBackImage);
		virtual wstring GetCheckPushedBackImage();
		virtual void SetCheckPushedBackImage(const wstring& checkPushedBackImage);
		virtual wstring GetDisableCheckedBackImage();
		virtual void SetDisableCheckedBackImage(const wstring& disableCheckedBackImage);
	public:
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnCheckedChanged();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintCheckButton(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif