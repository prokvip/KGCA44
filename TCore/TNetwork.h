#pragma once
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>   // std::thread
#include <conio.h>
#include <process.h> // _beginthreadex
#include "TProtocol.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

/**
 * @enum TResult
 * @brief 네트워크 작업의 결과를 나타내는 열거형
 */
enum TResult {
    TNet_FALSE = 0, ///< 작업 실패
	TNet_DisConnect, ///< 연결 해제
    TNet_EWOULDBLOCK, ///< 작업이 블록되지 않음
    TNet_TRUE, ///< 작업 성공
};

/**
 * @class TNetwork
 * @brief 네트워크 작업을 처리하는 클래스
 */
class TNetwork {
public:
    SOCKADDR_IN m_ServerAddr; ///< 서버 주소
    UPACKET     m_tPacket; ///< 패킷 데이터
    char*       m_pRecvBuffer = nullptr;
    SOCKADDR_IN m_Address; ///< 주소 정보
	bool        m_bConnect = false; ///< 연결 여부
public:
    bool    m_bUseTCP = false; ///< TCP 사용 여부
    SOCKET  m_Sock; ///< 소켓
    bool    m_bRun; ///< 실행 여부
    bool    m_bThreadRun = false; ///< 스레드 실행 여부
    std::string m_szRecvData; ///< 수신 데이터
    int     m_iSendBytes = 0; ///< 전송 바이트 수
    int     m_iRecvBytes = 0; ///< 수신 바이트 수
    std::vector<std::string>  m_DataMsg; ///< 데이터 메시지
    std::vector<UPACKET>  m_RecvPackets; 
    std::vector<UPACKET>  m_SendPackets; 
	virtual void    AddRecvPacket(UPACKET& packet);
	virtual void    AddSendPacket(UPACKET& packet);
    virtual UPACKET MakePacket(const char* msg, WORD type);
    virtual int     SendPacket(SOCKET sock, UPACKET& packet);
public:
    /**
     * @brief 서버에 연결
     * @param ip 서버 IP 주소
     * @param iPort 서버 포트 번호
     * @return 연결 성공 여부
     */
    virtual bool Connect(std::string ip, UINT iPort);

    /**
     * @brief 프레임 처리
     * @return 프레임 처리 성공 여부
     */
    virtual bool Frame();

    /**
     * @brief 자원 해제
     * @return 자원 해제 성공 여부
     */
    virtual bool Release();

    /**
     * @brief 패킷 전송
     * @param sock 소켓
     * @param msg 메시지
     * @param type 메시지 타입
     * @return 전송된 바이트 수
     */
    virtual int SendPacket(SOCKET sock, const char* msg, WORD type);

public:
    /**
     * @brief 네트워크 상태 초기화
     */
    void Reset();

    /**
     * @brief 네트워크 초기화
     * @return 초기화 성공 여부
     */
    bool Init();

    virtual SOCKET  CreateSocket();

    /**
     * @brief 네트워크 실행
     * @return 실행 성공 여부
     */
    bool Run();

    /**
     * @brief 서버 연결 해제
     * @return 연결 해제 성공 여부
     */
    bool DisConnect();

    /**
     * @brief 데이터 수신 작업
     * @return 수신 작업 성공 여부
     */
    virtual TResult RecvWork();

    /**
     * @brief 데이터 전송 작업
     * @param SendBuf 전송할 데이터 버퍼
     * @return 전송 작업 성공 여부
     */
    bool SendWork(std::string SendBuf);

    /**
     * @brief 네트워크 작업 결과 확인
     * @param iCode 결과 코드
     * @return 작업 결과
     */
    TResult Check(int iCode);

    /**
     * @brief 메시지 출력
     * @param msg 출력할 메시지
     */
    void Print(std::string msg);

    /**
     * @brief 패킷 처리
     * @return 패킷 처리 성공 여부
     */
    bool PacketProcess();
};
