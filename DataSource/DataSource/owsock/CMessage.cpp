#include "..\\stdafx.h"
#include "CMessage.h"

CMessage::CMessage()
{
	Init();
}


CMessage::CMessage(int groupID, int serviceID, int functionID, int sessionID, int requestID, int socketID, int state, int compressType, int bodyLength, char *body)
{
	m_groupID = groupID;
	m_serviceID = serviceID;
	m_functionID = functionID;
	m_sessionID = sessionID;
	m_requestID = requestID;
	m_socketID = socketID;
	m_state = state;
	m_compressType = compressType;
	m_bodyLength = bodyLength;
	m_body = new char[m_bodyLength];
	memcpy(m_body, body, m_bodyLength);
}

CMessage::CMessage(const CMessage &rhs)
{
	Init();
	Copy(rhs);
}

CMessage::~CMessage()
{
	if (m_body)
	{
		delete []m_body;
	}
	m_body = 0;
}

void CMessage::Copy(const CMessage &rhs)
{
	m_groupID = rhs.m_groupID;
	m_serviceID = rhs.m_serviceID;
	m_functionID = rhs.m_functionID;
	m_sessionID = rhs.m_sessionID;
	m_requestID= rhs.m_requestID;
	m_socketID = rhs.m_socketID;
	m_state = rhs.m_state;
	m_compressType = rhs.m_compressType;
	m_bodyLength = rhs.m_bodyLength;
	if (m_body)
	{
		delete []m_body;
	}
	m_body = new char[rhs.m_bodyLength];
	memcpy(m_body, rhs.m_body, rhs.m_bodyLength);
}

void CMessage::Init()
{
	m_groupID = 0;
	m_serviceID = 0;
	m_functionID = 0;
	m_sessionID = 0;
	m_requestID = 0;
	m_socketID = 0;
	m_state = 0;
	m_compressType = 0;
	m_bodyLength = 0;
	m_body = 0;
}
