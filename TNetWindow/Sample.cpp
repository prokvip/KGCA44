#include "Sample.h"
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 200:
        {
            char buffer[MAX_PATH] = { 0, };
            SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);            
            auto packet = m_pNet->MakePacket(buffer, PACKET_CHAT_MSG);
            m_pNet->AddSendPacket(packet);
        }break;
        }
    }break;
    case WM_ASYNC_SOCKET:
    {
        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_CONNECT:
        {
            m_pNet->m_bConnect = true;
        }break;
        case FD_CLOSE:
        {
            m_pNet->m_bConnect = false;
        }break;
        case FD_READ:
        {
            TResult iRet = m_pNet->RecvWork();
            if (iRet == TResult::TNet_DisConnect 
                || iRet == TResult::TNet_FALSE)
                {
                    m_pNet->m_bConnect = false;
                    m_pNet->m_iRecvBytes = 0;
                    m_pNet->m_pRecvBuffer = (char*)&m_pNet->m_tPacket;
                    break;
            }
            if (iRet != TResult::TNet_EWOULDBLOCK)
            {
                PostMessage(hWnd, WM_ASYNC_SOCKET, wParam, FD_READ);
            }
            else
            {
                int k = 0;
            }
        };
        case FD_WRITE:
        {
            bool  m_bSendEnable = true;
            
        }break;
        }
	}break;
	}
    
    return 0;
}
void    Sample::Init()
{    
    m_hEdit = CreateWindow(L"edit", NULL, 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        500, 10, 200, 25, m_hWnd, (HMENU)100, 
        m_hInstance, NULL);
    m_hSendBtn = CreateWindow(L"button",L"Send",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        700, 10, 50, 25, m_hWnd, (HMENU)200,
        m_hInstance, NULL);
    m_hListBtn = CreateWindow(L"listbox", NULL,
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
        0, 0, 400, 600, m_hWnd, (HMENU)300,
        m_hInstance, NULL);

	//m_pNet = std::make_shared<TNetworkUDP>();
    m_pNet = std::make_shared<TNetworkTCP>();
    m_pNet->Init();
	m_pNet->CreateSocket();
    //error C4996 : 'WSAAsyncSelect' : Use WSAEventSelect() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
    int iRet = WSAAsyncSelect(m_pNet->m_Sock, m_hWnd,
        WM_ASYNC_SOCKET,
        FD_CONNECT | FD_CLOSE | FD_READ | FD_WRITE);
    if (iRet == SOCKET_ERROR)
    {
        MessageBoxA(m_hWnd, "WSAAsyncSelect", "Error", MB_OK);
    }
    m_pNet->Connect("192.168.0.88", 10000);
    
}
void    Sample::PreFrame()
{
    for (int iSend = 0; iSend < m_pNet->m_SendPackets.size(); iSend++)
    {
        auto packet = m_pNet->m_SendPackets[iSend];
        m_pNet->SendPacket(m_pNet->m_Sock, packet);
    }
    m_pNet->m_SendPackets.clear();

    m_pNet->PacketProcess();

    if (m_pNet->m_DataMsg.size() > 0)
    {
        for (int iMsg = 0; iMsg < m_pNet->m_DataMsg.size(); iMsg++)
        {
            SendMessageA(m_hListBtn,
                LB_ADDSTRING, 0,
                (LPARAM)m_pNet->m_DataMsg[iMsg].c_str());
        }
        m_pNet->m_DataMsg.clear();
        int iMsgCounter = SendMessage(m_hListBtn,
            LB_GETCOUNT, 0, 0);
        if (iMsgCounter > 30)
        {
            SendMessage(m_hListBtn, LB_RESETCONTENT, 0, 0);
        }
    }
}
void    Sample::Frame()
{    
}
void    Sample::Render()
{    
}
void    Sample::Release()
{
    m_pNet->SendPacket(m_pNet->m_Sock, nullptr, PACKET_DRUP_USER);
    m_pNet->Release();
}

GAME_RUN