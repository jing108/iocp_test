#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

int main(void)
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	WSAStartup(wVersion, &wsaData);

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN servAddr;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(7890);

	bind(servSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	listen(servSock, 5);

	SOCKADDR_IN clientAddr;
	int length = sizeof(SOCKADDR);
	SOCKET clientSock = accept(servSock, (SOCKADDR*)&clientAddr, &length);
	char sendBuf[1024] = { 0 };
	char tmp[100] = { 0 };
	inet_ntop(AF_INET, &clientAddr.sin_addr, tmp, 100);
	sprintf_s(sendBuf, "Hello，你的地址是：%s，你的端口是：%d", tmp, clientAddr.sin_port);
	send(clientSock, sendBuf, sizeof(sendBuf), 0);
	recv(clientSock, sendBuf, sizeof(sendBuf), 0);

}