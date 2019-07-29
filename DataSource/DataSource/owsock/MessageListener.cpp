#include "..\\stdafx.h"
#include "MessageListener.h"

MessageListener::MessageListener()
{
}

MessageListener::~MessageListener()
{
	Clear();
}

void MessageListener::Add(ListenerMessageCallBack callBack, void *pInvoke)
{
	m_callBacks.push_back(callBack);
	m_callBackInvokes.push_back(pInvoke);
}

void MessageListener::CallBack(CMessage *message)
{
	int callBacksSize = (int)m_callBacks.size();
	for(int i = 0; i < callBacksSize; i++)
	{
		m_callBacks[i](message, m_callBackInvokes[i]);
	}
}

void MessageListener::Clear()
{
	m_callBacks.clear();
	m_callBackInvokes.clear();
}

void MessageListener::Remove(ListenerMessageCallBack callBack)
{
	void *pInvoke = 0;
	int pos = 0;
	vector<ListenerMessageCallBack>::iterator sIter = m_callBacks.begin();
	for(; sIter != m_callBacks.end(); ++sIter)
	{
		if(callBack == *sIter)
		{
			m_callBacks.erase(sIter);
			pInvoke = m_callBackInvokes[pos];
			break;
		}
		pos++;
	}
	vector<void*>::iterator sIter2 = m_callBackInvokes.begin();
	for(; sIter2 != m_callBackInvokes.end(); ++sIter2)
	{
		if(pInvoke == *sIter2)
		{
			m_callBackInvokes.erase(sIter2);
			break;
		}
	}
}
