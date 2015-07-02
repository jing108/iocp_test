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

	SOCKADDR_IN addr;
	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(7890);
	addr.sin_family = AF_INET;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	char buf[1024] = { 0 };
	recv(sock, buf, sizeof(buf),0);

	std::cout << buf << std::endl;

	return 0;
}