#include "TNetworkTCP.h"
SOCKET TNetworkTCP::CreateSocket()
{
    m_Sock = socket(AF_INET, SOCK_STREAM, 0);// IPPROTO_TCP);
    return m_Sock;
}
bool	TNetworkTCP::Connect(std::string ip, UINT iPort)
{   
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(10000); // 받는 사람
    //sa.sin_addr.s_addr = inet_addr("192.168.0.88");// 전화번호
    inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);
    int iRet = connect(m_Sock, (SOCKADDR*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR) return false;

    // 넌블록킹 소켓전환
    u_long on = 1;
    ioctlsocket(m_Sock, FIONBIO, &on);

    m_bRun = true;
    return true;
}
bool    TNetworkTCP::Frame()
{
    if (m_bRun == false) return true;
    ZeroMemory(&m_tPacket, sizeof(m_tPacket));
    char* pRecvMsg = (char*)&m_tPacket;
    m_iRecvBytes = 0;
    // [2],2
    //while (m_bRun)
    {
        int iRecvByte = recv(m_Sock, &pRecvMsg[m_iRecvBytes],
            PACKET_HEADER_SIZE - m_iRecvBytes, 0);
        TResult ret = Check(iRecvByte);
        if (ret == TResult::TNet_FALSE)
        {
            exit(1);
        }
        if (ret == TResult::TNet_TRUE)
        {
            m_iRecvBytes += iRecvByte;
            if (m_iRecvBytes > PACKET_HEADER_SIZE)
            {
                return true;
            }
        }

        if (m_iRecvBytes == PACKET_HEADER_SIZE)
        {
            while (m_tPacket.ph.len > m_iRecvBytes)//m_iRecvBytes= 4
            {
                int iRecvByte = recv(m_Sock,
                    &pRecvMsg[m_iRecvBytes],
                    m_tPacket.ph.len - m_iRecvBytes, 0);
                if (Check(iRecvByte) == TResult::TNet_TRUE)
                {
                    m_iRecvBytes += iRecvByte;
                }
            }
            PacketProcess();

            m_iRecvBytes = 0;
            pRecvMsg = (char*)&m_tPacket;
        }
    }
    return true;
}
int     TNetworkTCP::SendPacket(SOCKET sock,
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

    m_iSendBytes = send(m_Sock, pMsg, sendpacket.ph.len, 0);
    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}