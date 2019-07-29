#pragma once
#ifndef __Router_H__
#define __Router_H__

class Router{
public:
public:
	Router();
	~Router();
public:
	static DWORD WINAPI Wan(LPVOID lpParam);
	int Lan();
};
#endif