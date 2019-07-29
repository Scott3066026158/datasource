#ifndef _PUBLICMETHOD_H_
#define _PUBLICMETHOD_H_
#pragma once

#define MIN_DBL_NUMBER 0.0000000001

class PublicMethod
{
public:
	PublicMethod();
	~PublicMethod();
public:
	static void isEmpty();
	static String getCurrentTime(); 
	static void getCurrentTime(String* date, String* time);
	static bool d_eq(const double& a, const double& b);
	static String GetOrderStatus(int state);
};

#endif