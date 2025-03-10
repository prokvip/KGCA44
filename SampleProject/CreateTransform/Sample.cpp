#include "Sample.h"
TVector2 Sample::GetWorldMousePos()
{
    TVector2 vPos = { (float)m_Input.m_ptMouse.x,
                          (float)m_Input.m_ptMouse.y };
    vPos.x += m_vCamera.x - g_ptClientSize.x * 0.5f;
    vPos.y += m_vCamera.y - g_ptClientSize.y * 0.5f;
    return vPos;
}
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
    rt.SetP(-1000.0f, -1000.0f, +1000.0f, +1000.0f);
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
    m_pHero = std::make_shared<THeroObj>();
    m_pHero->SetMap(m_pMap.get());
    TVector2 vStart = { 0.0f-21.0f, 0.0f-30.0f };
    TVector2 tEnd = { vStart.x + 42.0f, vStart.y + 60.0f };
    TLoadResData resData;
    //resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    //resData.texShaderName = L"../../data/shader/Default.txt";
    resData.texPathName = L"../../data/texture/bitmap1.bmp";
    resData.texShaderName = L"../../data/shader/BlendMask.txt";
    m_pHero->m_pMeshRender = &TGameCore::m_MeshRender;
    if (m_pHero->Create(resData, vStart, tEnd))
    {
    }
    return true;
}
bool Sample::CreateNPC()
{
    // npc
    TRect rtWorldMap = m_pMap->m_rtScreen;
    for (int iNpc = 0; iNpc < 100; iNpc++)
    {
        auto npcobj = std::make_shared<TNpcObj>();
        npcobj->m_pMeshRender = &TGameCore::m_MeshRender;
        npcobj->SetMap(m_pMap.get());
        TVector2 vStart(100.0f + (rand() % (UINT)(rtWorldMap.vs.x - 100.0f)),
            100.0f + (rand() % (UINT)(rtWorldMap.vs.y - 100.0f)));
        TVector2 tEnd(vStart.x + 72.0f, vStart.y + 79.0f);
        TLoadResData resData;
        resData.texPathName = L"../../data/texture/bitmap1.bmp";
        resData.texShaderName = L"../../data/shader/BlendMask.txt";
        
        if (npcobj->Create(resData, vStart, tEnd))
        {
            npcobj->SetScale(30.0f, 30.0f );
            npcobj->SetRotation(T_Pi);
            m_NpcList.emplace_back(npcobj);
        }
    }
    return true;
}
bool Sample::CreateEffect()
{
    auto pObject3 = std::make_shared<TEffectObj>();  
    TVector2 vStart = { 400.0f-150, 100.0f-150.0f };
    TVector2 tEnd = { vStart.x + 300, vStart.y + 300.0f };
    AddEffect(vStart, tEnd);
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
void   Sample::AddEffect(TVector2 vStart, TVector2 tEnd)
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
    data.m_fOffsetTime = 0.01f;
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
    if (pObject3->Create(resData, vStart, tEnd))
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
        if (!data->m_bDead)
        {
            data->SetScale(10.0f + ((cosf(g_fGT) * 0.5f + 0.5f ) * 30.0f),
                           10.0f + ((cosf(g_fGT) * 0.5f + 0.5f) * 30.0f));
            data->Frame();
        }
    }
    // collision
    TVector2 vMouse = GetWorldMousePos();
    TSphere s;
    s.vCenter = vMouse;
    s.fRadius = 100.0f;
    for (UINT iNpc1 = 0; iNpc1 < m_NpcList.size(); iNpc1++)
    {
        if (m_NpcList[iNpc1]->m_bDead) continue;
        // m_Sphere by vMouse 
        if (g_GameKey.dwLeftClick == KEY_PUSH)
        {
            if (TCollision::CheckSphereToPoint(
                m_NpcList[iNpc1]->m_Sphere, vMouse))
            {
                m_NpcList[iNpc1]->m_bDead = true;
            }
        }
        // m_Sphere by m_Sphere 
        if (TCollision::CheckSphereToSphere(
            m_NpcList[iNpc1]->m_Sphere,
            m_pHero->m_Sphere))
        {
            m_NpcList[iNpc1]->m_bDead = true;
        }

        for (UINT iNpc2 = 0; iNpc2 < m_NpcList.size(); iNpc2++)
        {
            if (iNpc1 == iNpc2) continue;
            if (m_NpcList[iNpc2]->m_bDead) continue;
            // m_rtScreen by m_rtScreen 
            if (TCollision::CheckRectToRect(
                m_NpcList[iNpc1]->m_rtScreen,
                m_NpcList[iNpc2]->m_rtScreen))
            {
                //m_NpcList[iNpc1]->m_bDead = true;
            }
        }
    }
    
    if (g_GameKey.dwLeftClick == KEY_HOLD)
    {        
        TVector2 v1 = vMouse;
        v1.x = vMouse.x - 100.0f;
        v1.y = vMouse.y - 100.0f;
        TVector2 tEnd = { v1.x + 200.0f,
                          v1.y + 200.0f };
        AddEffect(v1, tEnd);

    }
    if (g_GameKey.dwRightClick == KEY_PUSH)
    {       
        for (int iCell = 0; iCell < m_pMap->m_Cells.size(); iCell++)
        {
            // TRect by vMouse 
            if (TCollision::CheckRectToPoint(
                m_pMap->m_Cells[iCell].rt, vMouse))
            {
                m_pMap->m_Cells[iCell].iTexID++;
                if (m_pMap->m_Cells[iCell].iTexID > 3)
                {
                    m_pMap->m_Cells[iCell].iTexID = 0;
                }                
            }
        }
    }

    for (auto iter = std::begin(m_EffectList);  iter != m_EffectList.end();)
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