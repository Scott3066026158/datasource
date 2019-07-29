/*****************************************************************************\
*                                                                             *
* Window.h -  Window functions, types, and definitions                        *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's window. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __WINDOW_H__
#define __WINDOW_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "WindowFrame.h"

namespace OwLib
{
	class  WindowFrameA;

	typedef  void (*WindowClosingEvent)(void*, bool*, void*);

	class  WindowA : public ControlA
	{
	protected:
		int m_borderWidth;
		bool m_canResize;
		int m_captionHeight;
		WindowFrameA *m_frame;
		bool m_isDialog;
		int m_resizePoint;
		_int64 m_shadowColor;
		int m_shadowSize;
		POINT m_startMousePoint;
		RECT m_startRect;
	protected:
		void CallWindowClosingEvents(int eventID, bool *cancel);
		CursorsA GetResizeCursor(int state);
		vector<RECT> GetResizePoints();
		int GetResizeState();
	public:
		WindowA();
		virtual ~WindowA();
		virtual int GetBorderWidth();
		virtual void SetBorderWidth(int borderWidth);
		virtual int GetCaptionHeight();
		virtual void SetCaptionHeight(int captionHeight);
		virtual bool CanResize();
		virtual void SetCanResize(bool canResize);
		virtual WindowFrameA* GetFrame();
		virtual void SetFrame(WindowFrameA *frame);
		virtual bool IsDialog();
		virtual _int64 GetShadowColor();
		virtual void SetShadowColor(_int64 shadowColor);
		virtual int GetShadowSize();
		virtual void SetShadowSize(int shadowSize);
	public:
		virtual void BringToFront();
		virtual void Close();
		virtual wstring GetControlType();
		RECT GetDynamicPaintRect();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual bool OnDragBegin();
		virtual void OnDragReady(POINT *startOffset);
		virtual void OnMouseDown(POINT mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(POINT mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseUp(POINT mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void OnVisibleChanged();
		virtual void OnWindowClosing(bool *cancel);
		virtual void OnWindowClosed();
		virtual void SendToBack();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void ShowDialog();
	};
}
#endif