// Client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "winsock2.h"
#include<iostream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
//BOOL RecieveLine(SOCKET S, char* buf);
#pragma warning(disable:4996)

int _tmain(int argc, _TCHAR* argv[])
{
	const int BUF_SIZE = 64;
	SOCKADDR_IN servAddr;
	SOCKET sHost;
	char buf[BUF_SIZE];
	char bufRecv[BUF_SIZE];
	WSADATA wsd;
	int retVal;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}

	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == sHost)
	{
		cout << "socket failed!" << endl;
		WSACleanup();
		return -1;
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		closesocket(sHost);
		WSACleanup();
		return -1;
	}
	while (true)
	{
		ZeroMemory(bufRecv, BUF_SIZE);
		/*ZeroMemory(buf, BUF_SIZE);*/
		cout << "send message to the serve:";
		cin.get(buf,64);
		retVal = send(sHost, buf, strlen(buf), 0);

		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			closesocket(sHost);
			WSACleanup();
			return -1;
		}
		recv(sHost, bufRecv, 64 , 0);
		cout << endl << "recive message from the serve:" << bufRecv << endl;
	}
	closesocket(sHost);
	WSACleanup();
	return 0;
}


