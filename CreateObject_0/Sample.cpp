#include "Sample.h"
void   Sample::Init() 
{
    m_pObject = new TObject2D;
    if (m_pObject)
    {
        m_pObject->Create();
        m_ObjList.emplace_back(m_pObject);
    }
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

    m_pObject->Frame();
}
void   Sample::Render() 
{    
    m_pObject->Render();
}
void   Sample::Release() 
{
    m_pObject->Release();
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