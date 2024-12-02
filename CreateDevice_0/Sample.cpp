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