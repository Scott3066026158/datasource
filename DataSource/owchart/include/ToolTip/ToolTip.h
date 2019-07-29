/*****************************************************************************\
*                                                                             *
* ToolTip.h -   Tool tip functions, types, and definitions                    *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's tool tip. All rights reserved.*
*                                                                             *
*******************************************************************************/

#ifndef __TOOLTIP_H__
#define __TOOLTIP_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Label\\Label.h"

namespace OwLib
{
	class  ToolTipA : public LabelA
	{
	private:
		int m_timerID;
	protected:
		int m_autoPopDelay;
		int m_initialDelay;
		POINT m_lastMousePoint;
		bool m_showAlways;
		bool m_useAnimation;
	protected:
		int m_remainAutoPopDelay;
		int m_remainInitialDelay;
	public:
		ToolTipA();
		virtual ~ToolTipA();
		virtual int GetAutoPopDelay();
		virtual void SetAutoPopDelay(int autoPopDelay);
		virtual int GetInitialDelay();
		virtual void SetInitialDelay(int initialDelay);
		virtual bool ShowAlways();
		virtual void SetShowAlways(bool showAlways);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void Hide();
		virtual void OnLoad();
		virtual void OnTimer(int timerID);
		virtual void OnVisibleChanged();
		virtual void Show();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif