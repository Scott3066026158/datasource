//*************************************************************************************\
//*                                                                                      *
//* HttpGetService.h -  Http get service functions, types, and definitions.              *
//*                                                                                      *
//*               Version 1.00 бя														 *
//*                                                                                      *
//*               Copyright (c) 2016-2017, Server. All rights reserved.                  *
//*               Created by Lord.														 *
//*                                                                                      *
//**************************************************************************************

#ifndef __HTTPGETSERVICE_H__
#define __HTTPGETSERVICE_H__
#pragma once

namespace OwLibCT
{
    class HttpGetService
    {
    public:
        static string Get(const string &url);
		static string Get(const string &url, int time);
    };
}


#endif
