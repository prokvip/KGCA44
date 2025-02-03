#include "TNetwork.h"
int     TNetwork::SendPacket(SOCKET sock,
    const char* msg,
    WORD type)
{
    UINT iMsgSize = 0;
    if (msg != nullptr)
    {
        iMsgSize = strlen(msg);
    }
    UPACKET sendpacket;
    ZeroMemory(&sendpacket, sizeof(sendpacket));
    sendpacket.ph.len = PACKET_HEADER_SIZE + iMsgSize;
    sendpacket.ph.type = type;
    if (iMsgSize > 0)
    {
        memcpy(sendpacket.msg, msg, iMsgSize);
    }
    char* pMsg = (char*)&sendpacket;

    int iSendbyte = send(sock, pMsg, sendpacket.ph.len, 0);
    /*if (Check(iSendbyte) == TResult::TNet_FALSE)
    {
        return false;
    }*/
    return true;
}
void  TNetwork::Broadcasting(UPACKET& packet)
{
    for (auto sendHost = m_HostList.begin(); sendHost != m_HostList.end(); sendHost++)
    {
        THost& host = *sendHost;
        if (host.m_bConnect == false) continue;
        char* pMsg = (char*)&packet;
        int iSendSize = send(host.sock, pMsg,
            packet.ph.len, 0);
        Check(host, iSendSize);
    }
}
bool    TNetwork::CreateServer(int iPort)
{   
    m_Sock = socket(AF_INET, SOCK_STREAM, 0);// IPPROTO_TCP);
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);// 전화번호
    sa.sin_port = htons(iPort); // 받는 사람    
    int iRet = bind(m_Sock, (SOCKADDR*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR) return false;
    iRet = listen(m_Sock, SOMAXCONN);
    if (iRet == SOCKET_ERROR) return false;

    // 넌블록킹 소켓전환
    u_long on = 1;
    ioctlsocket(m_Sock, FIONBIO, &on);

    m_bRun = true;
    return true;
}
bool    TNetwork::Init()
{
    // 윈속 초기화( 버전선택)
    WSADATA wsa;
    int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (iRet != 0) return 1;
    return true;
}
bool    TNetwork::Release()
{
    closesocket(m_Sock);
    // 윈속 소멸
    WSACleanup();
    return true;
}
bool    TNetwork::AddHost(SOCKET clientSock, SOCKADDR_IN clientaddr)
{
    std::cout << "접속(IP):" << inet_ntoa(clientaddr.sin_addr)
        << "포트번호" << ntohs(clientaddr.sin_port)
        << std::endl;
    THost host;
    host.addr = clientaddr;
    host.sock = clientSock;
    m_HostList.push_back(host);
    return true;
}
bool    TNetwork::Accept()
{
    SOCKADDR_IN clientaddr;
    int addlen = sizeof(clientaddr);
    SOCKET clientSock = accept(m_Sock, (SOCKADDR*)&clientaddr,
        &addlen);
    if (CheckAccept(clientSock))
    {
        AddHost(clientSock, clientaddr);
        SendPacket(clientSock, nullptr, PACKET_CHAT_NAME_SC_REQ);
    }
    return true;
}
bool    TNetwork::RecvRun()
{
    for (auto iter = m_HostList.begin();
        iter != m_HostList.end();
        iter++)
    {
        THost& host = *iter;
        if (host.m_bConnect == false) continue;
        host.Run(*this);
    }
    return true;
}
bool    TNetwork::PacketProcess()
{
    for (auto recvHost = m_RecvPool.begin();
        recvHost != m_RecvPool.end();
        recvHost++)
    {
        UPACKET& packet = *recvHost;        
        Broadcasting(packet);
    }
    m_RecvPool.clear();
    return true;
}
bool    TNetwork::PostProcess()
{
    // 종료처리
    for (auto iter = m_HostList.begin();
        iter != m_HostList.end(); )
    {
        THost& host = *iter;
        if (host.m_bConnect == false)
        {
            std::cout << "접속종료(IP):" <<
                inet_ntoa(host.addr.sin_addr)
                << "포트번호" << ntohs(host.addr.sin_port)
                << std::endl;
            closesocket(host.sock);

            iter = m_HostList.erase(iter);

            // DrupHost
            //m_RecvPool.emplace_back(m_tPacket);
        }
        else
        {            
            iter++;
        }
    }
    return true;
}
bool    TNetwork::Run()
{
    while (m_bRun)
    {
        Accept();
        RecvRun();        
        PacketProcess();
        PostProcess();        
    }    
    return true;
}

bool TNetwork::Check(THost& host, int iCode)
{
    if (iCode == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        if (iError != WSAEWOULDBLOCK)
        {
            host.m_bConnect = false;
        }
    }
    else
    {
        return true;
    }
    return false;
}
bool TNetwork::CheckAccept(int iCode)
{
    if (iCode == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        if (iError != WSAEWOULDBLOCK)
        {
            exit(1);
        }
    }
    else
    {
        return true;
    }
    return false;
}