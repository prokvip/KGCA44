#include "TNetwork.h"
//쓰레드의 시작함수 : 반환되면 쓰레드는 정상종료된다.
DWORD WorkSend(LPVOID lpThreadParameter)
{
    TNetwork* net = (TNetwork*)lpThreadParameter;
    std::string SendBuf;
    SendBuf.reserve(256);
    while (net->m_bRun)
    {
        std::getline(std::cin, SendBuf);
        //net->SendWork(SendBuf);
        net->SendPacket(net->m_Sock, // 목적지
            SendBuf.c_str(),
            PACKET_CHAT_MSG);
    }
    return 1;
}

void    TNetwork::AddRecvPacket(UPACKET& packet)
{
	m_RecvPackets.push_back(packet);
    m_iRecvBytes = 0;
    m_pRecvBuffer = (char*)&m_tPacket;
    memset(m_pRecvBuffer, 0, PACKET_MAX_PACKET_SIZE);
}
void    TNetwork::AddSendPacket(UPACKET& packet)
{
    m_SendPackets.push_back(packet);
}
void    TNetwork::Print(std::string msg)
{
#ifdef _CONSOLE
    std::cout << msg << std::endl;
#else
    m_DataMsg.push_back(msg);
#endif

}
UPACKET TNetwork::MakePacket(const char* msg,WORD type)
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
    return sendpacket;
}
int     TNetwork::SendPacket(SOCKET sock,const char* msg,WORD type) {
    return 0;
}
int     TNetwork::SendPacket(SOCKET sock, UPACKET& packet)
{
    return 0;
}
void    TNetwork::Reset()
{
    m_iRecvBytes = 0;
}
bool    TNetwork::Init()
{
	// 윈속 초기화( 버전선택)
	WSADATA wsa;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iRet != 0) return 1;

    m_iRecvBytes = 0;
    m_pRecvBuffer = (char*)&m_tPacket;

    m_bRun = false;
    m_szRecvData.resize(1024);
	return true;
}
bool    TNetwork::Release()
{
	// 윈속 소멸
	WSACleanup();
	return true;
}
SOCKET TNetwork::CreateSocket()
{
    return NULL;
}
bool	TNetwork::Connect(std::string ip, UINT iPort) { return false; }
bool	TNetwork::DisConnect()
{
    closesocket(m_Sock);
    return true;
}
bool    TNetwork::Run()
{
    HANDLE hThread1 = CreateThread(NULL, 0,
        WorkSend, this, CREATE_SUSPENDED, NULL);   

    UPACKET recvPacket;
    ZeroMemory(&recvPacket, sizeof(recvPacket));
    char* pRecvMsg = (char*)&recvPacket;
    m_iRecvBytes = 0;
    // [2],2
    while (m_bRun)
    {        
        int iRecvByte = recv(m_Sock,&pRecvMsg[m_iRecvBytes],
            PACKET_HEADER_SIZE - m_iRecvBytes, 0);
        TResult ret  = Check(iRecvByte);
        if (ret == TResult::TNet_FALSE)
        {
            exit(1);
        }
        if (ret == TResult::TNet_TRUE)
        {
            m_iRecvBytes += iRecvByte;
            if (m_iRecvBytes > PACKET_HEADER_SIZE)
            {
                continue;
            }
        }
        
        if (m_iRecvBytes == PACKET_HEADER_SIZE)
        {
            while (recvPacket.ph.len > m_iRecvBytes)//m_iRecvBytes= 4
            {
                int iRecvByte = recv(m_Sock,
                    &pRecvMsg[m_iRecvBytes],
                    recvPacket.ph.len - m_iRecvBytes, 0);
                if (Check(iRecvByte) == TResult::TNet_TRUE)
                {
                    m_iRecvBytes += iRecvByte;
                }
            }
            // 패킷 완성
            if (recvPacket.ph.type == PACKET_JOIN_USER)
            {
                USER_NAME* pData = (USER_NAME*)recvPacket.msg;
                std::string msg = pData->name;
                msg += "님이 입장하셨습니다.";
                Print(msg);
            }
            if (recvPacket.ph.type == PACKET_CHAT_MSG)
            {
                recvPacket.msg[recvPacket.ph.len-PACKET_HEADER_SIZE] = 0;
                std::cout << recvPacket.msg << std::endl;
                std::string msg = recvPacket.msg;
                Print(msg);
            }
            if (recvPacket.ph.type == PACKET_GAME_START)
            {   
               
            }
            if (recvPacket.ph.type == PACKET_GAME_END)
            {
              
            }
            if (recvPacket.ph.type == PACKET_DRUP_USER)
            {
                USER_NAME* pData = (USER_NAME*)recvPacket.msg; 
                std::string msg = pData->name;
                msg += "님이 퇴장하셨습니다.";
                Print(msg);               
            }
            if (recvPacket.ph.type == PACKET_CHAT_NAME_SC_REQ)
            {
                std::string SendBuf;
                SendBuf.reserve(256);
                std::getline(std::cin, SendBuf);

                SendPacket(m_Sock, // 목적지
                    SendBuf.c_str(),
                    PACKET_CHAT_NAME_CS_ACK);
                m_bThreadRun = true;
               
                ResumeThread(hThread1);
            }
            m_iRecvBytes = 0;
            pRecvMsg = (char*)&recvPacket;
        }
        //if (!RecvWork()) break;
    }

    CloseHandle(hThread1);
    return true;
}
bool    TNetwork::Frame() { return true; };
bool    TNetwork::SendWork(std::string SendBuf)
{
    if (SendBuf.empty())
    {
        return true;
    }
    m_iSendBytes = send(m_Sock, &SendBuf[0], SendBuf.size(), 0);
    if (Check(m_iSendBytes) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
TResult     TNetwork::RecvWork() {
    TResult ret = TResult::TNet_FALSE;
    return ret;
}

TResult TNetwork::Check(int iCode)
{
    if (iCode == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        if (iError != WSAEWOULDBLOCK)
        {
            return TResult::TNet_FALSE;
        }
        return TResult::TNet_EWOULDBLOCK;
    }
    return TResult::TNet_TRUE;
}

bool    TNetwork::PacketProcess()
{
    for (auto& packet : m_RecvPackets)
    {
        // 패킷 완성
        if (packet.ph.type == PACKET_JOIN_ACK)
        {
            std::string msg;
            msg += "접속되었습니다.";
            Print(msg);
        }

        if (packet.ph.type == PACKET_CHAT_MSG)
        {
            Print(packet.msg);
        }

        if (packet.ph.type == PACKET_JOIN_USER)
        {
            USER_NAME* pData = (USER_NAME*)packet.msg;
            std::string msg = pData->name;
            msg += "님이 입장하셨습니다.";
            Print(msg);
        }

        if (packet.ph.type == PACKET_GAME_START)
        {

        }
        if (packet.ph.type == PACKET_GAME_END)
        {

        }
        if (packet.ph.type == PACKET_DRUP_USER)
        {
            USER_NAME* pData = (USER_NAME*)packet.msg;
            std::string msg = pData->name;
            msg += "님이 퇴장하셨습니다.";
            Print(msg);
        }
        if (packet.ph.type == PACKET_CHAT_NAME_SC_REQ)
        {

#ifdef _CONSOLE
            std::string SendBuf;
            SendBuf.reserve(256);
            std::getline(std::cin, SendBuf);
#else
            std::string SendBuf = "홍길동";
#endif

            SendPacket(m_Sock, // 목적지
                SendBuf.c_str(),
                PACKET_CHAT_NAME_CS_ACK);

            m_bThreadRun = true;
        }
    }
    m_RecvPackets.clear();
    return true;
}