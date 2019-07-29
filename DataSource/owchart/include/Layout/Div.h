/**********************************************************************************\
*                                                                                 *
* Div.h -     Div functions, types, and definitions                               *
*                                                                                 *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                           *
*                                                                                 *
*               Copyright (c) 2016-2016, Lord's scroll bar. All rights reserved.  *
*               Check right 2016/9/22 by Lord.                                    *
*                                                                                 *
***********************************************************************************/


#ifndef __DIV_H__
#define __DIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\Control.h"
#include "..\\ScrollBar\\ScrollBar.h"
#include "..\\ScrollBar\\HScrollBar.h"
#include "..\\ScrollBar\\VScrollBar.h"

namespace OwLib
{
	class  HScrollBarA;
	class  VScrollBarA;

	class  DivA : public ControlA
	{
	protected:
		bool m_allowDragScroll;
		HScrollBarA *m_hScrollBar;
		bool m_isDragScrolling;
		bool m_isDragScrolling2;
		bool m_readyToDragScroll;
		ControlKeyEvent m_scrollButtonKeyDownEvent;
		ControlMouseEvent m_scrollButtonMouseWheelEvent;
		bool m_showHScrollBar;
		bool m_showVScrollBar;
		POINT m_startMovePoint;
		int m_startMovePosX;
		int m_startMovePosY;
		DWORD m_startMoveTime;
		VScrollBarA *m_vScrollBar;
		ControlEvent m_vScrollBarScrolledEvent;
		static void ScrollButtonKeyDown(void *sender, char key, void *pInvoke);
		static void ScrollButtonMouseWheel(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
	public:
		DivA();
		virtual ~DivA();
		virtual bool AllowDragScroll();
		virtual void SetAllowDragScroll(bool allowDragScroll);
		HScrollBarA* GetHScrollBar();
		virtual bool ShowHScrollBar();
		virtual void SetShowHScrollBar(bool showHScrollBar);
		virtual bool IsDragScrolling();
		virtual bool ShowVScrollBar();
		virtual void SetShowVScrollBar(bool showVScrollBar);
		virtual VScrollBarA* GetVScrollBar();
	public:
		virtual int GetContentHeight();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		virtual POINT GetDisplayOffset();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void LineDown();
		virtual void LineLeft();
		virtual void LineRight();
		virtual void LineUp();
		virtual void OnDragReady(POINT *startOffset);
		virtual void OnDragScrollEnd();
		virtual void OnDragScrolling();
		virtual bool OnDragScrollPermit();
		virtual void OnDragScrollStart();
		virtual void OnKeyDown(char key);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual bool OnPreviewsMouseEvent(int eventID, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void PageDown();
		virtual void PageLeft();
		virtual void PageRight();
		virtual void PageUp();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
		virtual void UpdateScrollBar();
	};
}

#endif