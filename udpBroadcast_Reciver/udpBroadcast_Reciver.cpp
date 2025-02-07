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
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
		&broadcast, sizeof(broadcast));

	sockaddr_in BroadcastRecvAddr;
	BroadcastRecvAddr.sin_family = AF_INET;
	BroadcastRecvAddr.sin_port = htons(10000);
	BroadcastRecvAddr.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (sockaddr*)&BroadcastRecvAddr, sizeof(BroadcastRecvAddr));
	
	char msg[256] = { 0, };
	int iSize = sizeof(char)*256;
	int iRecvAddrLen = sizeof(BroadcastRecvAddr);
	int iRet = recvfrom(sock, msg, iSize, 0,
		(sockaddr*)&BroadcastRecvAddr, &iRecvAddrLen);
	if (iRet == SOCKET_ERROR)
	{
		int K = 0;
	}
	std::cout << msg << std::endl;
	
	/*sockaddr_in BroadcastSendAddr;
	BroadcastSendAddr.sin_family = AF_INET;
	BroadcastSendAddr.sin_port = htons(10000);
	BroadcastSendAddr.sin_addr.s_addr = INADDR_BROADCAST;*/

	//sendto(sock, msg, strlen(msg), 0,
	//	(sockaddr*)&BroadcastAddr, sizeof(BroadcastAddr));

	
	_getch();
	closesocket(sock);
	WSACleanup();
}
