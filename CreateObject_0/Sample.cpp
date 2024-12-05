#include "Sample.h"

void   Sample::Init() 
{
    m_pObject = std::make_shared<TObject2D>();
    if (m_pObject)
    {
        m_pObject->Create(L"kgca08.bmp");
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

    for (auto data : m_ObjList)
    {
        data->Frame();
    }
}
void   Sample::Render() 
{    
   
    for (auto data : m_ObjList)
    {
        data->Render();
    }
}
void   Sample::Release() 
{
    for (auto data : m_ObjList)
    {
        data->Release();
    }
    
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