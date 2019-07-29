/*****************************************************************************\
*                                                                             *
* CTable.h -    DataSource functions, types, and definitions                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CTABLE_H__
#define __CTABLE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CList.h"

namespace OwLib
{
	class  CTable;

	class  CRow
	{
	protected:
		CTable *m_table;
		CList<double> m_values;
	public:
		CRow(CTable *table);
		CRow(CTable *table, int capacity, int step);
		CRow(CTable *table, double *ary, int size);
		virtual ~CRow();
		void FillEmpty(int columns);
		double Get(int index);
		void Remove(int index);
		void Set(int index, double value);
	};

	class  CTable
	{
	protected:
		int m_autoField;
		int m_colsCapacity;
		int m_colsStep;
		CList<int*> m_columns;
		CList<double> m_keys;
		CList<CRow*> m_rows;
		CRow* AddKey(double num);
		void FillEmpty();
	public:
		double NaN;
		CTable();
		virtual ~CTable();
		int AUTOFIELD();
		static inline int NULLFIELD()
		{
			return -1;
		}
		void AddColumn(int colName);
		void AddRow(double pk, double *ary, int size);
		int ColumnsCount();
		void Clear();
		int GetColumnIndex(int colName);
		int GetRowIndex(double key);
		double GetXValue(int rowIndex);
		double Get(double pk, int colName);
		double Get2(int rowIndex, int colName);
		double Get3(int rowIndex, int colIndex);
		static inline bool IsNaN(double value)
		{
			return ((*(((long long*) &value)) & 0x7fffffffffffffffL) > 0x7ff0000000000000L);
		}
		void RemoveAt(int rowIndex);
		void RemoveColumn(int name);
		int RowsCount();
		void Set(double pk, int colName, double value);
		void Set2(int rowIndex, int colName, double value);
		void Set3(int rowIndex, int colIndex, double value);
		void SetColsCapacity(int capacity);
		void SetColsGrowStep(int step);
		void SetRowsCapacity(int capacity);
		void SetRowsGrowStep(int step);
		double* DATA_ARRAY(int colName, int rowIndex, int n, int *length);
	};
}
#endif