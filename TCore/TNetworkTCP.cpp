#include "TNetworkTCP.h"
//void TUser::Put(char* pBuffer, DWORD dwByte)
//{
//    //m_dwWritePos 다음 버퍼 위치
//    //m_dwStartPos 패킷의 시작 위치
//    //m_dwReadPos  받은 데이터 크기
//    if (m_dwWritePos + dwByte >= MAX_STREAM_SIZE)
//    {
//        if (m_dwReadPos > 0)
//        {
//            memmove(m_szPackStream, &m_szPackStream[m_dwStartPos], m_dwReadPos);
//        }
//        m_dwStartPos = 0;
//        m_dwWritePos = m_dwReadPos;
//    }
//    memcpy(&m_szPackStream[m_dwWritePos], pBuffer, dwByte);
//    m_dwWritePos += dwByte;
//    m_dwReadPos += dwByte;
//
//    if (m_dwReadPos >= PACKET_HEADER_SIZE)
//    {
//        UPACKET* pPacket = (UPACKET*)&m_szPackStream[m_dwStartPos];
//        // 받은 데이터 크기(1개의 패킷보다 크면)
//        if (pPacket->ph.len <= m_dwReadPos)
//        {
//            do {
//                T_PACKET tPacket;
//                ZeroMemory(&tPacket, sizeof(tPacket));
//                tPacket.pUser = this;
//                memcpy(&tPacket.packet, &m_szPackStream[m_dwStartPos], pPacket->ph.len);
//                I_Server.m_RecvPool.Push(tPacket);
//
//                m_dwReadPos -= pPacket->ph.len;
//                m_dwStartPos += pPacket->ph.len;
//                if (m_dwReadPos < PACKET_HEADER_SIZE)
//                {
//                    break;
//                }
//                pPacket = (UPACKET*)&m_szPackStream[m_dwStartPos];
//                if (pPacket->ph.type == 0)
//                {
//                    break;
//                }
//            } while (pPacket->ph.len <= m_dwReadPos);
//        }
//    }
//}

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
int     TNetworkTCP::SendPacket(SOCKET sock, UPACKET& packet)
{
    char* pMsg = (char*)&packet;
    m_iSendBytes = send(sock, pMsg, packet.ph.len, 0);
    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
int     TNetworkTCP::SendPacket(SOCKET sock, const char* msg, WORD type)
{
    UPACKET sendpacket = MakePacket(msg, type);   
    char* pMsg = (char*)&sendpacket;
    m_iSendBytes = send(m_Sock, pMsg, sendpacket.ph.len, 0);
    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
TResult     TNetworkTCP::RecvWork()
{
	TResult tRet = TResult::TNet_FALSE;
    int iRecvByte = 0;
    if (m_pRecvBuffer != nullptr)
    {
        if (m_iRecvBytes < PACKET_HEADER_SIZE)
        {
            iRecvByte = recv(m_Sock,
                &m_pRecvBuffer[m_iRecvBytes],
                PACKET_HEADER_SIZE - m_iRecvBytes, 0);
            
            tRet = Check(iRecvByte);
            if (tRet == TResult::TNet_TRUE)
            {
                m_iRecvBytes += iRecvByte;                
                if (m_tPacket.ph.len == m_iRecvBytes)//m_iRecvBytes= 4
                {
                    AddRecvPacket(m_tPacket);
                }
            }
        }
        else
        {
            if (m_tPacket.ph.len > m_iRecvBytes)//m_iRecvBytes= 4
            {
                iRecvByte = recv(m_Sock,
                    &m_pRecvBuffer[m_iRecvBytes],
                    m_tPacket.ph.len - m_iRecvBytes, 0);
                tRet = Check(iRecvByte);
                if (tRet == TResult::TNet_TRUE)
                {
                    m_iRecvBytes += iRecvByte;
                    if (m_iRecvBytes == m_tPacket.ph.len)
                    {
                        AddRecvPacket(m_tPacket);
                    }
                }
            }
        }
    }
    return tRet;
}