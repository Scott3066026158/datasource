//GAIA_CFILE_CPP_S5:012,50%;
/*****************************************************************************\
*                                                                             *
* CFile.h -      File functions                                               *
*                                                                             *
*               Version 1.00 ★★★★★                                       *
*                                                                             *
*               Copyright (c) 2016-2016, Gaia's OwChart. All rights reserved. *
*                                                                             *
*******************************************************************************/

#ifndef __CFILE_H__
#define __CFILE_H__
#pragma once
#include "..\\stdafx.h"
#include "io.h"
#include <direct.h>
#include <fstream>
#include <sys/stat.h>

class CFileA
{
public:
	//追加内容
	static bool Append(const char *file, const char *content);
	//追加内容-宽字符
	static bool Append(const String &file, const String &content);
	//创建目录
	static void CreateDirectory(const char *dir);
	//创建目录-宽字符
	static void CreateDirectory(const String &dir);
	//判断目录是否存在
	static bool IsDirectoryExist(const char *dir);
	//判断目录是否存在-宽字符
	static bool IsDirectoryExist(const String &dir);
	//文件是否存在
	static bool IsFileExist(const char *file);
	//文件是否存在-宽字符
	static bool IsFileExist(const String &file);
	//获取目录
	static bool GetDirectories(const char *dir, vector<string> *dirs);
	//获取目录-宽字符
	static bool GetDirectories(const String &file, vector<String> *dirs);
	//获取文件修改时间
	static _int64 GetFileMTime(const char* file);
	//获取文件长度
	static int GetFileLength(const char *file);
	//获取文件长度-宽字符
	static int GetFileLength(const String &file);
	//获取文件
	static bool GetFiles(const char *dir, vector<string> *files);
	//获取文件-宽字符
	static bool GetFiles(const String &dir, vector<String> *files);
	//获取文件状态
	static int GetFileState(const char *file, struct stat *buf);
	//获取文件状态-宽字符
	static int GetFileState(const String &file, struct stat *buf);
	//读取文件
	static bool Read(const char *file, string *content);
	// 读取文件
	static bool ReadLine(ifstream *fs, string *lineContent, int lineLength);
	// 读取文件
	static bool ReadLine(ifstream *fs, String *lineContent, int lineLength);
	//读取文件-宽字符
	static bool Read(const String &file, String *content);
	//移除文件
	static void RemoveFile(const char *file);
	//移除文件-宽字符 
	static void RemoveFile(const String &file);
	//写入文件
	static bool Write(const char *file, const char *content);
	//写入文件-宽字符
	static bool Write(const String &file, const String &content);
};
#endif