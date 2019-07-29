/*****************************************************************************\
*                                                                             *  
* CIndicator.h - Indicator functions, types, and definitions                  *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Gaia's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/
#ifndef __CINDICATOR_H__
#define __CINDICATOR_H__
#pragma once

#define FUNCTIONID_CHUNK 40
#define FUNCTIONID_FUNCVAR 10
#define FUNCTIONID_FUNCTION 9
#define FUNCTIONID_VAR 10

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "..\\Base\\CMathLib.h"
#include "Enums.h"
#include "CTable.h"
#include "CDiv.h"
#include "CList.h"
#include "BaseShape.h"

namespace OwLib
{
	class  CIndicator;
	class  CMathElement;

	class  CVariable
	{
	public:
		CVariable();
		virtual ~CVariable();
		BarShape *m_barShape;
		CandleShape *m_candleShape;
		wstring m_expression;
		int m_field;
		int m_fieldIndex;
		wstring m_fieldText;
		int m_functionID;
		wstring m_funcName;
		CIndicator *m_indicator;
		int m_line;
		PointShape *m_pointShape;
		PolylineShape *m_polylineShape;
		wstring m_name;
		CVariable **m_parameters;
		int m_parametersLength;
		CMathElement **m_splitExpression;
		int m_splitExpressionLength;
		int *m_tempFields;
		int m_tempFieldsLength;
		int *m_tempFieldsIndex;
		int m_tempFieldsIndexLength;
		TextShape *m_textShape;
		int m_type;
		double m_value;
		void CreateTempFields(int count);
	};

	class  CMathElement
	{
	public:
		CMathElement();
		CMathElement(int type, double value);
		virtual ~CMathElement();
		int m_type;
		double m_value;
		CVariable *m_var;
	};

	class   CMathElementEx : public CMathElement
	{
	public:
		CMathElementEx *m_next;
		CMathElementEx(int type, double value):CMathElement(type, value)
		{
			m_next = 0;
		}
		virtual ~CMathElementEx()
		{
			if(m_next)
			{
				delete m_next;
				m_next = 0;
			}
		}
	};

	class  CFunction
	{
	public:
		CFunction();
		virtual ~CFunction();
		int m_ID;
		wstring m_name;
		int m_type;
	public:
		virtual double OnCalculate(CVariable *var);
	};

	class  CVar
    {
	public:
        vector<wstring> *m_list;
        map<wstring, wstring> *m_map;
        double m_num;
        wstring m_str;
        int m_type;
        CVar *m_parent;
	public:
        CVar()
        {
			m_list = 0;
			m_map = 0;
			m_parent = 0;
        }
        virtual ~CVar()
        {
			if (m_list)
            {
                delete m_list;
				m_list = 0;
            }
            if (m_map)
            {
                delete m_map;
				m_map = 0;
            }
            m_parent = 0;
        }
	public:
        virtual wstring GetText(CIndicator *indicator, CVariable *name);
		virtual double GetValue(CIndicator *indicator, CVariable *name);
		virtual double OnCreate(CIndicator *indicator, CVariable *name, CVariable *value);
		virtual void SetValue(CIndicator *indicator, CVariable *name, CVariable *value);
    };

	class  CVarFactory
	{
	public:
		virtual CVar* CreateVar()
		{
			return new CVar;
		}
	};

	class  CIndicator
	{
	protected:
		CRITICAL_SECTION _csLock;
		map<wstring,double> m_defineParams;
		map<wstring,CFunction*> m_functions;
		map<int, CFunction*> m_functionsMap;
		int m_index;
		vector<CVariable*> m_lines;
		vector<_int64> m_systemColors;
		void *m_tag;
		map<wstring, CVariable*> m_tempFunctions;
        map<wstring, CVariable*> m_tempVariables;
		vector<CVariable*> m_variables;
		CVarFactory *m_varFactory;
	protected:
		AttachVScale m_attachVScale;
		int m_break;
		CTable *m_dataSource;
		CDiv *m_div;
		wstring m_name;
		double m_result;
		CVar m_resultVar;
	protected:
		void AnalysisVariables(wstring *sentence, int line, wstring funcName, wstring fieldText, bool isFunction);
		void AnalysisScriptLine(wstring line);
		double Calculate(CMathElement **expr, int exprLength);
		double CallFunction(CVariable *var);
		void DeleteTempVars();
		void DeleteTempVars(CVariable *var);
		_int64 GetColor(const wstring& strColor);
		LPDATA GetDatas(int fieldIndex, int mafieldIndex, int index, int n);
		float GetLineWidth(const wstring& strLine);
		int GetMiddleScript(const wstring& script, vector<wstring> *lines);
		int GetOperator(const wstring& op);
		bool IsNumeric(const wstring& str);
		wstring Replace(const wstring& parameter);
		CMathElement** SplitExpression(const wstring& expression, int *sLength);
		wstring* SplitExpression2(const wstring& expression, int *sLength);
	public:
		CIndicator();
		virtual ~CIndicator();
		map<wstring ,int> m_mainVariables;
		map<int, CVar*> m_tempVars;
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual CTable* GetDataSource();
		virtual void SetDataSource(CTable *dataSource);
		virtual CDiv* GetDiv();
		virtual void SetDiv(CDiv *div);
		virtual int GetIndex();
		virtual wstring GetName();
		virtual void SetName(const wstring& name);
		virtual double GetResult();
		virtual void SetScript(const wstring& script);
		virtual vector<_int64> GetSystemColors();
		virtual void SetSystemColors(vector<_int64> systemColors);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual CVarFactory* GetVarFactory();
		virtual void SetVarFactory(CVarFactory *varFactory);
	public:
		void AddFunction(CFunction *function);
		double CallFunction(wstring funcName);
		void Clear();
		vector<CFunction*> GetFunctions();
		vector<BaseShape*> GetShapes();
		wstring GetText(CVariable *var);
		double GetValue(CVariable *var);
		CVariable* GetVariable(const wstring& name);
		void Lock();
		void OnCalculate(int index);
		void RemoveFunction(CFunction *function);
		void SetSourceField(const wstring& key, int value);
		void SetSourceValue(int index, const wstring& key, double value);
		void SetVariable(CVariable *variable, CVariable *parameter);
		void UnLock();
	protected:
		double ABS2(CVariable *var);
		double AMA(CVariable *var);
		double ACOS(CVariable *var);
		double ASIN(CVariable *var);
		double ATAN(CVariable *var);
		double AVEDEV(CVariable *var);
		int BARSCOUNT(CVariable *var);
		int BARSLAST(CVariable *var);
		int BETWEEN(CVariable *var);
		int BREAK(CVariable *var);
		double CEILING(CVariable *var);
		double CHUNK(CVariable *var);
		int CONTINUE(CVariable *var);
		double COS(CVariable *var);
		int COUNT(CVariable *var);
		int CROSS(CVariable *var);
		int CURRBARSCOUNT(CVariable *var);
		int DATE(CVariable *var);
		int DAY(CVariable *var);
		int DELETE2(CVariable *var);
		double DMA(CVariable *var);
		int DOTIMES(CVariable *var);
		int DOWHILE(CVariable *var);
		int DOWNNDAY(CVariable *var);
		double DRAWICON(CVariable *var);
		double DRAWKLINE(CVariable *var);
		double DRAWNULL(CVariable *var);
		double DRAWTEXT(CVariable *var);
		int EXIST(CVariable *var);
		double EMA(CVariable *var);
		int EVERY(CVariable *var);
		double EXPMEMA(CVariable *var);
		double EXP(CVariable *var);
		double FLOOR(CVariable *var);
		int FOR(CVariable *var);
		double FUNCTION(CVariable *var);
		double FUNCVAR(CVariable *var);
		double GET(CVariable *var);
		double HHV(CVariable *var);
		double HHVBARS(CVariable *var);
		int HOUR(CVariable *var);
		double IF(CVariable *var);
		double IFN(CVariable *var);
		double INTPART(CVariable *var);
		int LAST(CVariable *var);
		double LLV(CVariable *var);
		double LLVBARS(CVariable *var);
		double LOG(CVariable *var);
		double MA(CVariable *var);
		double MAX2(CVariable *var);
		double MEMA(CVariable *var);
		double MIN2(CVariable *var);
		int MINUTE(CVariable *var);
		double MOD(CVariable *var);
		int MONTH(CVariable *var);
		int NDAY(CVariable *var);
		int NOT(CVariable *var);
		double POLYLINE(CVariable *var);
		double POW(CVariable *var);
		int RAND(CVariable *var);
		double REF(CVariable *var);
		double RETURN(CVariable *var);
		double REVERSE(CVariable *var);
		double ROUND(CVariable *var);
		double SAR(CVariable *var);
		double SET(CVariable *var);
		int SIGN(CVariable *var);
		double SIN(CVariable *var);
		double SMA(CVariable *var);
		double SQRT(CVariable *var);
		double SQUARE(CVariable *var);
		double STD(CVariable *var);
		double STICKLINE(CVariable *var);
		double SUM(CVariable *var);
		double TAN(CVariable *var);
		int TIME(CVariable *var);
		int TIME2(CVariable *var);
		double TMA(CVariable *var);
		int UPNDAY(CVariable *var);
		double VALUEWHEN(CVariable *var);
		double VAR(CVariable *var);
		int WHILE(CVariable *var);
		double WMA(CVariable *var);
		int YEAR(CVariable *var);
		double ZIG(CVariable *var);
	public:
		int STR_CONTACT(CVariable *var);
		int STR_EQUALS(CVariable *var);
		int STR_FIND(CVariable *var);
		int STR_FINDLAST(CVariable *var);
		int STR_LENGTH(CVariable *var);
		int STR_SUBSTR(CVariable *var);
		int STR_REPLACE(CVariable *var);
		int STR_SPLIT(CVariable *var);
		int STR_TOLOWER(CVariable *var);
		int STR_TOUPPER(CVariable *var);
		int LIST_ADD(CVariable *var);
		int LIST_CLEAR(CVariable *var);
		int LIST_GET(CVariable *var);
		int LIST_INSERT(CVariable *var);
		int LIST_REMOVE(CVariable *var);
		int LIST_SIZE(CVariable *var);
		int MAP_CLEAR(CVariable *var);
		int MAP_CONTAINSKEY(CVariable *var);
		int MAP_GET(CVariable *var);
		int MAP_GETKEYS(CVariable *var);
		int MAP_REMOVE(CVariable *var);
		int MAP_SET(CVariable *var);
		int MAP_SIZE(CVariable *var);
	};
}
#endif