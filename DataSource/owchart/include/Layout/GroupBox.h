/*****************************************************************************\
*                                                                             *
* GroupBox.h -  Div functions, types, and definitions                         *
*                                                                             *
*            Version 4.00 ¡ï¡ï¡ï                                              *
*                                                                             *
*            Copyright (c) 2016-2016, Lord's layout. All rights reserved.     *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GROUPBOX_H__
#define __GROUPBOX_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Div.h"

namespace OwLib
{
	class  GroupBoxA : public DivA
	{
	public:
		GroupBoxA();
		virtual ~GroupBoxA();
	public:
		virtual wstring GetControlType();
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif