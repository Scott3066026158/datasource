/*********************************************************************************\
*                                                                                 *
* HScrollBar.h - Horizontal scroll bar functions, types, and definitions          *
*                                                                                 *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                           *
*                                                                                 *
*               Copyright (c) 2016-2016, Lord's scroll bar. All rights reserved.  *
*                                                                                 *
***********************************************************************************/

#ifndef __HSCROLLBAR_H__
#define __HSCROLLBAR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "ScrollBar.h"

namespace OwLib
{
	class  HScrollBarA:public ScrollBarA
	{
	protected:
        ControlMouseEvent m_backButtonMouseDownEvent;
		ControlMouseEvent m_backButtonMouseUpEvent;
		static void BackButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void BackButtonMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
	public:
		HScrollBarA();
		virtual ~HScrollBarA();
		virtual wstring GetControlType();
		void OnBackButtonMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void OnBackButtonMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnDragScroll();
		virtual void OnLoad();
		virtual void Update();
	};
}

#endif