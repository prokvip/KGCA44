#include "Sample.h"
void   Sample::Init() 
{
}
void   Sample::Frame()  
{
    if (g_GameKey.dwWkey == KEY_PUSH)
    {
        INT A = 0;
    }
    if (g_GameKey.dwWkey == KEY_UP)
    {
        INT A = 0;
    }
}
void   Sample::Render() 
{    
    //// 디바이스컨텍스트(화면에 뿌리는 허가권)
    //HDC hc = GetDC(g_hWnd);
    //RECT rt;
    //GetClientRect(g_hWnd, &rt);
    //DrawText(hc, L"AAa", -1, &rt, DT_LEFT | DT_VCENTER);
    //ReleaseDC(g_hWnd,hc);
}
void   Sample::Release() 
{
  
}

//GameStart(800, 600);
int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    Sample sample;
    sample.SetWindowClass(hInstance);
    sample.SetWindow();
    sample.GameRun();    
}