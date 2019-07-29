#pragma once
#ifndef __CMESSAGE_H__
#define __CMESSAGE_H__

struct CMessage
{
public:
	CMessage();
	CMessage(int groupID, int serviceID, int functionID, int sessionID, int requestID, int socketID, int state, int compressType, int bodyLength, char *body);
	CMessage(const CMessage &rhs);
	CMessage& operator= (const CMessage &rhs)
	{
		if (&rhs == this)
		{
			return *this;
		}
		Copy(rhs);
		return *this;
	}
	virtual ~CMessage();
	int m_groupID;   
	int m_serviceID;   
	int m_functionID;  
	int m_sessionID;   
	int m_requestID;   
	int m_socketID; 
	int m_state;
	int m_compressType;
	int m_bodyLength;  
	char *m_body; 
	void Copy(const CMessage &rhs);
	void Init();
};

#endif