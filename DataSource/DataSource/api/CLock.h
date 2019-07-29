#pragma once
#ifndef __CLOCK__H__
#define __CLOCK__H__

class CLock
{
public:
	CLock();
	CLock(const char *name);
	virtual ~CLock();
private:
	CRITICAL_SECTION m_cs;
	char m_name[100];
public:
	void Lock();
	void Lock(const char *funcName);
	void SetName(const char *name);
	void UnLock();
	void UnLock(const char *funcName);
};

#endif
