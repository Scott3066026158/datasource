/*****************************************************************************\
*                                                                             *
* NativeBase.h -Base functions, types, and definitions                        *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*               Check right 2016/9/17 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __NATIVEBASE_H__
#define __NATIVEBASE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "Control.h"
#include "CStr.h"
#include "CPaint.h"
#include "GdiPaint.h"
#include "GdiPlusPaint.h"
#include "ControlHost.h"
#include "WinHost.h"

namespace OwLib
{
	typedef enum  SORTTYPE
	{
		SORTTYPE_NONE,
		SORTTYPE_ASC,
		SORTTYPE_DESC
	};

	class  ControlA;
	class  ControlHost;
	class  WinHost;
	class  NativeBase
	{
	protected:
		bool m_allowScaleSize;
		SIZE m_displaySize;
		POINT m_drawBeginPoint;
		RECT m_dragBeginRect;
		POINT m_dragStartOffset;
		ControlA *m_exportingControl;
		ControlHost *m_host;
		NativeBase *m_mirrorHost;
		MirrorMode m_mirrorMode;
		float m_opacity;
		CPaint *m_paint;
		POINT m_mouseDownPoint;
		wstring m_resourcePath;
		int m_rotateAngle;
		SIZE m_scaleSize;
		map<int, ControlA*> m_timers;
		ControlA* FindControl(const POINT& mp, vector<ControlA*> *controls);
		ControlA* FindControl(const wstring& name, vector<ControlA*> *controls);
		ControlA* FindPreviewsControl(ControlA *control);
		ControlA* FindWindow(ControlA *control);
		float GetPaintingOpacity(ControlA *control);
		wstring GetPaintingResourcePath(ControlA *control);
		bool GetSortedControls(ControlA *parent, vector<ControlA*> *sortedControls);
		void GetTabStopControls(ControlA *control, vector<ControlA*> *tabStopControls);
		bool IsPaintEnabled(ControlA *control);
		void RenderControls(const RECT& rect, vector<ControlA*> *controls, wstring resourcePath, float opacity);
		void SetCursor(ControlA *control);
		void SetPaint(int offsetX, int offsetY, const RECT& clipRect, wstring resourcePath, float opacity);
	public:
		ControlA *m_draggingControl;
		ControlA *m_focusedControl;
		ControlA *m_mouseDownControl;
		ControlA *m_mouseMoveControl;
	public:
		vector<ControlA*> m_controls;
		vector<NativeBase*> m_mirrors;
		NativeBase();
		virtual ~NativeBase();
		bool AllowScaleSize();
		void SetAllowScaleSize(bool allowScaleSize);
		CursorsA GetCursor();
		void SetCursor(CursorsA cursor);
		SIZE GetDisplaySize();
		void SetDisplaySize(SIZE displaySize);
		ControlA* GetFocusedControl();
		void SetFocusedControl(ControlA *focusedControl);
		ControlHost* GetHost();
		void SetHost(ControlHost *host);
		ControlA* GetHoveredControl();
		NativeBase* GetMirrorHost();
		MirrorMode GetMirrorMode();
		void SetMirrorMode(MirrorMode mirrorMode);
		POINT GetMousePoint();
		float GetOpacity();
		void SetOpacity(float opacity);
		CPaint* GetPaint();
		void SetPaint(CPaint *paint);
		ControlA* GetPushedControl();
		wstring GetResourcePath();
		void SetResourcePath(const wstring& resourcePath);
		int GetRotateAngle();
		void SetRotateAngle(int rotateAngle);
		SIZE GetScaleSize();
		void SetScaleSize(SIZE scaleSize);
	public:
		void AddControl(ControlA *control);
		void AddMirror(NativeBase *mirrorHost, ControlA *control);
		void BringToFront(ControlA *control);
		void CancelDragging();
		void ClearControls();
		int ClientX(ControlA *control);
		int ClientY(ControlA *control);
		bool ContainsControl(ControlA *control);
        void ExportToImage(const wstring& exportPath);
        void ExportToImage(const wstring& exportPath, ControlA *control);
		ControlA* FindControl(const POINT& mp);
		ControlA* FindControl(const POINT& mp, ControlA *parent);
		ControlA* FindControl(const wstring& name);
		vector<ControlA*> GetControls();
		void InsertControl(int index, ControlA *control);
		void Invalidate();
		void Invalidate(ControlA *control);
		void Invalidate(const RECT& rect);
		bool OnChar(wchar_t key);
		void OnDoubleClick(MouseButtonsA button, int clicks, int delta);
		void OnKeyDown(char key);
		void OnKeyUp(char key);
		void OnMouseDown(MouseButtonsA button, int clicks, int delta);
		void OnMouseLeave(MouseButtonsA button, int clicks, int delta);
		void OnMouseMove(MouseButtonsA button, int clicks, int delta);
		void OnMouseUp(MouseButtonsA button, int clicks, int delta);
		void OnMouseWheel(MouseButtonsA button, int clicks, int delta);
		void OnPaint(const RECT& rect);
		bool OnPreviewsKeyEvent(int eventID, char key);
		bool OnPreviewsMouseEvent(int eventID, ControlA *control, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void OnResize();
		void OnTimer(int timerID);
		void RemoveControl(ControlA *control);
		void RemoveMirror(ControlA *control);
		void SendToBack(ControlA *control);
		void SetAlign(vector<ControlA*> *controls);
		void SetAnchor(vector<ControlA*> *controls, SIZE oldSize);
		void SetDock(vector<ControlA*> *controls);
		void StartTimer(ControlA *control, int timerID, int interval);
		void StopTimer(int timerID);
		void Update();
	};
}
#endif