/*****************************************************************************\
*                                                                             *
* TableLayoutDiv.h -  Table layout div functions, types, and definitions      *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's layout. All rights reserved.  *
*               Check right 2016/7/2 by Lord.                                 *
*                                                                             *
*******************************************************************************/
#ifndef __TABLELAYOUTDIV_H__
#define __TABLELAYOUTDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Div.h"

namespace OwLib
{	
	typedef enum  SizeTypeA
	{
		SizeTypeA_AbsoluteSize,
		SizeTypeA_AutoFill,
		SizeTypeA_PercentSize
	};

	class  ColumnStyleA : public CProperty
	{
	protected:
		SizeTypeA m_sizeType;
		float m_width;
	public:
		ColumnStyleA(SizeTypeA sizeType, float width);
		virtual ~ColumnStyleA();
		virtual SizeTypeA GetSizeType();
		virtual void SetSizeTypeA(SizeTypeA  sizeType);
		virtual float GetWidth();
		virtual void SetWidth(float width);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};

	class  RowStyleA : public CProperty
	{
	protected:
		float m_height;
		SizeTypeA m_sizeType;
	public:
		RowStyleA(SizeTypeA sizeType, float height);
		virtual ~RowStyleA();
		virtual float GetHeight();
		virtual void SetHeight(float height);
		virtual SizeTypeA GetSizeType();
		virtual void SetSizeTypeA(SizeTypeA  sizeType);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};

	class  TableLayoutDivA : public DivA
	{
	protected:
		vector<int> m_columns;
		int m_columnsCount;
		vector<int> m_rows;
		int m_rowsCount;
		vector<ControlA*> m_tableControls;
	public:
		vector<ColumnStyleA> m_columnStyles;
		vector<RowStyleA> m_rowStyles;
		TableLayoutDivA();
		virtual ~TableLayoutDivA();
		virtual int GetColumnsCount();
		virtual void SetColumnsCount(int columnsCount);
		virtual int GetRowsCount();
		virtual void SetRowsCount(int rowsCount);
	public:
		virtual void AddControl(ControlA *control);
		virtual void AddControl(ControlA *control, int column, int row);
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual bool OnResetLayout();
		virtual void RemoveControl(ControlA *control);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif