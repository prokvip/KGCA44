#include "TSelectModel.h"
bool  TEventSelect::Init() {

	// listensocket -> 0 index
	// clientsocket -> 1 index
	// clientsocket -> 2 index
	WSAEVENT hEvent = WSACreateEvent();
	// 소켓과 이벤트를 연동한다.
	WSAEventSelect(m_Sock, hEvent,FD_ACCEPT | FD_CLOSE );
	m_EventArray.push_back(hEvent);
	return true; 
}
bool  TEventSelect::Run() {

	//DWORD dwTimeout = 0;
	//INT iIndex = WSAWaitForMultipleEvents(m_EventArray.size(),&m_EventArray.at(0),
	//	FALSE, dwTimeout, FALSE	);
	//if (iIndex == WSA_WAIT_FAILED) return false;
	//if (iIndex == WSA_WAIT_TIMEOUT) return true;
	//// 어떤 이벤트냐?
	//WSANETWORKEVENTS NetworkEvent;
	//int iRet = WSAEnumNetworkEvents(m_Sock, m_EventArray[iIndex],&NetworkEvent);
	//if (NetworkEvent.lNetworkEvents & FD_ACCEPT)
	//{
	//	if (NetworkEvent.iErrorCode[FD_ACCEPT_BIT] != 0)
	//	{
	//		// ERROR
	//	}
	//	// accept()
	//	WSAEVENT hEvent = WSACreateEvent();
	//	// 소켓과 이벤트를 연동한다.
	//	WSAEventSelect(m_Sock, hEvent, 	FD_READ | FD_WRITE | FD_CLOSE);
	//	m_EventArray.push_back(hEvent);		
	//}
	//if (NetworkEvent.lNetworkEvents & FD_READ)
	//{
	//	if (NetworkEvent.iErrorCode[FD_READ_BIT] != 0)
	//	{
	//		// ERROR
	//	}
	//	//RECV()
	//}
	//if (NetworkEvent.lNetworkEvents & FD_WRITE)
	//{
	//	if (NetworkEvent.iErrorCode[FD_WRITE_BIT] != 0)
	//	{
	//		// ERROR
	//	}
	//	//SEND

	//}
	//if (NetworkEvent.lNetworkEvents & FD_CLOSE)
	//{
	//	if (NetworkEvent.iErrorCode[FD_CLOSE_BIT] != 0)
	//	{
	//		// ERROR
	//		//CLOSE();
	//	}
	//}
	return true; 
}