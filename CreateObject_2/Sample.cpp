#include "Sample.h"
bool Sample::GameDataLoad(W_STR filename)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, filename.c_str(), _T("rt"));
    if (fp_src == NULL) return false;

    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
    m_rtSpriteList.resize(iNumSprite);

    for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
    {
        int iNumFrame = 0;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
        //m_rtSpriteList[iCnt].resize(iNumFrame);

        RECT rt;
        for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                &rt.left, &rt.top, &rt.right, &rt.bottom);
            m_rtSpriteList[iCnt].push_back(rt);
        }
    }
    fclose(fp_src);
    return true;
}
void   Sample::Init()
{
    GameDataLoad(L"SpriteData.txt");
    TSoundManager& mgr = TSoundManager::GetInstance();
    m_pSound = mgr.Load(L"../../data/sound/abel_leaf.asf");
    m_pSoundEffect = mgr.Load(L"../../data/sound/GunShot.mp3");
    m_pSound->Play();

    tObject pObject1 = std::make_shared<TMapObj>();
    if (pObject1->Create())
    {
        TTexture* pTex = I_Tex.Load(L"../../data/texture/Board.png");
        pObject1->SetTexture(pTex).
            SetShader().
            SetLayout();
        m_ObjList.emplace_back(pObject1);
    }

    tObject pObject2 = std::make_shared<THeroObj>();
    TVertex2 tStart = { 400.0f, 300.0f };
    TVertex2 tEnd = { tStart.x + 42.0f, tStart.y + 60.0f };
    TLoadResData resData;
    resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    resData.texShaderName = L"../../data/shader/Default.txt";
    if (pObject2->Create(resData, tStart, tEnd))
    {
        m_ObjList.emplace_back(pObject2);
    }

    tObject pObject3 = std::make_shared<TEffectObj>();
    tStart.x = 400.0f;
    tStart.y = 100.0f;
    TVertex2 tEnd2 = { tStart.x + 42.0f, tStart.y + 60.0f };
    resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    resData.texShaderName = L"../../data/shader/Default.txt";
    ((TEffectObj*)pObject3.get())->m_rtList = m_rtSpriteList[2];
    if (pObject3->Create(resData, tStart, tEnd2))
    {        
        m_ObjList.emplace_back(pObject3);
    }
}
void   Sample::Frame()  
{
    TSoundManager::GetInstance().Frame();
    if (m_pSoundEffect && m_pSound)
    {
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
            m_pSound->VolumeUp(g_fSPF * 0.33f);
        }
        if (g_GameKey.dwRightClick == KEY_HOLD)
        {
            m_pSound->VolumeDown(g_fSPF * 0.33f);
        }
        static float fTime = 0.0f;
        fTime += g_fSPF;
        if (fTime > 1.0f)
        {
            m_DxWrite.Add(m_pSound->m_csBuffer);
            fTime = 0.0f;
        }
    }

    for (auto data : m_ObjList)
    {
        data->Frame();
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
    m_ObjList[2]->Render();

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