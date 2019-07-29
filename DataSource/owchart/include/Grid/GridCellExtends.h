/*****************************************************************************\
*                                                                             *
* GridCellExtends.h -  Grid cell functions, types, and definitions            *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's grid. All rights reserved.    *
*               Check right 2016/9/22 by Lord.                                *
*                                                                             *
*******************************************************************************/

#ifndef __GRIDCELLEXTENDS_H__
#define __GRIDCELLEXTENDS_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridCell.h"
#include "GridColumn.h"
#include "GridRow.h"
#include "Grid.h"

namespace OwLib
{
	class  GridCell;
	class  GridColumn;
	class  GridRow;
	class  GridA;
	class  ButtonA;
	class  CheckBoxA;
	class  ComboBoxA;
	class  DateTimePickerA;
	class LabelA;
	class  SpinA;
	class  RadioButtonA;
	class  TextBoxA;

	class  GridBoolCell : public GridCell
	{
	protected:
		bool m_value;
	public:
		GridBoolCell();
		GridBoolCell(bool value);
		virtual ~GridBoolCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
	    virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridButtonCell: public GridControlCell
	{
	public:
		GridButtonCell();
		virtual ~GridButtonCell();
		ButtonA* GetButton();
	};

	class  GridCheckBoxCell : public GridControlCell
	{
	protected:
	public:
		GridCheckBoxCell();
		virtual ~GridCheckBoxCell();
		CheckBoxA* GetCheckBox();
	public:
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
		virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridComboBoxCell : public GridControlCell
	{
	public:
		GridComboBoxCell();
		virtual ~GridComboBoxCell();
		ComboBoxA* GetComboBox();
	public:
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void OnAdd();
        virtual void OnRemove();
		virtual void SetBool(bool value);
		virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridDateTimePickerCell : public GridControlCell
	{
	public:
		GridDateTimePickerCell();
		virtual ~GridDateTimePickerCell();
		DateTimePickerA* GetDatePicker();
	};

	class  GridDivCell : public GridControlCell
	{
	public:
		GridDivCell();
		virtual ~GridDivCell();
		DivA* GetDiv();
	};

	class  GridDoubleCell : public GridCell
	{
	protected:
		double m_value;
	public:
		GridDoubleCell();
		GridDoubleCell(double value);
		virtual ~GridDoubleCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridFloatCell : public GridCell
	{
	protected:
		float m_value;
	public:
		GridFloatCell();
		GridFloatCell(float value);
		virtual ~GridFloatCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridIntCell : public GridCell
	{
	protected:
		int m_value;
	public:
		GridIntCell();
		GridIntCell(int value);
		virtual ~GridIntCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridLabelCell : public GridControlCell
	{
	public:
		GridLabelCell();
		virtual ~GridLabelCell();
		LabelA* GetLabel();
	};

	class  GridLongCell : public GridCell
	{
	protected:
		_int64 m_value;
	public:
		GridLongCell();
		GridLongCell(_int64 value);
		virtual ~GridLongCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridRadioButtonCell : public GridControlCell
	{
	public:
		GridRadioButtonCell();
		virtual ~GridRadioButtonCell();
		RadioButtonA* GetRadioButton();
	public:
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetBool(bool value);
		virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
        virtual void SetString(const wstring& value);
	};

	class  GridSpinCell : public GridControlCell
	{
	public:
		GridSpinCell();
		virtual ~GridSpinCell();
		SpinA* GetSpin();
	public:
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual void SetBool(bool value);
		virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
	};

	class  GridStringCell : public GridCell
	{
	protected:
		wstring m_value;
	public:
		GridStringCell();
		GridStringCell(const wstring& value);
		virtual ~GridStringCell();
	public:
		virtual int CompareTo(GridCell *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetString();
		virtual void SetString(const wstring& value);
	};

	class  GridPasswordCell : public GridStringCell
	{
	public:
		GridPasswordCell();
		virtual ~GridPasswordCell();
	public:
		virtual wstring GetPaintText();
	};

	class  GridTextBoxCell: public GridControlCell
	{
	public:
		GridTextBoxCell();
		virtual ~GridTextBoxCell();
		TextBoxA* GetTextBox();
	};
}
#endif