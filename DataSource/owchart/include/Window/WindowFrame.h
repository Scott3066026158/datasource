/*****************************************************************************\
*                                                                             *
* WindowFrameA.h -   Window frame functions, types, and definitions           *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
******************************************************************************/

#ifndef __WINDOWFRAME_H__
#define __WINDOWFRAME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Window.h"

namespace OwLib
{
	class  WindowFrameA : public ControlA
	{
	public:
		WindowFrameA();
		virtual ~WindowFrameA();
	public:
		virtual bool ContainsPoint(const POINT& point);
		virtual wstring GetControlType();
		virtual void Invalidate();
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
	};
}
#endif