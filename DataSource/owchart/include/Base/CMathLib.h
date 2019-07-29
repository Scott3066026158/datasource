/*****************************************************************************\
*                                                                             *
* CMathLib.h -  Math functions                                                *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                       *
*                                                                             *
*               Copyright (c) 2016-2016,  Lord's owchart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CMATHLIB_H__
#define __CMATHLIB_H__
#pragma once

#include "..\\..\\stdafx.h"
#pragma comment(lib,"owmath.lib")

namespace OwLib
{
	struct LPDATA
	{
	public:
		LPDATA()
		{
		};
		double lastvalue;
		double first_value;
		int mode;
		double sum;
	};

	extern "C" _declspec(dllexport) void M001(int index, int n, double s, double m, double high, double low, double hhv, double llv, int last_state, 
	double last_sar, double last_af, int *state, double *af, double *sar);
	extern "C" _declspec(dllexport) double M002(double value, double *listForAvedev, int listForAvedev_length, double avg);
	extern "C" _declspec(dllexport) double M003(int index, int n, double value, struct LPDATA last_MA);
	extern "C" _declspec(dllexport) double M004(int index, int n, double value, struct LPDATA last_SUM);
	extern "C" _declspec(dllexport) double M005(int n, int weight, double value, double lastWMA);
	extern "C" _declspec(dllexport) double M006(int n, double value, double lastEMA);
	extern "C" _declspec(dllexport) double M007(double *list, int length, double avg,  double standardDeviation);
	extern "C" _declspec(dllexport) double M008(double *list, int length);
	extern "C" _declspec(dllexport) double M009(double *list, int length);
	extern "C" _declspec(dllexport) double M010(double *list, int length);
	extern "C" _declspec(dllexport) double M011(double *list, int length);
	extern "C" _declspec(dllexport) int M012(double min, double max, int yLen, int maxSpan, int minSpan, int defCount, double *step, int *digit);
	extern "C" _declspec(dllexport) void M013(int index, double close, double p, double *sxp, int *sxi, double *exp, int *exi, int *state, 
	int *cStart, int *cEnd, double *k, double *b);
	extern "C" _declspec(dllexport) void M014(double *list, int length, float *k, float *b);
	extern "C" _declspec(dllexport) double M015(double close, double lastSma, int n, int m);
	extern "C" _declspec(dllexport) void M105(int x1, int y1, int x2, int y2, int *x, int *y, int *w, int *h);
	extern "C" _declspec(dllexport) double M106(float x1,  float y1,  float x2,  float y2,  float oX,  float oY);
	extern "C" _declspec(dllexport) void M107(float x1,  float y1,  float x2,  float y2,  float oX,  float oY,  float *k,  float *b);
	extern "C" _declspec(dllexport) void M108(float width,  float height,  float *a,  float *b);
	extern "C" _declspec(dllexport) bool M109(float x, float y, float oX, float oY, float a, float b);
	extern "C" _declspec(dllexport) void M110(float x1, float y1, float x2, float y2, float x3, float y3, float *oX, float *oY, float *r);
	extern "C" _declspec(dllexport) int M112(int index);
	extern "C" _declspec(dllexport) void M124(float x1, float y1, float x2, float y2, float x3, float y3, float *x4, float *y4);
	extern "C" _declspec(dllexport) double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
	extern "C" _declspec(dllexport) void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
	extern "C" _declspec(dllexport) int M131();
	extern "C" _declspec(dllexport) void M132(RECT *bounds, SIZE *parentSize, SIZE *oldSize, bool anchorLeft, bool anchorTop, bool anchorRight, bool anchorBottom);
	extern "C" _declspec(dllexport) void M133(RECT *bounds, RECT *spaceRect, SIZE *cSize, int dock);
	extern "C" _declspec(dllexport) void M135(int layoutStyle, RECT *bounds, PADDING *padding, 
	PADDING *margin, int left, int top, int width, int height,
	 int tw, int th, POINT *headerLocation);
	extern "C" _declspec(dllexport) bool M136(RECT *bounds, int rowHeight, int scrollV, double visiblePercent, int cell, int floor);
	extern "C" _declspec(dllexport) void M137(int resizePoint, int *left, int *top, int *right, int *bottom, POINT *nowPoint, POINT *startMousePoint);
	extern "C" _declspec(dllexport) bool M138(int indexTop, int indexBottom, int cell, int floor, int lineHeight, double visiblePercent);
}
#endif