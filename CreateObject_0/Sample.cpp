#include "Sample.h"

void   Sample::Init() 
{   
    m_Sound.Init();
    m_Sound.Load(L"abel_leaf.asf");
    m_SoundEffect.Init();
    m_SoundEffect.Load(L"GunShot.mp3");
    m_Sound.Play();
    

    tObject pObject1 = std::make_shared<TMap>();
    pObject1->Create(L"kgca08.bmp");
    m_ObjList.emplace_back(pObject1);

    tObject pObject2 = std::make_shared<THero>();
    TVertex2 tStart = { 400.0f, 300.0f };
    TVertex2 tEnd   = { 800.0f, 600.0f };
    pObject2->Create(L"kgcalogo.bmp", tStart, tEnd);
    m_ObjList.emplace_back(pObject2);
}
void   Sample::Frame()  
{
    m_Sound.Frame();
    if (g_GameKey.dwWkey == KEY_PUSH)
    {
        m_SoundEffect.PlayEffect();
    }
    if (g_GameKey.dwSkey == KEY_PUSH)
    {
        m_SoundEffect.Stop();
    }
    if (g_GameKey.dwAkey == KEY_PUSH)
    {
        m_Sound.Paused();
    }
    if (g_GameKey.dwLeftClick == KEY_HOLD)
    {
        m_Sound.VolumeUp(g_fSPF*0.33f);
    }
    if (g_GameKey.dwRightClick == KEY_HOLD)
    {
        m_Sound.VolumeDown(g_fSPF * 0.33f);
    }

    for (auto data : m_ObjList)
    {
        data->Frame();
    }

    static float fTime = 0.0f;
    fTime += g_fSPF;
    if (fTime > 1.0f)
    {
        m_DxWrite.Add(m_Sound.m_csBuffer);
        fTime = 0.0f;
    }
}
void   Sample::Render() 
{       
    m_Sound.Render();   
    for (auto data : m_ObjList)
    {
        data->Render();
    }

    D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
    m_DxWrite.DirectDraw(rt, L"Sample::Render");
}
void   Sample::Release() 
{
    m_Sound.Release();
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