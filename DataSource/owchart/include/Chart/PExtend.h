/*****************************************************************************\
*                                                                             *
* PExtend.h -   Plot extentions                                               *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __PEXTEND_H__
#define __PEXTEND_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CPlot.h"
#include "PlotBase.h"

namespace OwLib
{
	class  PlotBase;

	class  P001:public PlotBase
	{
	public:
		P001();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P002:public PlotBase
	{
	public:
		P002();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P003:public PlotBase
	{
	public:
		P003();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P004:public PlotBase
	{
	public:
		P004();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};
	class  P005:public PlotBase
	{
	protected:
		RECT GetDownArrowRect(float x, float y, float width);
	public:
		P005();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};
	class  P006:public PlotBase
	{
	protected:
		float* GetDropLineParams(map<int, PlotMark*> *pList);
	public:
		P006();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P009:public PlotBase
	{
	public:
		P009();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P010:public PlotBase
	{
	protected:
		float* FibonacciEllipseParam(map<int, PlotMark*> *pList);
	public:
		P010();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P011:public PlotBase
	{
	public:
		P011();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P012:public PlotBase
	{
	protected:
		vector<int> GetFibonacciTimeZonesParam(map<int,PlotMark*> *pList);
	public:
		P012();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P014:public PlotBase
	{
	protected:
		POINT m_oppositePoint;
	public:
		P014();
		virtual ActionType GetAction();
		ActionType GetClickStatus();
		POINT* GetGannBoxPoints(float x1, float y1, float x2, float y2);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P016:public PlotBase
	{
	public:
		P016();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P017:public PlotBase
	{
	public:
		P017();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P018:public PlotBase
	{
	public:
		P018();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P019:public PlotBase
	{
	protected:
		float* LevelGradingParams(double value1, double value2);
	public:
		P019();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P020:public PlotBase
	{
	public:
		P020();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P021:public PlotBase
	{
	public:
		P021();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P022 : public PlotBase
	{
	public:
		P022();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P023:public PlotBase
	{
	public:
		P023();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P024:public PlotBase
	{
	protected:
		void NullPoint(float x1, float y1, float x2, float y2, float *nullX, float *nullY);
		double* GetNullPointParams(map<int,PlotMark*> *pList);
	public:
		P024();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P025:public PlotBase
	{
	protected:
		float* GetParallelParams(map<int,PlotMark*> *pList);
	public:
		P025();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P026:public PlotBase
	{
	protected:
		float* GetPercentParams(double value1, double value2);
	public:
		P026();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P027:public PlotBase
	{
	protected:
		int m_period;
		int m_beginPeriod;
	public:
		P027();
		virtual ActionType GetAction();
		vector<double> GetPLParams(map<int,PlotMark*> *pList);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P028:public PlotBase
	{
	protected:
		SIZE m_textSize;
	public:
		P028();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P029:public PlotBase
	{
	public:
		P029();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P030:public PlotBase
	{
	public:
		P030();
		float* GetRaseLineParams(map<int,PlotMark*> *pList);
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P031:public PlotBase
	{
	public:
		P031();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P032:public PlotBase
	{
	protected:
		POINT m_oppositePoint;
	public:
		P032();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P033:public PlotBase
	{
	public:
		P033();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P034:public PlotBase
	{
	public:
		P034();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P035:public PlotBase
	{
	public:
		P035();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P036:public PlotBase
	{
	protected:
		double GetSEChannelSD(map<int,PlotMark*> *pList);
	public:
		P036();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P037:public PlotBase
	{
	public:
		P037();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P038:public PlotBase
	{
	protected:
		float* GetSymmetricTriangleParams(map<int,PlotMark*> *pList);
	public:
		P038();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P041:public PlotBase
	{
	protected:
		double* GetTimeRulerParams(map<int,PlotMark*> *pList);
	public:
		P041();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart(); 
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P042:public PlotBase
	{
	public:
		P042();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};
	class  P043:public PlotBase
	{
	protected:
		RECT GetUpArrowRect(float x, float y, float width);
	public:
		P043();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P044:public PlotBase
	{
	public:
		P044();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P045:public PlotBase
	{
	protected:
		float* GetWaveRulerParams(double value1, double value2);
	public:
		P045();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P046:public PlotBase
	{
	protected:
		double* GetTironelLevelsParams(map<int,PlotMark*> *pList);
	public:
		P046();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P047:public PlotBase
	{
	protected:
		double GetRRCRange(map<int,PlotMark*> *pList, float *param);
	public:
		P047();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P048:public P026
	{
	public: 
		P048();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P049:public P032
	{
	protected:
		ActionType GetAction(const POINT& mp);
	public:
		P049();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P050:public PlotBase
	{
	public:
		P050();
		virtual ActionType GetAction();
		POINT* GetPLPoints(map<int,PlotMark*> *pList);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaint *paint);
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P051:public PlotBase
	{
	public:
		P051();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P052:public P025
	{
	protected:
		void GetLine3Params(map<int,PlotMark*> *pList, float *k, float *d, float *x4);
		void PaintEx(CPaint *paint, map<int,PlotMark*> *pList,_int64 lineColor);
	public:
		P052();
		virtual ActionType GetAction();
		virtual void OnMoveStart();
		virtual void OnPaint(CPaint *paint);
        virtual void OnPaintGhost(CPaint *paint);
	};

	class  P053:public PlotBase
	{
	public:
		P053();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  P054:public P042
	{
	protected:
		float* GetGoldenRatioAimParams(map<int,PlotMark*> *pList);
	public:
		P054();
		virtual ActionType GetAction();
		virtual void OnMoveStart();
		virtual void Paint(CPaint *paint, map<int,PlotMark*> *pList, _int64 lineColor);
	};

	class  PFactory
	{
	public:
		static CPlot* CreatePlot(const wstring& plotType);
	};
}
#endif