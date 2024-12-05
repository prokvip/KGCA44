#include "Sample.h"

void   Sample::Init() 
{       
    tObject pObject1 = std::make_shared<TObject2D>();
    pObject1->Create(L"kgca08.bmp");
    m_ObjList.emplace_back(pObject1);

    tObject pObject2 = std::make_shared<TObject2D>();
    TVertex2 tStart = { 400.0f, 300.0f };
    TVertex2 tEnd   = { 800.0f, 600.0f };
    pObject2->Create(L"kgcalogo.bmp", tStart, tEnd);
    m_ObjList.emplace_back(pObject2);
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