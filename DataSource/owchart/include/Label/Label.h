/*****************************************************************************\
*                                                                             *
* Label.h -  Label functions, types, and definitions                          *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's label. All rights reserved.   *
*                                                                             *
*******************************************************************************/

#ifndef __LABEL_H__
#define __LABEL_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	class  LabelA : public ControlA
	{
	protected:
		ContentAlignmentA m_textAlign;
	public:
		LabelA();
		virtual ~LabelA();
		virtual ContentAlignmentA GetTextAlign();
		virtual void SetTextAlign(ContentAlignmentA textAlign);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void OnPrePaint(CPaint *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif