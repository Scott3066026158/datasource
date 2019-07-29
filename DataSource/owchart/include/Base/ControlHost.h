/*****************************************************************************\
*                                                                             *
* ControlHost.h -Control host functions, types, and definitions               *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CONTROLHOST_H__
#define __CONTROLHOST_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Control.h"
#include "CStr.h"
#include "CPaint.h"
#include "GdiPaint.h"
#include "GdiPlusPaint.h"
#include "NativeBase.h"

namespace OwLib
{
	class  ControlA;
	class  NativeBase;

	class  ControlHost
	{
	public:
		ControlHost();
		virtual ~ControlHost();
		virtual NativeBase* GetNative();
		virtual void SetNative(NativeBase *native);
	public:
		virtual void ActiveMirror();
		virtual bool AllowOperate();
		virtual bool AllowPartialPaint();
		virtual void BeginInvoke(ControlA *control, void *args);
		virtual void Copy(string text);
		virtual ControlA* CreateInternalControl(ControlA *parent, const wstring& clsid);
        virtual CursorsA GetCursor();
		virtual int GetIntersectRect(LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect);
        virtual POINT GetMousePoint();
        virtual SIZE GetSize();
		virtual int GetUnionRect(LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect);
		virtual void Invalidate();
        virtual void Invalidate(const RECT& rect);
		virtual void Invoke(ControlA *control, void *args);
		virtual bool IsKeyPress(char key);
		virtual string Paste();
		virtual void SetAllowOperate(bool allowOperate);
		virtual void SetAllowPartialPaint(bool allowPartialPaint);
        virtual void SetCursor(CursorsA cursor);
		virtual void ShowToolTip(const wstring& text, const POINT& mp);
        virtual void StartTimer(int timerID, int interval);
        virtual void StopTimer(int timerID);
	};
}
#endif