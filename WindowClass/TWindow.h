#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
class TWindow
{
	HINSTANCE   m_hInstance;
	HWND		m_hWnd;
	bool		m_bRun = true;
public:
	// 윈도우클래스 등록
	bool   SetWindowClass(HINSTANCE hInstance);
	// 윈도우창 생성
	bool   SetWindow(
		std::wstring title = L"Sample Project",
		UINT iWindowX=800,
		UINT iWindowY=600);
	// 메세지 프로시쳐, 처리
	bool   MessageProcess();
public:
	virtual bool GameRun();
};

