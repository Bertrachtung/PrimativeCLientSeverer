// Serve.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const int BUF_SIZE = 256;
	WSADATA WSD;
	SOCKET sServer;
	SOCKET sClient;
	SOCKADDR_IN addrServ;
	char buf[BUF_SIZE];
	char sendBuf[BUF_SIZE];
	int retVal;
	if (WSAStartup(MAKEWORD(2, 2), &WSD)!= 0)
	{
		cout << "WSAStartup failed!" << endl;
		return 1;
	}
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sServer)
	{
		cout << "socket failed!" << endl;
		WSACleanup();
		return -1;
	}
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}



	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
	if (INVALID_SOCKET == sServer)
	{
		cout << "accept failed!" << endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	while (true)
	{
		ZeroMemory(buf, BUF_SIZE);
		/*ZeroMemory(sendBuf, BUF_SIZE);*/
		retVal = recv(sClient, buf, BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed" << endl;
			closesocket(sServer);
			closesocket(sClient);
			WSACleanup();
			return -1;
		}
		if (buf[0] == '0')
			break;
		cout << "message from the client:" << buf << endl;

		cout << "send message to thee client:";
		cin.get(sendBuf, 64);

		send(sClient, sendBuf, strlen(sendBuf), 0);

	}
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
	return 0;
}


