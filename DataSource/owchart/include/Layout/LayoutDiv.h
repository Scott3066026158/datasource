/*****************************************************************************\
*                                                                             *
* LayoutDiv.h -  Layout functions, types, and definitions                     *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's layout. All rights reserved.  *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __LAYOUTDIV_H__
#define __LAYOUTDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Div.h"

namespace OwLib
{
	class  LayoutDivA : public DivA
	{
	protected:
		bool m_autoWrap;
		LayoutStyleA m_layoutStyle;
	public:
		LayoutDivA();
		virtual ~LayoutDivA();
		virtual bool AutoWrap();
		virtual void SetAutoWrap(bool autoWrap);
		virtual LayoutStyleA GetLayoutStyle();
		virtual void SetLayoutStyle(LayoutStyleA layoutStyle);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual bool OnResetLayout();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif