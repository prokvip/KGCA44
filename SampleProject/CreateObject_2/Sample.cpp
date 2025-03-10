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
        int iType = 0;
        float fLife = 0.0f;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d %d %f"), pTemp,
            (unsigned int)_countof(pTemp), &iNumFrame, &iType, &fLife);
        //m_rtSpriteList[iCnt].resize(iNumFrame);

        if (iType == 0)
        {
            RECT rt;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                    &rt.left, &rt.top, &rt.right, &rt.bottom);
                m_rtSpriteList[iCnt].push_back(rt);
            }
        }
        if (iType == 1)
        {
            TCHAR pTexFileName[256] = { 0 };    
            T_STR_VECTOR strVector;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%s %s"),
                    pTemp, (unsigned int)_countof(pTemp),
                    pTexFileName, (unsigned int)_countof(pTexFileName));
                
                I_Tex.Load(pTexFileName);
                strVector.push_back(I_Tex.SplitPath(pTexFileName));              
            }
            m_szSpriteList.push_back(strVector);
        }
    }
    fclose(fp_src);
    return true;
}
void   Sample::Init()
{
    m_pBitmap1Mask = I_Tex.Load(L"../../data/texture/bitmap2.bmp");
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
    //resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    //resData.texShaderName = L"../../data/shader/Default.txt";
    resData.texPathName = L"../../data/texture/bitmap1.bmp";
    resData.texShaderName = L"../../data/shader/BlendMask.txt";
    if (pObject2->Create(resData, tStart, tEnd))
    {
        m_ObjList.emplace_back(pObject2);
    }

    auto pObject3 = std::make_shared<TEffectObj>();
    tStart.x = 400.0f;
    tStart.y = 100.0f;
    TVertex2 tEnd2 = { tStart.x + 42.0f, tStart.y + 60.0f };
    AddEffect(tStart, tEnd2);
}
void   Sample::AddEffect(TVertex2 tStart, TVertex2 tEnd)
{
    auto pObject3 = std::make_shared<TEffectObj>();
    TLoadResData resData;
    resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    resData.texShaderName = L"../../data/shader/DefaultMask.txt";
    TEffectData data;
    data.m_bLoop = true;
    data.m_fLifeTime = 1.0f;
    data.m_fOffsetTime = 0.1f;
    UINT iSprite = rand() % 3;
    data.m_iType = 1;// rand() % m_szSpriteList[0].size();
    if (data.m_iType == 0)
    {
        data.m_iNumAnimFrame = m_rtSpriteList[iSprite].size();
        data.m_rtList = m_rtSpriteList[iSprite];
    }
    if (data.m_iType == 1)
    {
        data.m_iNumAnimFrame = m_szSpriteList[0].size();
        data.m_szList = m_szSpriteList[0];
    }
    pObject3->SetData(data);
    if (pObject3->Create(resData, tStart, tEnd))
    {
        m_EffectList.emplace_back(pObject3);
    }
}
void   Sample::AddEffectSingle(TVertex2 tStart, TVertex2 tEnd)
{
    auto pObject3 = std::make_shared<TEffectObj>();
    TLoadResData resData;
    resData.texPathName = L"../../data/effect/5heng01_blue.dds";
    resData.texShaderName = L"../../data/shader/DefaultBlack.txt";
    TEffectData data;
    data.m_bLoop = true;
    data.m_fLifeTime = 1.0f;
    data.m_fOffsetTime = 1.0f;
    data.m_iType = 2;
    data.m_iNumAnimFrame = 1;        
    pObject3->SetData(data);
    if (pObject3->Create(resData, tStart, tEnd))
    {
        m_EffectList.emplace_back(pObject3);
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

    if (g_GameKey.dwMiddleClick == KEY_PUSH)
    {
        TVertex2 tStart = { m_Input.m_ptMouse.x, m_Input.m_ptMouse.y };
        TVertex2 tEnd = { tStart.x + 100.0f, tStart.y + 100.0f };
        AddEffect(tStart, tEnd);
        /*UINT iType = rand() / 3;
        if(iType ==0 )
            AddEffectSingle(tStart, tEnd, std::shared_ptr<TE1>());
        if (iType == 1)
            AddEffectSingle(tStart, tEnd, std::shared_ptr<TE2>());
        if (iType == 2)
            AddEffectSingle(tStart, tEnd, std::shared_ptr<TE3>());*/
    }

    for (auto iter = std::begin(m_EffectList);
           iter != m_EffectList.end();)
    {
        TEffectObj* pObj = (TEffectObj*)iter->get();
        if (pObj->m_bDead == false)
        {
            pObj->Frame();
            iter++;
        }
        else
        {
            pObj->Release();
            iter = m_EffectList.erase(iter);
        }
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
    //TDevice::m_pd3dContext->PSSetSamplers(0, 1, &TDxState::m_pPointSS);

    TDevice::m_pd3dContext->PSSetShaderResources(
        1, 1, &m_pBitmap1Mask->m_pTexSRV);
    m_ObjList[1]->Render();    

    for (auto data : m_EffectList)
    {
        data->Render();
    }

    D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
    m_DxWrite.DirectDraw(rt, L"Sample::Render");
}
void   Sample::Release() 
{
    for (auto data : m_ObjList)
    {
        data->Release();
    }
    for (auto data : m_EffectList)
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