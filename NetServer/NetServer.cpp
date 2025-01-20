#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
int main()
{
    WSADATA wsa;
    int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (iRet != 0) return 1;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);// IPPROTO_TCP);
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);// 전화번호
    sa.sin_port = htons(10000); // 받는 사람
    //iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
    iRet = bind(sock, (SOCKADDR*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR) return 1;
    iRet = listen(sock, SOMAXCONN);
    if (iRet == SOCKET_ERROR) return 1;
    SOCKADDR_IN clientaddr;
    int addlen = sizeof(clientaddr);

    std::string SendBuf;
    while (1)
    {
        SOCKET clientSock = accept(sock, (SOCKADDR*)&clientaddr,
            &addlen);
        std::cout   << "접속(IP):" << inet_ntoa(clientaddr.sin_addr)
                    << "포트번호" << ntohs(clientaddr.sin_port) 
                    <<std::endl;
        while (1)
        {
            char Recvbuffer[256] = { 0, };
            int iRecvSize = recv(clientSock, Recvbuffer, sizeof(Recvbuffer), 0);
            if (iRecvSize == 0)
            {
                std::cout << "접속종료(IP):" << inet_ntoa(clientaddr.sin_addr)
                    << "포트번호" << ntohs(clientaddr.sin_port)
                    << std::endl;
                closesocket(clientSock);
            }
            std::cout << Recvbuffer << std::endl;
            SendBuf = Recvbuffer;
            SendBuf += " 뭐라고하노";
            int iSendSize = send(clientSock, 
                &SendBuf[0], SendBuf.size(), 0);
            if (iSendSize == SOCKET_ERROR)
            {
                std::cout << "접속종료(IP):" << inet_ntoa(clientaddr.sin_addr)
                    << "포트번호" << ntohs(clientaddr.sin_port)
                    << std::endl;
                closesocket(clientSock);
                std::cout << "서버에 문제가 있다." << std::endl;
                break;
            }
            SendBuf.clear();
        }        
    }
    Sleep(10000);
    
    closesocket(sock);
    WSACleanup();
    
}
