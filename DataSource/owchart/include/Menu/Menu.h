/*********************************************************************************\
*                                                                                 *
* Menu.h -      Menu functions, types, and definitions                            *
*                                                                                 *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                           *
*                                                                                 *
*               Copyright (c) 2016-2016, Lord's menu. All rights reserved.        *
*               Checked in 2016/10/09 by Lord.                                    *
*                                                                                 *
***********************************************************************************/

#ifndef __MENU_H__
#define __MENU_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Layout\\LayoutDiv.h"
#include "MenuItem.h"

namespace OwLib
{
	class  MenuItemA;

	typedef  void (*MenuItemMouseEvent)(void*, MenuItemA*, const POINT& mp, MouseButtonsA button, int clicks, int delta, void*);

	class  MenuA : public LayoutDivA
	{
	protected:
		bool m_autoHide;
		int m_timerID;
	protected:
		MenuItemA *m_parentItem;
		bool m_popup;
		void Adjust(MenuA *menu);
		bool CheckDivFocused(vector<MenuItemA*> items);
		bool CheckFocused(ControlA *control);
		bool CloseMenus(vector<MenuItemA*> items);
	protected:
		void CallMenuItemMouseEvent(int eventID, MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta);
	public:
		vector<MenuItemA*> m_items;
		MenuA();
		virtual ~MenuA();
		bool AutoHide();
		void SetAutoHide(bool autoHide);
		MenuItemA* GetParentItem();
		void SetParentItem(MenuItemA *parentItem);
		bool IsPopup();
		void SetPopup(bool popup);
	public:
		void AddItem(MenuItemA *item);
		void ClearItems();
		virtual MenuA* CreateDropDownMenu();
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		vector<MenuItemA*> GetItems();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertItem(int index, MenuItemA *item);
		virtual bool OnAutoHide();
		virtual void OnLoad();
		virtual void OnMenuItemClick(MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMenuItemMouseMove(MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnTimer(int timerID);
		virtual void OnVisibleChanged();
		void RemoveItem(MenuItemA *item);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif