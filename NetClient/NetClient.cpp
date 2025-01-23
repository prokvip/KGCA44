#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <iostream>
#include <string>
#include <thread>   // std::thread
#include <conio.h>
#include <process.h> // _beginthreadex
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

bool Check(int iCode)
{
    if (iCode == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        if (iError != WSAEWOULDBLOCK)
        {
            std::cout << "서버가 비정상종료,문제가 발생" << std::endl;
            exit(1);
        }
        return false;
    }
    return true;
}
bool RecvWork(SOCKET sock)
{
    std::string RecvBuf;
    RecvBuf.resize(256);
    int iRecvSize = recv(sock, &RecvBuf[0], RecvBuf.size(), 0);
    if (iRecvSize == 0)
    {
        std::cout << "서버가 정상종료" << std::endl;
        return false;
    }
    if (Check(iRecvSize))
    {
        std::cout << RecvBuf << std::endl;
    }
    RecvBuf.clear();
    return true;
}
bool SendWork(SOCKET sock)
{
    std::string SendBuf;
    SendBuf.reserve(256);
    std::getline(std::cin, SendBuf);
    if (SendBuf.empty())
    {
        return false;
    }
    int iSendSize = send(sock, &SendBuf[0], SendBuf.size(), 0);
    if (!Check(iSendSize)) {
        return false;
    }
    SendBuf.clear();  
    return true;
}
//쓰레드의 시작함수 : 반환되면 쓰레드는 정상종료된다.
DWORD WorkSend(LPVOID lpThreadParameter)
{
    SOCKET* sock = (SOCKET*)lpThreadParameter;
    while (1)
    {
        SendWork(*sock);
    }
    return 1;
}
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

    // 넌블록킹 소켓전환
    u_long on = 1;
    ioctlsocket(sock, FIONBIO, &on);

    // 쓰레드 생성
    DWORD ThreadId;
    HANDLE hThread1    = CreateThread(
        NULL,
        0,
        WorkSend,
        &sock,
        0,
        &ThreadId);
    while (1)
    {        
        if (!RecvWork(sock)) break;
    }
    closesocket(sock);

    CloseHandle(hThread1);
    // 윈속 소멸
    WSACleanup();    
}
