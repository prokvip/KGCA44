#include "TNetwork.h"
bool    TNetwork::Init()
{
	// 윈속 초기화( 버전선택)
	WSADATA wsa;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iRet != 0) return 1;

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
bool	TNetwork::Connect(std::string ip, UINT iPort)
{
    //  TCP & IP 프로토콜
    m_Sock = socket(AF_INET, SOCK_STREAM, 0);// IPPROTO_TCP);

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
bool	TNetwork::DisConnect()
{
    closesocket(m_Sock);
    return true;
}
bool    TNetwork::Run()
{
    while (m_bRun)
    {
        if (!RecvWork()) break;
    }
    return true;
}
bool TNetwork::SendWork(std::string SendBuf)
{
    if (SendBuf.empty())
    {
        return true;
    }
    m_iSendbyte = send(m_Sock, &SendBuf[0], SendBuf.size(), 0);
    if (Check(m_iSendbyte) == TResult::TNet_FALSE)
    {
        return false;
    }
    return true;
}
bool TNetwork::RecvWork()
{
    m_iRecvbyte = recv(m_Sock,&m_szRecvData[0], m_szRecvData.size(), 0);
    if (m_iRecvbyte == 0)
    {
        return false;
    }
    if (Check(m_iRecvbyte)== TResult::TNet_TRUE)
    {
        std::string msg;
        msg = m_szRecvData.substr(0, m_iRecvbyte);
        std::cout << msg.c_str() << std::endl;
    }
    return true;
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