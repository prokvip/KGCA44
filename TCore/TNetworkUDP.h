#pragma once
#include "TNetwork.h"
class TNetworkUDP :    public TNetwork
{
public:
	virtual SOCKET  CreateSocket() override;
	virtual bool	Connect(std::string ip, UINT iPort) override;
	virtual int     SendPacket(SOCKET sock, const char* msg, WORD type) override;
	virtual int     SendPacket(SOCKET sock, UPACKET& packet) override;
	virtual bool    Frame() override;
	virtual TResult RecvWork()override;
};

