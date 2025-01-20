#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <iostream>
#include <string>
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

    std::string SendBuf;
    SendBuf.resize(256);
    std::string RecvBuf;
   
    while (1)
    {        
        std::getline(std::cin, SendBuf);
        if (SendBuf.empty())
        {
            break;
        }
        int iSendSize = send(sock, &SendBuf[0], SendBuf.size(), 0);        
        if (iSendSize == 0 || iSendSize == SOCKET_ERROR) {
            std::cout << "서버가 종료되었거나 문제가 발생" << std::endl;
            break;
        }
        RecvBuf.resize(256);
        int iRecvSize = recv(sock, &RecvBuf[0], RecvBuf.size(), 0);
        if (iRecvSize == 0 || iRecvSize == SOCKET_ERROR)        {
            std::cout << "서버가 종료되었거나 문제가 발생" << std::endl;
            break;
        }
        std::cout << RecvBuf << std::endl;
        RecvBuf.clear();
    }
    closesocket(sock);
    // 윈속 소멸
    WSACleanup();    
    std::cout << "Hello World!\n";
}
