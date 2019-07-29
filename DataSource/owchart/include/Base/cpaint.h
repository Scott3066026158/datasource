/*****************************************************************************\
*                                                                             *
* CPaint.h -    Paint functions, types, and definitions                       *
*                                                                             *
*               Version 4.00  ¡ï¡ï¡ï¡ï¡ï                                      *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
******************************************************************************/

#ifndef __CPAINT_H__
#define __CPAINT_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	struct  ANCHOR
	{
	public:
		bool bottom;
		bool left;
		bool right;
		bool top;
		ANCHOR()
		{
			bottom = false;
			left = false;
			right = false;
			top = false;
		}
		ANCHOR(bool left, bool top, bool right, bool bottom)
		{
			this->left = left;
			this->top = top;
			this->right = right;
			this->bottom = bottom;
		}
	};

	typedef enum  ContentAlignmentA
	{
        ContentAlignmentA_BottomCenter,
        ContentAlignmentA_BottomLeft,
        ContentAlignmentA_BottomRight,
        ContentAlignmentA_MiddleCenter,
        ContentAlignmentA_MiddleLeft,
        ContentAlignmentA_MiddleRight,
        ContentAlignmentA_TopCenter,
        ContentAlignmentA_TopLeft,
        ContentAlignmentA_TopRight,
	};

	typedef enum  CursorsA
	{
		CursorsA_AppStarting,
        CursorsA_Arrow,
        CursorsA_Cross,
        CursorsA_Hand,
		CursorsA_Help,
		CursorsA_IBeam,
		CursorsA_No,
        CursorsA_SizeAll,
        CursorsA_SizeNESW,
        CursorsA_SizeNS,
        CursorsA_SizeNWSE,
        CursorsA_SizeWE,
		CursorsA_UpArrow,
		CursorsA_WaitCursor
	};

	typedef enum  DockStyleA
	{
		DockStyleA_Bottom,
		DockStyleA_Fill,
		DockStyleA_Left,
		DockStyleA_None,
		DockStyleA_Right,
		DockStyleA_Top
	};

	typedef enum  HorizontalAlignA
	{
		HorizontalAlignA_Center,
		HorizontalAlignA_Right,
		HorizontalAlignA_Inherit,
		HorizontalAlignA_Left
	};

	typedef enum  VerticalAlignA
	{
		VerticalAlignA_Bottom,
		VerticalAlignA_Inherit,
		VerticalAlignA_Middle,
		VerticalAlignA_Top
	};

	typedef enum  LayoutStyleA
	{
		LayoutStyleA_BottomToTop,
		LayoutStyleA_LeftToRight,
		LayoutStyleA_None,
		LayoutStyleA_RightToLeft,
		LayoutStyleA_TopToBottom
	};

	typedef enum  MouseButtonsA
	{
		MouseButtonsA_Left,
		MouseButtonsA_None,
		MouseButtonsA_Right
	};

	typedef enum  MirrorMode
	{
		MirrorMode_BugHole,
		MirrorMode_None,
		MirrorMode_Shadow
	};

	static _int64 COLOR_CONTROL = (_int64)-200000000001;
	static _int64 COLOR_CONTROLBORDER = (_int64)-200000000002;
	static _int64 COLOR_CONTROLTEXT = (_int64)-200000000003;
    static _int64 COLOR_DISABLEDCONTROL = (_int64)-200000000004;
    static _int64 COLOR_DISABLEDCONTROLTEXT = (_int64)-200000000005;
	static _int64 COLOR_HOVEREDCONTROL = (_int64)-200000000006;
	static _int64 COLOR_PUSHEDCONTROL = (_int64)-200000000007;
	static _int64 COLOR_EMPTY = (_int64)-200000000000;

	struct  POINTF
	{
	public:
		float x;
		float y;
	};

	struct  SIZEF
	{
	public:
		float cx;
		float cy;
	};

	struct  RECTF
	{
	public:
		float left;
		float top;
		float right;
		float bottom;
	};

	class  FONT
	{
	public:
		wstring m_fontFamily;
		float m_fontSize;
		bool m_bold;
		bool m_underline;
		bool m_italic;
		bool m_strikeout;
		FONT()
		{
			m_fontFamily = L"Simsun";
			m_fontSize = 12;
			m_bold = false;
			m_underline = false;
			m_italic = false;
			m_strikeout = false;
		}
		FONT(const wstring& fontFamily, float fontSize, bool bold, bool underline, bool italic)
		{
			m_fontFamily = fontFamily;
			m_fontSize = fontSize;
			m_bold = bold;
			m_underline = underline;
			m_italic = italic;
			m_strikeout = false;
		}
		FONT(const wstring& fontFamily, float fontSize, bool bold, bool underline, bool italic, bool strikeout)
		{
			m_fontFamily = fontFamily;
			m_fontSize = fontSize;
			m_bold = bold;
			m_underline = underline;
			m_italic = italic;
			m_strikeout = strikeout;
		}
	public:
		void Copy(FONT *font)
		{
			m_fontFamily = font->m_fontFamily;
			m_fontSize = font->m_fontSize;
			m_bold = font->m_bold;
			m_underline = font->m_underline;
			m_italic = font->m_italic;
			m_strikeout = font->m_strikeout;
		}
	};

	struct  PADDING
	{
	public:
		int bottom;
		int left;
		int right;
		int top;
		PADDING()
		{
			bottom = 0;
			left = 0;
			right = 0;
			top = 0;
		}
		PADDING(int all)
		{
			bottom = all;
			left = all;
			right = all;
			top = all;
		}
		PADDING(int left, int top, int right, int bottom)
		{
			this->left = left;
			this->top = top;
			this->right = right;
			this->bottom = bottom;
		}
	};

	class  CTouch
	{
	public:
		POINT m_point;
		int m_tapCount;
		int m_timestamp;
	public:
		CTouch()
		{
			m_point.x = 0;
			m_point.y = 0;
			m_tapCount = 0;
			m_timestamp = 0;
		}
		~CTouch()
		{
		}
	};

	class  CPaint
	{
	public:
		CPaint();
		virtual ~CPaint();
	public:
		virtual void AddArc(const RECT& rect, float startAngle, float sweepAngle);
		virtual void AddBezier(POINT *apt, int cpt);
		virtual void AddCurve(POINT *apt, int cpt);
		virtual void AddEllipse(const RECT& rect);
		virtual void AddLine(int x1, int y1, int x2, int y2);
		virtual void AddRect(const RECT& rect);
		virtual void AddPie(const RECT& rect, float startAngle, float sweepAngle);
		virtual void AddText(LPCWSTR strText, FONT *font, const RECT& rect);
		virtual void BeginExport(const wstring& exportPath, const RECT& rect);
		virtual void BeginPaint(HDC hDC, const RECT& wRect, const RECT& pRect);
		virtual void BeginPath();
		virtual void ClearCaches();
		virtual void ClipPath();
		virtual void CloseFigure();
		virtual void ClosePath();
		virtual void DrawArc(_int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle);
		virtual void DrawBezier(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawCurve(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawEllipse(_int64 dwPenColor, float width, int style, const RECT& rect);
		virtual void DrawEllipse(_int64 dwPenColor, float width, int style, int left, int top, int right, int bottom);
		virtual void DrawImage(LPCWSTR imagePath, const RECT& rect);
		virtual void DrawLine(_int64 dwPenColor, float width, int style, const POINT& x, const POINT& y);
		virtual void DrawLine(_int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2);
		virtual void DrawPath(_int64 dwPenColor, float width, int style);
		virtual void DrawPie(_int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle);
		virtual void DrawPolygon(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawPolyline(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawRect(_int64 dwPenColor, float width, int style, int left, int top, int right, int bottom);
		virtual void DrawRect(_int64 dwPenColor, float width, int style, const RECT& rect);
		virtual void DrawRoundRect(_int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius);
		virtual void DrawText(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect);
		virtual void DrawText(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect);
		virtual void DrawTextAutoEllipsis(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect);
		virtual void EndExport();
		virtual void EndPaint();
		virtual void ExcludeClipPath();
		virtual void FillEllipse(_int64 dwPenColor, const RECT& rect);
		virtual void FillGradientEllipse(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle);
		virtual void FillGradientPath(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle);
		virtual void FillGradientPolygon(_int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle);
		virtual void FillGradientRect(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle);
		virtual void FillPath(_int64 dwPenColor);
		virtual void FillPie(_int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle);
		virtual void FillPolygon(_int64 dwPenColor, POINT *apt, int cpt);
		virtual void FillRect(_int64 dwPenColor, const RECT& rect);
		virtual void FillRect(_int64 dwPenColor, int left, int top, int right, int bottom);
		virtual void FillRoundRect(_int64 dwPenColor, const RECT& rect, int cornerRadius);
		virtual _int64 GetColor(_int64 dwPenColor);
		virtual _int64 GetPaintColor(_int64 dwPenColor);
		virtual POINT GetOffset();
		virtual POINT Rotate(const POINT& op, const POINT& mp, int angle);
		virtual void SetClip(const RECT& rect);
		virtual void SetLineCap(int startLineCap, int endLineCap);
		virtual void SetOffset(const POINT& offset);
		virtual void SetOpacity(float opacity);
        virtual void SetResourcePath(const wstring& resourcePath);
		virtual void SetRotateAngle(int rotateAngle);
		virtual void SetScaleFactor(double scaleFactorX, double scaleFactorY);
		virtual void SetSmoothMode(int smoothMode);
		virtual void SetTextQuality(int textQuality);
		virtual bool SupportTransparent();
		virtual SIZE TextSize(LPCWSTR strText, FONT *font);
		virtual SIZEF TextSizeF(LPCWSTR strText, FONT *font);
	};

	class  COLOR
	{
	public:
		static _int64 ARGB(int r, int g, int b);
		static _int64 ARGB(int a, int r, int g, int b);
		static void ToARGB(CPaint *paint, _int64 dwPenColor, int *a, int *r, int *g, int *b);
		static _int64 RatioColor(CPaint *paint, _int64 originalColor, double ratio);
		static _int64 Reverse(CPaint *paint, _int64 originalColor);
	};
}

#endif