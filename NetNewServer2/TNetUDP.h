#pragma once
#include "TNetwork.h"
class TNetUDP : public TNetwork
{
public:
	UPACKET     m_tPacket;
	SOCKADDR_IN m_Address;
public:
	virtual bool  CreateServer(int iPort) override;
	virtual bool  Run() override;
	virtual bool  RecvRun() override;
	virtual int   SendPacket(SOCKADDR_IN addr, const char* msg,WORD type) override;
	virtual bool  PostProcess() override;
	virtual void  Broadcasting(UPACKET& packet) override;
};

