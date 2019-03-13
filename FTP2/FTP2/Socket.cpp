#include"stdafx.h"

#include "Socket.h"
#include <fstream>
#include "Ws2tcpip.h"
#include<winsock.h> 
#pragma comment(lib,"ws2_32.lib")

 

//socket连接
boolean Socket::Connect(int port, const char* adr) {

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	inet_pton(AF_INET, adr, &saddr.sin_addr.s_addr);
	saddr.sin_port = htons(port);

	if (connect(sock, (SOCKADDR*)(&saddr), sizeof(saddr)) != 0)
		return FALSE;
	isConnect = TRUE;
	return TRUE;
}

//发送msg
boolean Socket::SendMsg(const CStringA msg) {
	if (send(sock, msg, msg.GetLength(), 0) == -1)
		return false;
	return true;
}


boolean Socket::SendMsg(char* msg, int size) {
	if (send(sock, msg, size, 0) == -1)
		return false;
	return true;
}

//接受msg
char* Socket::RecvMsg(int num) {
	int x;
	char* receiv = new char[num];
	memset(receiv, '\0', 1024);
	x = recv(sock, receiv, num, 0); //recv() returns length of message
	receiv[x] = '\0'; //0 indexing
	return receiv;
}

//关闭socket
void Socket::CloseCon() {
	closesocket(sock);
}

boolean Socket::IsConnect()
{
	return isConnect;
}
