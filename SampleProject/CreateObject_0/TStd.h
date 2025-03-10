#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <tchar.h> // _T("") == L""
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <memory>
#include <atlconv.h>  // A2W
#pragma comment(lib,"d3d11.lib") // 加己 眠啊辆加己 
#pragma comment(lib,"d3dcompiler.lib") // 加己 眠啊辆加己 
#ifndef _DEBUG
    #pragma comment(lib, "DirectXTK_R.lib")
#else
    #pragma comment(lib, "DirectXTK_d.lib")
#endif


static std::wstring to_mw(const std::string& _src)
{
    USES_CONVERSION;
    return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
    USES_CONVERSION;
    return std::string(W2A(_src.c_str()));
};
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

static void DX_CHECK(HRESULT hr, const TCHAR* function)
{
    if (FAILED(hr))
    {
        LPWSTR output;
        WCHAR buffer[256] = { 0, };
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&output, 0, NULL);
        wsprintf(buffer, L"File=%ls\nLine=%d\nFuction=%ls", _T(__FILE__), __LINE__, function);
        std::wstring msg = buffer;
        msg += L"\n";
        msg += output;

        std::wstring title = L"ERROR(";
        title += std::to_wstring(hr);
        title += L")";
        MessageBox(NULL, msg.c_str(),
            title.c_str(), MB_OK);
    }
}