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
bool Sample::CreateMap()
{
    TRect rt;
    rt.SetS(0.0f, 0.0f, 800.0f, 600.0f);
    m_pMap = std::make_shared<TMapObj>(rt, 10, 10);
    if (m_pMap->Create())
    {
        TTexture* pTex = I_Tex.Load(L"../../data/texture/gg.bmp");
        m_pMap->SetTexture(pTex).
            SetShader().
            SetLayout();
    }
    return true;
}
bool Sample::CreateHero()
{
    //TVector2 vMapCenter = m_pMap->m_srtScreen.tCenter;
    m_pHero = std::make_shared<THeroObj>();
    //m_pHero->SetMap(m_pMap.get());
    TVector2 tStart = { 400.0f, 300.0f };
    TVector2 tEnd = { tStart.x + 42.0f, tStart.y + 60.0f };
    TLoadResData resData;
    //resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    //resData.texShaderName = L"../../data/shader/Default.txt";
    resData.texPathName = L"../../data/texture/bitmap1.bmp";
    resData.texShaderName = L"../../data/shader/BlendMask.txt";
    m_pHero->m_pMeshRender = &TGameCore::m_MeshRender;
    if (m_pHero->Create(resData, tStart, tEnd))
    {
    }
    return true;
}
bool Sample::CreateNPC()
{
    // npc
    TRect rtWorldMap = m_pMap->m_srtScreen;
    for (int iNpc = 0; iNpc < 200; iNpc++)
    {
        auto npcobj = std::make_shared<TNpcObj>();
        npcobj->m_pMeshRender = &TGameCore::m_MeshRender;
        npcobj->SetMap(m_pMap.get());
        TVector2 tStart(100.0f + (rand() % (UINT)(rtWorldMap.w - 100.0f)),
            100.0f + (rand() % (UINT)(rtWorldMap.h - 100.0f)));
        TVector2 tEnd(tStart.x + 42.0f, tStart.y + 60.0f);
        TLoadResData resData;
        resData.texPathName = L"../../data/texture/bitmap1.bmp";
        resData.texShaderName = L"../../data/shader/BlendMask.txt";
        if (npcobj->Create(resData, tStart, tEnd))
        {
            m_NpcList.emplace_back(npcobj);
        }
    }
    return true;
}
bool Sample::CreateEffect()
{
    auto pObject3 = std::make_shared<TEffectObj>();
    //pObject3->SetMap(m_pMap.get());
    TVector2 tStart;
    tStart.x = 400.0f;
    tStart.y = 100.0f;
    TVector2 tEnd2 = { tStart.x + 42.0f, tStart.y + 60.0f };
    AddEffect(tStart, tEnd2);
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

    CreateMap();
    CreateHero();
    CreateNPC();
    CreateEffect();    
}
void   Sample::AddEffect(TVector2 tStart, TVector2 tEnd)
{
    auto pObject3 = std::make_shared<TEffectObj>();
    pObject3->m_pMeshRender = &TGameCore::m_MeshRender;
    pObject3->m_vVertexList = pObject3->m_pMeshRender->m_vVertexList;
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
void   Sample::AddEffectSingle(TVector2 tStart, TVector2 tEnd)
{
    auto pObject3 = std::make_shared<TEffectObj>();
    pObject3->m_pMeshRender = &TGameCore::m_MeshRender;

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
    m_pMap->Frame();
    m_pHero->Frame();

    m_vCamera.x = m_pHero->m_vPos.x;
    m_vCamera.y = m_pHero->m_vPos.y;

    for (auto data : m_NpcList)
    {
        if(!data->m_bDead)   data->Frame();
    }    
    // collision
    for (UINT iNpc1=0; iNpc1 <  m_NpcList.size(); iNpc1++)
    {       
        if (m_NpcList[iNpc1]->m_bDead) continue;
        //if (TCollision::CheckRectToRect(
        /*if (TCollision::CheckSphereToSphere(
            m_NpcList[iNpc1]->m_Sphere,
            m_pHero->m_Sphere))*/
        TSphere s;
        s.vCenter = { (float)m_Input.m_ptMouse.x,  (float)m_Input.m_ptMouse.y };
        s.fRadius = 100.0f;
        if (g_GameKey.dwLeftClick == KEY_PUSH)
        {
            if (TCollision::CheckSphereToPoint(
                s,
                m_NpcList[iNpc1]->m_Sphere.vCenter))
            {
                m_NpcList[iNpc1]->m_bDead = true;
            }
        }
        /*for (UINT iNpc2 = 0; iNpc2 < m_NpcList.size(); iNpc2++)
        {
            if (iNpc1 == iNpc2) continue;
            if (m_NpcList[iNpc2]->m_bDead) continue;
            if (TCollision::CheckRectToRect(
                m_NpcList[iNpc1]->m_srtScreen, 
                m_NpcList[iNpc2]->m_srtScreen ))
            {
                m_NpcList[iNpc1]->m_bDead = true;
            }
        }*/
    }

    if (g_GameKey.dwLeftClick == KEY_HOLD)
    {
        TVector2 tStart = { m_Input.m_ptMouse.x-50.0f, m_Input.m_ptMouse.y-50.0f };
        TVector2 tEnd = { tStart.x + 100.0f, tStart.y + 100.0f };
        AddEffect(tStart, tEnd);

        for (int iCell = 0; iCell < m_pMap->m_Cells.size(); iCell++)
        {
            if (TCollision::CheckRectToPoint(
                m_pMap->m_Cells[iCell].rt, m_Input.m_ptMouse))
            {
                m_pMap->m_Cells[iCell].iTexID = 2;
            }
        }
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
    m_pMap->Transform(m_vCamera);
    m_pMap->Render();

    TDevice::m_pd3dContext->PSSetSamplers(0, 1, TDxState::m_pPointSS.GetAddressOf());
    TDevice::m_pd3dContext->PSSetShaderResources(1, 1, &m_pBitmap1Mask->m_pTexSRV);
    m_pHero->Transform(m_vCamera);
    m_pHero->Render();
 
    for (auto data : m_NpcList)
    {
        if (data->m_bDead) continue;
        data->Transform(m_vCamera);
        data->Render();
    }
        
    for (auto data : m_EffectList)
    {
        data->Transform(m_vCamera);
        data->Render();
    }
    D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
    m_DxWrite.DirectDraw(rt, L"Sample::Render");
}
void   Sample::Release() 
{
    for (auto data : m_NpcList)
    {
        data->Release();
    }
    for (auto data : m_EffectList)
    {
        data->Release();
    }

    m_pHero->Release();
    m_pMap->Release();
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
    sample.SetWindow(L"test", 800, 600);
    sample.GameRun();    
}