#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
int main()
{
    // 윈속 초기화( 버전선택)
    WSADATA wsa;
    int iRet = WSAStartup(MAKEWORD(2,2), &wsa);
    if (iRet != 0) return 1;
    // 소켓생성
    SOCKET sock;
    //  TCP & IP 프로토콜
    sock = socket(AF_INET, SOCK_STREAM, 0);// IPPROTO_TCP);

    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    //error C4996: 'inet_addr': Use inet_pton() or InetPton() 
    //instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
    sa.sin_addr.s_addr = inet_addr("192.168.0.88");// 전화번호
    sa.sin_port = htons(10000); // 받는 사람
    iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR) return 1;
    char SendBuffer[256] = "안녕하세여.";// { 0, };
    int iSendSize = send(sock, SendBuffer, strlen(SendBuffer), 0);
    char RecvBuffer[256] = { 0, };
    int iRecvSize = recv(sock, RecvBuffer, sizeof(RecvBuffer), 0);
    std::cout << RecvBuffer << std::endl;
    Sleep(3000);
    closesocket(sock);
    // 윈속 소멸
    WSACleanup();    
    std::cout << "Hello World!\n";
}
