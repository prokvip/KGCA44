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
 * @brief ��Ʈ��ũ �۾��� ����� ��Ÿ���� ������
 */
enum TResult {
    TNet_FALSE = 0, ///< �۾� ����
	TNet_DisConnect, ///< ���� ����
    TNet_EWOULDBLOCK, ///< �۾��� ��ϵ��� ����
    TNet_TRUE, ///< �۾� ����
};

/**
 * @class TNetwork
 * @brief ��Ʈ��ũ �۾��� ó���ϴ� Ŭ����
 */
class TNetwork {
public:
    SOCKADDR_IN m_ServerAddr; ///< ���� �ּ�
    UPACKET     m_tPacket; ///< ��Ŷ ������
    char*       m_pRecvBuffer = nullptr;
    SOCKADDR_IN m_Address; ///< �ּ� ����
	bool        m_bConnect = false; ///< ���� ����
public:
    bool    m_bUseTCP = false; ///< TCP ��� ����
    SOCKET  m_Sock; ///< ����
    bool    m_bRun; ///< ���� ����
    bool    m_bThreadRun = false; ///< ������ ���� ����
    std::string m_szRecvData; ///< ���� ������
    int     m_iSendBytes = 0; ///< ���� ����Ʈ ��
    int     m_iRecvBytes = 0; ///< ���� ����Ʈ ��
    std::vector<std::string>  m_DataMsg; ///< ������ �޽���
    std::vector<UPACKET>  m_RecvPackets; 
    std::vector<UPACKET>  m_SendPackets; 
	virtual void    AddRecvPacket(UPACKET& packet);
	virtual void    AddSendPacket(UPACKET& packet);
    virtual UPACKET MakePacket(const char* msg, WORD type);
    virtual int     SendPacket(SOCKET sock, UPACKET& packet);
public:
    /**
     * @brief ������ ����
     * @param ip ���� IP �ּ�
     * @param iPort ���� ��Ʈ ��ȣ
     * @return ���� ���� ����
     */
    virtual bool Connect(std::string ip, UINT iPort);

    /**
     * @brief ������ ó��
     * @return ������ ó�� ���� ����
     */
    virtual bool Frame();

    /**
     * @brief �ڿ� ����
     * @return �ڿ� ���� ���� ����
     */
    virtual bool Release();

    /**
     * @brief ��Ŷ ����
     * @param sock ����
     * @param msg �޽���
     * @param type �޽��� Ÿ��
     * @return ���۵� ����Ʈ ��
     */
    virtual int SendPacket(SOCKET sock, const char* msg, WORD type);

public:
    /**
     * @brief ��Ʈ��ũ ���� �ʱ�ȭ
     */
    void Reset();

    /**
     * @brief ��Ʈ��ũ �ʱ�ȭ
     * @return �ʱ�ȭ ���� ����
     */
    bool Init();

    virtual SOCKET  CreateSocket();

    /**
     * @brief ��Ʈ��ũ ����
     * @return ���� ���� ����
     */
    bool Run();

    /**
     * @brief ���� ���� ����
     * @return ���� ���� ���� ����
     */
    bool DisConnect();

    /**
     * @brief ������ ���� �۾�
     * @return ���� �۾� ���� ����
     */
    virtual TResult RecvWork();

    /**
     * @brief ������ ���� �۾�
     * @param SendBuf ������ ������ ����
     * @return ���� �۾� ���� ����
     */
    bool SendWork(std::string SendBuf);

    /**
     * @brief ��Ʈ��ũ �۾� ��� Ȯ��
     * @param iCode ��� �ڵ�
     * @return �۾� ���
     */
    TResult Check(int iCode);

    /**
     * @brief �޽��� ���
     * @param msg ����� �޽���
     */
    void Print(std::string msg);

    /**
     * @brief ��Ŷ ó��
     * @return ��Ŷ ó�� ���� ����
     */
    bool PacketProcess();
};
