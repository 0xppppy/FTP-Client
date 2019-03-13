#pragma once


#include <iostream>
#include <afxinet.h>
class Socket
{
public:
	boolean Connect(int port, const char* adr);

	boolean SendMsg(const CStringA msg);

	boolean SendMsg(char* msg, int size);

	char* RecvMsg(int num);

	void CloseCon();
	boolean IsConnect();
	Socket()
	{
		WORD Requested;
		WSADATA wsaData;
		int ret;
		
		Requested = MAKEWORD(2, 2);
		ret = WSAStartup(Requested, &wsaData);

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
			WSACleanup();

		isConnect = FALSE;
	}
	~Socket()
	{
		WSACleanup();
	}
private:
	boolean isConnect;
	int sock;
	sockaddr_in saddr;
};