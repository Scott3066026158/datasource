/*****************************************************************************\
*                                                                             *
* CBase.h -    Base functions, types, and definitions.                        *
*                                                                             *
*              Version 1.00 ¡ï¡ï¡ï¡ï¡ï                                        *
*                                                                             *
*              Copyright (c) 2010-2014, Lord's client. All rights reserved.   *
*                                                                             *
******************************************************************************/

#ifndef __CBASE_H__
#define __CBASE_H__
#pragma once
#include "..//stdafx.h"
#include <string>
using namespace std;

namespace OwLibSock
{
	class CBase64  
	{  
	private:  
		CBase64();  
	public:  
		virtual ~CBase64();  
		static string Encode(const unsigned char *Data,int DataByte);  
		static string Decode(const char *Data,int DataByte,int& OutByte);  
	};
}

#endif