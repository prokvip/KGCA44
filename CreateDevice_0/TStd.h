#pragma once
#include <windows.h>
#include <d3d11.h>
#include <tchar.h> // _T("") == L""
#include <string>
#pragma comment(lib,"d3d11.lib") // 加己 眠啊辆加己 



struct TGameKey
{
	//DWORD frontMove;// w or VK_UP
	//DWORD Attack;// Lbutton or VK_ENTER
	DWORD dwWkey;
	DWORD dwSkey;
	DWORD dwAkey;
	DWORD dwDkey;
	DWORD dwLeftClick;
	DWORD dwRightClick;
	DWORD dwMiddleClick;
	DWORD dwExit;
	DWORD dwSpace;
};

extern POINT g_WindowSize;
extern HWND  g_hWnd;
extern TGameKey g_GameKey;
extern float   g_fSPF;
extern float   g_fGT;