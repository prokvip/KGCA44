#pragma once
#define WM_ASYNC_SOCKET WM_USER + 1
//빌드 후 이벤트
//copy "*.h" "..\\..\\TCore\\Inc"
//copy "..\\..\\output\\debug\\TCore.lib" "..\\..\\TCore\\lib\\"

#include "TGameCore.h"
#include "TNetworkTCP.h"
#include "TNetworkUDP.h"
class Sample : public TGameCore
{
	HWND   m_hEdit;
	HWND   m_hSendBtn;
	HWND   m_hListBtn;
	std::shared_ptr<TNetwork> m_pNet;
public:
	void    Init();
	void    PreFrame();
	void    Frame();
	void    Render();
	void    Release();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

