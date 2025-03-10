#include "TSelectModel.h"
#include "TNetwork.h"
THost* TEventSelect::GetHost(SOCKET sock)
{
	for (auto& host : m_pNet->m_HostList)
	{		
		if (host.sock == sock)
		{
			return &host;
		}
	}
	return nullptr;
}
void  TEventSelect::Rebuild()
{
	// rebuild
	auto eventarray = m_EventArray;
	auto sockarray = m_SockArray;
	m_EventArray.clear();
	m_SockArray.clear();

	UINT iIndex = 1;
	for (auto& host : m_pNet->m_HostList)
	{
		if (host.m_bConnect == false)
		{
			m_bDisconnectArray[iIndex] = false ;
		}
		iIndex++;
	}

	for (int iArray = 0; iArray < m_bDisconnectArray.size(); iArray++)
	{
		if (m_bDisconnectArray[iArray] != false)
		{
			m_EventArray.push_back(eventarray[iArray]);
			m_SockArray.push_back(sockarray[iArray]);
		}
	}

	m_bDisconnectArray.clear();
	for (int iArray = 0; iArray < m_EventArray.size(); iArray++)
	{
		m_bDisconnectArray.push_back(true);
	}
}
void  TEventSelect::Disconnect(UINT iIndex)
{
	THost* host = GetHost(m_SockArray[iIndex]);
	if (host)host->m_bConnect = false;
	m_bDisconnectArray[iIndex] = false;	
}

bool  TEventSelect::Init(TNetwork* pNet) {

	m_pNet = pNet;
	m_Sock = m_pNet->m_Sock;
	// listensocket -> 0 index
	// clientsocket -> 1 index
	// clientsocket -> 2 index
	WSAEVENT hEvent = WSACreateEvent();
	// 소켓과 이벤트를 연동한다.
	WSAEventSelect(m_Sock, hEvent,FD_ACCEPT | FD_CLOSE );
	m_EventArray.push_back(hEvent);
	m_SockArray.push_back(m_Sock);
	m_bDisconnectArray.push_back(true);
	return true; 
}
bool  TEventSelect::Run() {

	Rebuild();

	DWORD dwTimeout = 0;
	INT iIndex = WSAWaitForMultipleEvents(m_EventArray.size(),&m_EventArray.at(0),	FALSE, dwTimeout, FALSE	);
	if (!NetEvent_Check(iIndex))
	{
		return false;
	}
	// 어떤 이벤트냐?
	WSANETWORKEVENTS NetworkEvent;
	int iRet = WSAEnumNetworkEvents(m_SockArray[iIndex],m_EventArray[iIndex],&NetworkEvent);
	if (iRet == SOCKET_ERROR)
	{
		Disconnect(iIndex);
		DWORD dwError = WSAGetLastError();
		return false;
	}
	if (NetworkEvent.lNetworkEvents & FD_ACCEPT)
	{
		if (NetworkEvent.iErrorCode[FD_ACCEPT_BIT] != 0)
		{
			exit(1);
			return false;
		}
		SOCKET sock = m_pNet->Accept();
		WSAEVENT hEvent = WSACreateEvent();
		// 소켓과 이벤트를 연동한다.
		WSAEventSelect(sock, hEvent, FD_READ | FD_WRITE | FD_CLOSE);
		m_EventArray.push_back(hEvent);	
		m_SockArray.push_back(sock);	
		m_bDisconnectArray.push_back(true);
	}
	if (NetworkEvent.lNetworkEvents & FD_READ)
	{
		if (!NetEvent_Recv(iIndex, NetworkEvent))
		{
			return false;
		}		
	}
	if (NetworkEvent.lNetworkEvents & FD_WRITE)
	{
		if (NetEvent_Write(iIndex, NetworkEvent))
		{
			return false;
		}
	}
	if (NetworkEvent.lNetworkEvents & FD_CLOSE)
	{
		if (NetEvent_Close(iIndex, NetworkEvent))
		{
			return false;
		}
	}

	// 동시에 이벤트가 발생하면 
	// 후순위 이벤트도 확인해야 한다.
	for (INT iEvent = iIndex+1;iEvent < m_EventArray.size(); iEvent++)
	{
		INT iSignal = WSAWaitForMultipleEvents(1, &m_EventArray.at(iEvent),	TRUE, dwTimeout, FALSE);
		if (!NetEvent_Check(iSignal))
		{
			continue;
		}		
		// 어떤 이벤트냐?
		WSANETWORKEVENTS NetworkEvent;
		int iRet = WSAEnumNetworkEvents(m_SockArray[iEvent],m_EventArray[iEvent], &NetworkEvent);
		if (iRet == SOCKET_ERROR)
		{
			Disconnect(iEvent);
			continue;
		}
		if (NetworkEvent.lNetworkEvents & FD_READ)
		{
			if (!NetEvent_Recv(iEvent, NetworkEvent))
			{
				continue;
			}
		}
		if (NetworkEvent.lNetworkEvents & FD_WRITE)
		{
			if (NetEvent_Write(iEvent, NetworkEvent))
			{					
				continue;
			}
			
		}
		if (NetworkEvent.lNetworkEvents & FD_CLOSE)
		{
			if (NetEvent_Close(iEvent, NetworkEvent))
			{				
				continue;
			}			
		}
	}

	return true; 
}
bool  TEventSelect::NetEvent_Check(UINT iEvent)
{
	if (iEvent == SOCKET_ERROR)
	{
		Disconnect(iEvent);
		return false;
	}
	if (iEvent == WSA_WAIT_FAILED) return false;;
	if (iEvent == WSA_WAIT_TIMEOUT) return false;
	return true;
}
bool  TEventSelect::NetEvent_Write(UINT iEvent, WSANETWORKEVENTS NetworkEvent)
{
	if (NetworkEvent.iErrorCode[FD_WRITE_BIT] != 0)
	{
		Disconnect(iEvent);
		return false;
	}
	return true;
}
bool  TEventSelect::NetEvent_Close(UINT iEvent, WSANETWORKEVENTS NetworkEvent)
{
	if (NetworkEvent.iErrorCode[FD_CLOSE_BIT] != 0)
	{
		Disconnect(iEvent);
		return false;
	}
	Disconnect(iEvent);
	return true;
}
bool  TEventSelect::NetEvent_Recv(UINT iEvent, WSANETWORKEVENTS NetworkEvent)
{
	if (NetworkEvent.iErrorCode[FD_READ_BIT] != 0)
	{
		Disconnect(iEvent);
		return false;
	}
	THost* host = GetHost(m_SockArray[iEvent]);
	if (host->m_bConnect != false)
	{
		host->RunTCP(*m_pNet);
	}
	return true;
}