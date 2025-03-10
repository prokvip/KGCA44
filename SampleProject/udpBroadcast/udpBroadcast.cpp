#include <winsock2.h>
#include<iostream>
#include<conio.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	char broadcast = '1';
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST,&broadcast, sizeof(broadcast));
	
	sockaddr_in BroadcastSendAddr;
	BroadcastSendAddr.sin_family = AF_INET;
	BroadcastSendAddr.sin_port = htons(10000);
	BroadcastSendAddr.sin_addr.s_addr = INADDR_BROADCAST;

	char msg[] = "hello";
	sendto(sock, msg, strlen(msg), 0,(sockaddr*)&BroadcastSendAddr, sizeof(BroadcastSendAddr));

	_getch();
	closesocket(sock);
	WSACleanup();
}
