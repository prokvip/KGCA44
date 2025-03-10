#include "Sample.h"

void   Sample::Init() 
{   
    TSoundManager& mgr = TSoundManager::GetInstance();
    m_pSound = mgr.Load(L"abel_leaf.asf");
    m_pSoundEffect = mgr.Load(L"GunShot.mp3");
    m_pSound->Play();

    tObject pObject1 = std::make_shared<TMap>();
    pObject1->Create(L"Board.png");
    m_ObjList.emplace_back(pObject1);

    tObject pObject2 = std::make_shared<THero>();
    TVertex2 tStart = { 400.0f, 300.0f };
    TVertex2 tEnd   = { tStart.x+42.0f, tStart.y+60.0f };
    pObject2->Create(L"bitmap1Alpha.bmp", tStart, tEnd);
    m_ObjList.emplace_back(pObject2);
}
void   Sample::Frame()  
{
    TSoundManager::GetInstance().Frame();
    if (g_GameKey.dwWkey == KEY_PUSH)
    {
        m_pSoundEffect->PlayEffect();
    }
    if (g_GameKey.dwSkey == KEY_PUSH)
    {
        m_pSoundEffect->Stop();
    }
    if (g_GameKey.dwAkey == KEY_PUSH)
    {
        m_pSound->Paused();
    }
    if (g_GameKey.dwLeftClick == KEY_HOLD)
    {
        m_pSound->VolumeUp(g_fSPF*0.33f);
    }
    if (g_GameKey.dwRightClick == KEY_HOLD)
    {
        m_pSound->VolumeDown(g_fSPF * 0.33f);
    }

    for (auto data : m_ObjList)
    {
        data->Frame();
    }

    static float fTime = 0.0f;
    fTime += g_fSPF;
    if (fTime > 1.0f)
    {
        m_DxWrite.Add(m_pSound->m_csBuffer);
        fTime = 0.0f;
    }
}
void   Sample::Render() 
{       
    TSoundManager::GetInstance().Render();

    /*for (auto data : m_ObjList)
    {
        data->Render();
    }*/
    m_ObjList[0]->Render();
    TDevice::m_pd3dContext->PSSetSamplers(0, 1, &TDxState::m_pPointSS);
    m_ObjList[1]->Render();

    D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
    m_DxWrite.DirectDraw(rt, L"Sample::Render");
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