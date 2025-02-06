#pragma once
#include "THost.h"

class TNetwork
{
protected:
    SOCKET  m_Sock;
    bool    m_bRun = false;
    std::list<THost> m_HostList;
public:
    std::list<UPACKET>  m_RecvPool;
    std::list<UPACKET>  m_SendPool;
public:
    bool   Init();
    bool   Release();
public:   
    virtual bool  CreateServer(int iPort);
    virtual bool  Run();
    virtual bool  RecvRun();
    virtual bool  PostProcess();
    virtual bool  PacketProcess();
    virtual int   SendPacket(SOCKET sock, const char* msg, WORD type);
    virtual int   SendPacket(SOCKADDR_IN addr, const char* msg, WORD type);
    virtual void  Broadcasting(UPACKET& packet);
public:
   
    bool  AddHost(SOCKET clientSock, SOCKADDR_IN clientaddr);
    bool  Accept();    
  
public:
    bool Check(THost& host, int iCode);
    bool CheckAccept(int iCode);
};
class TNetworkTCP : public TNetwork {};
class TNetworkUDP : public TNetwork 
{
public:
    virtual bool  CreateServer(int iPort);
};


class TNetworkClientTCP : public TNetworkTCP {};
class TNetworkServerTCP : public TNetworkTCP {};
class TNetworkClientUDP : public TNetworkUDP {};
class TNetworkServerUDP : public TNetworkUDP {};

