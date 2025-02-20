#pragma once
#include "THost.h"
class TNetwork;
class TSelectModel
{
public:
	SOCKET		m_Sock;
	TNetwork*   m_pNet=nullptr;
public:
	virtual bool  Init(TNetwork* pNet) = 0;
	virtual bool  Run() = 0;
};

class TAsyncSelect : public TSelectModel
{
public:
	virtual bool  Init(TNetwork* pNet) { return true; }
	virtual bool  Run() { return true; }
};

class TStdSelect : public TSelectModel
{
	FD_SET			m_rSet;
	FD_SET			m_wSet;
	FD_SET			m_eSet;
public:
	virtual bool  Init(TNetwork* pNet);
	virtual bool  Run();
	void    Rebuild();
	bool	NetEvent_Check(int iEvent);
};

class TEventSelect : public TSelectModel
{
	std::vector<WSAEVENT>  m_EventArray;
	std::vector<SOCKET>    m_SockArray;
	std::vector<bool>      m_bDisconnectArray;
public:
	THost* GetHost(SOCKET sock);
	virtual bool  Init(TNetwork* pNet);
	virtual bool  Run();
	void    Rebuild();
	void    Disconnect(UINT iIndex);
public:
	bool  NetEvent_Check(UINT iEventt);
	bool  NetEvent_Recv(UINT iEvent, WSANETWORKEVENTS NetworkEvent);
	bool  NetEvent_Close(UINT iEvent, WSANETWORKEVENTS NetworkEvent);
	bool  NetEvent_Write(UINT iEvent, WSANETWORKEVENTS NetworkEvent);
	
};
