#pragma once
#include "THost.h"
#define MAX_NUM_WORK_THREAD 3

class TNetwork;

struct OVERLAPPED2 : TObjectPool<OVERLAPPED2>
{
	enum { MODE_RECV=0, MODE_SEND=1,};
	OVERLAPPED m_ov;
	UINT  m_iFlag;
	OVERLAPPED2()
	{
		m_iFlag = MODE_RECV;
		ZeroMemory(&m_ov, sizeof(m_ov));
	}
	OVERLAPPED2(UINT flag)
	{
		m_iFlag = flag;
		ZeroMemory(&m_ov, sizeof(m_ov));
	}
};

// IOCP(Input,Output, Completion, Port)
class TNetModel
{
public:
	SOCKET		m_Sock;
	TNetwork*   m_pNet=nullptr;
	HANDLE m_hWorkerThread[MAX_NUM_WORK_THREAD];
	HANDLE m_hIOCP;
public:
	virtual bool  Init(TNetwork* pNet);
	virtual bool  Run();
	SOCKET  Accept();
};

class TAsyncSelect : public TNetModel
{
public:
	virtual bool  Init(TNetwork* pNet) { return true; }
	virtual bool  Run() { return true; }
};

class TStdSelect : public TNetModel
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

class TEventSelect : public TNetModel
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
