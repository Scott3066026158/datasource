#include "..\\stdafx.h"
#include "SocketArray.h"

SocketArray::SocketArray()
{
}

SocketArray::~SocketArray()
{
}

void SocketArray::AddSocket(int socketID)
{
	vector<int>::iterator sIter = m_sockets.begin();
	for(; sIter != m_sockets.end(); ++sIter)
	{
		if(socketID == *sIter)
		{
			return;
		}
	}
	m_sockets.push_back(socketID);
}

void SocketArray::GetSocketList(vector<int> *socketList)
{
	vector<int>::iterator sIter = m_sockets.begin();
	for(; sIter != m_sockets.end(); ++sIter)
	{
		socketList->push_back(*sIter);
	}
}

void SocketArray::RemoveSocket(int socketID)
{
	vector<int>::iterator sIter = m_sockets.begin();
	for(; sIter != m_sockets.end(); ++sIter)
	{
		if(socketID == *sIter)
		{
			m_sockets.erase(sIter);
			return;
		}
	}
}