#include "TNetworkUDP.h"
SOCKET TNetworkUDP::CreateSocket()
{
    m_Sock = socket(AF_INET, SOCK_DGRAM, 0);// IPPROTO_TCP);
    return m_Sock;
}
bool    TNetworkUDP::Connect(std::string ip, UINT iPort)
{
    ZeroMemory(&m_ServerAddr, sizeof(m_ServerAddr));
    m_ServerAddr.sin_family = AF_INET;    
    m_ServerAddr.sin_port = htons(iPort); // 받는 사람 
    //m_ServerAddr.sin_addr.s_addr = inet_addr(ip.c_str());// 전화번호
    inet_pton(AF_INET, ip.c_str(), &m_ServerAddr.sin_addr);
    
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);// 전화번호
    sa.sin_port = htons(iPort); // 받는 사람    
    int iRet = bind(m_Sock, (SOCKADDR*)&sa, sizeof(sa));

    // 넌블록킹 소켓전환
    u_long on = 1;
    ioctlsocket(m_Sock, FIONBIO, &on);

    SendPacket(m_Sock, nullptr, PACKET_JOIN_REQ);


    m_bRun = true;
    return true;
}
bool    TNetworkUDP::Frame()
{
    int iAddlen = sizeof(m_Address);
    char* pRecvMsg = (char*)&m_tPacket;
    int iRecvByte = recvfrom(m_Sock, pRecvMsg,
        PACKET_MAX_PACKET_SIZE, 0,
        (SOCKADDR*)&m_Address, &iAddlen);

    if (iRecvByte == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        if (iError != WSAEWOULDBLOCK)
        {
            //return TResult::TNet_FALSE;
            return false;
        }
        //return TResult::TNet_EWOULDBLOCK;
    }
    else
    {
        PacketProcess();
    }
    //return TResult::TNet_TRUE;
    return true;
}
int     TNetworkUDP::SendPacket(SOCKET sock, const char* msg,WORD type)
{
    UPACKET sendpacket = MakePacket(msg, type);
    char* pMsg = (char*)&sendpacket;

    m_iSendBytes = sendto(m_Sock, pMsg,
        sendpacket.ph.len, 0,
        (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr));

    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
int     TNetworkUDP::SendPacket(SOCKET sock, UPACKET& packet)
{
    char* pMsg = (char*)&packet;
    m_iSendBytes = sendto(sock, pMsg,
        packet.ph.len, 0,
        (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr));

    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
TResult TNetworkUDP::RecvWork()
{
    TResult tRet = TResult::TNet_FALSE;
    int iAddlen = sizeof(m_Address);
    char* pRecvMsg = (char*)&m_tPacket;
    int iRecvByte = recvfrom(m_Sock, pRecvMsg,
        PACKET_MAX_PACKET_SIZE, 0,
        (SOCKADDR*)&m_Address, &iAddlen);
    tRet = Check(iRecvByte);
    if (tRet == TResult::TNet_TRUE)
    {
        AddRecvPacket(m_tPacket);
    }
    return tRet;
}