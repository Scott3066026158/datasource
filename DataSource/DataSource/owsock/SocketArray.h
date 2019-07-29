#pragma once
#ifndef __SOCKETARRAY_H__
#define __SOCKETARRAY_H__
class SocketArray
{
private:
	vector<int> m_sockets;
public:
	SocketArray();
	virtual ~SocketArray();
public:
	void AddSocket(int socketID);
	void GetSocketList(vector<int> *socketList);
	void RemoveSocket(int socketID);
};

#endif