#include "TSceneGameIn.h"
#include "TGameCore.h"
#include "TGame.h"

UINT TSceneGameIn::m_iGameStage = 1;
TSceneGameIn::TSceneGameIn(TGame* p) {
    m_pOwner = p;
}
TSceneGameIn::~TSceneGameIn() {}

void    TSceneGameIn::Reset()
{
    m_iKillCounter = 10;
}
void TSceneGameIn::ProcessAction(TObject* pObj)
{
    if (m_bNextScene == true)
    {
        m_pOwner->m_pAction->Release();
        m_pOwner->SetTransition(TSceneEvent::EVENT_NEXT_SCENE);
        m_bNextScene = false;
        m_bPrevScene = false;
        return;
    }
    if (m_bPrevScene == true)
    {
        m_pOwner->m_pAction->Release();
        m_pOwner->SetTransition(TSceneEvent::EVENT_PREV_SCENE);
        m_bPrevScene = false;
        m_bNextScene = false;
        return;
    }
}
bool TSceneGameIn::CreateSound()
{
    TSoundManager& mgr = TSoundManager::GetInstance();
    m_pSound = mgr.Load(L"../../data/sound/abel_leaf.asf");
    m_pSoundEffect = mgr.Load(L"../../data/sound/GunShot.mp3");
    m_pSound->Play();
    return true;
}
TVector2 TSceneGameIn::GetWorldMousePos()
{
    TVector2 vPos = { (float)g_ptMouse.x,(float)g_ptMouse.y };
    vPos.x += m_vCamera.x - g_ptClientSize.x * 0.5f;
    vPos.y += m_vCamera.y - g_ptClientSize.y * 0.5f;
    return vPos;
}
bool TSceneGameIn::GameDataLoad(W_STR filename)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, filename.c_str(), _T("rt"));
    if (fp_src == NULL) return false;

    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer, _T("%s%d"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
    //m_rtSpriteList.resize(iNumSprite);

    for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
    {
        int iNumFrame = 0;
        int iType = 0;
        float fLife = 0.0f;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d %d %f"), pTemp,
            (unsigned int)_countof(pTemp), &iNumFrame, &iType, &fLife);
        
        
        if (iType == 0)
        {
            RECT_ARRAY rtArray;
            rtArray.resize(iNumFrame);

            RECT rt;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                    &rt.left, &rt.top, &rt.right, &rt.bottom);
                rtArray[iFrame] = rt;
            }
            m_rtSpriteList.emplace_back(rtArray);
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
                strVector.emplace_back(I_Tex.SplitPath(pTexFileName));
            }
            m_szSpriteList.emplace_back(strVector);
        }
    }
    fclose(fp_src);
    return true;
}
bool TSceneGameIn::CreateMap()
{
    TRect rt;
    rt.SetP(-1000.0f, -1000.0f, +1000.0f, +1000.0f);
    m_pMap = std::make_shared<TMapObj>(rt, 50, 50);
    if (m_pMap->Create(m_pWorld.get()))
    {
        TTexture* pTex = I_Tex.Load(L"../../data/texture/gg.bmp");
        m_pMap->SetTexture(pTex).
            SetShader().
            SetLayout();
    }
    return true;
}
bool TSceneGameIn::CreateHero()
{
    m_pHero = std::make_shared<THeroObj>();
    m_pHero->SetMap(m_pMap.get());
    TVector2 vStart = { 0.0f - 21.0f, 0.0f - 30.0f };
    TVector2 tEnd = { vStart.x + 42.0f, vStart.y + 60.0f };
    TLoadResData resData;
    //resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    //resData.texShaderName = L"../../data/shader/Default.txt";
    resData.texPathName = L"../../data/texture/bitmap1.bmp";
    resData.texShaderName = L"../../data/shader/BlendMask.txt";
    m_pHero->m_pMeshRender = &TGameCore::m_MeshRender;
    m_pHero->m_pWorld = m_pWorld.get();
    if (m_pHero->Create(m_pWorld.get(), resData, vStart, tEnd))
    {
        m_pHero->m_iCollisionType = TCollisionType::T_Overlap;
    }
    return true;
}
bool TSceneGameIn::CreateNPC()
{
    TNpcObj::CreateActionFSM();
    // npc
    TRect rtWorldMap = m_pMap->m_rtScreen;
    m_iKillCounter = m_iGameStage+=10;
    for (int iNpc = 0; iNpc < m_iKillCounter; iNpc++)
    {
        auto npcobj = std::make_shared<TNpcObj>();
        npcobj->m_pMeshRender = &TGameCore::m_MeshRender;
        npcobj->SetMap(m_pMap.get());
        npcobj->SetFSM(&m_fsm);
        TVector2 vStart(
            rtWorldMap.v1.x + (rand() % (UINT)(rtWorldMap.vs.x - 100.0f)),
            rtWorldMap.v1.y + (rand() % (UINT)(rtWorldMap.vs.y - 100.0f)));
        TVector2 tEnd(vStart.x + 72.0f, vStart.y + 79.0f);
        TLoadResData resData;
        resData.texPathName = L"../../data/texture/bitmap1.bmp";
        resData.texShaderName = L"../../data/shader/BlendMask.txt";

        if (npcobj->Create(m_pWorld.get(), resData, vStart, tEnd))
        {
            npcobj->m_fSpeed = 50.0f + (rand() % 200);
            npcobj->m_iCollisionType = TCollisionType::T_Overlap;
            //npcobj->SetScale(30.0f, 30.0f );
            //npcobj->SetRotation(T_Pi);
            m_NpcList.emplace_back(npcobj);
        }
    }
    return true;
}
bool TSceneGameIn::CreateUI()
{
    TButtonGUI::CreateActionFSM();

    for (int iNum = 0; iNum < 10; iNum++)
    {
        std::wstring filename = L"../../data/ui/";
        filename += std::to_wstring(iNum);
        filename += L".png";
        m_pNumber.push_back(I_Tex.Load(filename));
    }


    TLoadResData resData;
    resData.texPathName = L"../../data/ui/main_start_nor.png";
    resData.texShaderName = L"../../data/shader/Default.txt";

    auto ui1 = std::make_shared<TPrevBtn>();
    ui1->m_pMeshRender = &TGameCore::m_MeshRender;
    ui1->SetFSM(&m_GuiFSM);
    TVector2 vStart1 = { 0.0f, 0.0f };
    TVector2 vEnd1 = { 100.0f, 100.0f };
    if (ui1->Create(m_pWorld.get(), resData, vStart1, vEnd1))
    {
        ui1->m_iCollisionType = TCollisionType::T_Overlap;
        //ui1->SetScale(100.0f, 50.0f);
        //ui1->SetRotation(T_Pi * 0.25f);
        m_UiList.emplace_back(ui1);        
    }

    //auto ui2 = std::make_shared<TNextBtn>();
    //ui2->m_pMeshRender = &TGameCore::m_MeshRender;
    //ui2->SetFSM(&m_GuiFSM);
    //TVector2 vStart2 = { 700.0f, 0.0f };
    //TVector2 vEnd2 = { 800.0f, 100.0f };
    //if (ui2->Create(m_pWorld.get(), resData, vStart2, vEnd2))
    //{
    //    ui2->m_iCollisionType = TCollisionType::T_Overlap;
    //    //ui2->SetScale(50.0f, 100.0f);
    //    //ui2->SetRotation(T_Pi * -0.25f);
    //    m_UiList.emplace_back(ui2);
    //}

    resData.texPathName = L"../../data/ui/0.png";
    resData.texShaderName = L"../../data/shader/Default.txt";
    m_pNum10 = std::make_shared<TImageGUI>();
    m_pNum10->m_pMeshRender = &TGameCore::m_MeshRender;
    //m_pNum10->SetFSM(&m_GuiFSM);
    if (m_pNum10->Create(m_pWorld.get(), resData, { 360.0f, 0.0f }, { 400.0f, 40.0f }))
    {
        m_pNum10->m_iCollisionType = TCollisionType::T_Overlap;
    }
    m_pNum01 = std::make_shared<TImageGUI>();
    m_pNum01->m_pMeshRender = &TGameCore::m_MeshRender;
    //m_pNum01->SetFSM(&m_GuiFSM);
    if (m_pNum01->Create(m_pWorld.get(), resData, { 400.0f, 0.0f }, { 440.0f, 40.0f }))
    {
        m_pNum01->m_iCollisionType = TCollisionType::T_Overlap;
    }
    return true;
}
bool TSceneGameIn::CreateEffect()
{
    auto pObject3 = std::make_shared<TEffectObj>();
    TVector2 vStart = { 400.0f - 150, 100.0f - 150.0f };
    TVector2 tEnd = { vStart.x + 300, vStart.y + 300.0f };
    AddEffect(vStart, tEnd);
    return true;
}
void   TSceneGameIn::AddEffect(TVector2 vStart, TVector2 tEnd)
{
    srand(time(NULL));
    auto pObject3 = std::make_shared<TEffectObj>();
    pObject3->m_pMeshRender = &TGameCore::m_MeshRender;
    pObject3->m_vVertexList = pObject3->m_pMeshRender->m_vVertexList;
    TLoadResData resData;
    resData.texPathName = L"../../data/texture/bitmap1Alpha.bmp";
    resData.texShaderName = L"../../data/shader/Default.txt";
    TEffectData data;
    data.m_bLoop = true;
    data.m_fLifeTime = 1.0f;
    data.m_fOffsetTime = 0.01f;
    UINT iSprite = rand() % m_rtSpriteList.size();
    data.m_iType =  rand() % 2;
    if (data.m_iType == 0)
    {
        data.m_iNumAnimFrame = m_rtSpriteList[iSprite].size();
        data.m_rtList = m_rtSpriteList[iSprite];
    }
    if (data.m_iType == 1)
    {
        resData.texShaderName = L"../../data/shader/DefaultBlack.txt";
        data.m_iNumAnimFrame = m_szSpriteList[0].size();
        data.m_szList = m_szSpriteList[0];
    }
    pObject3->SetData(data);
    if (pObject3->Create(m_pWorld.get(), resData, vStart, tEnd))
    {
        pObject3->m_pCurrentTexture = pObject3->m_pTexture;
        m_EffectList.emplace_back(pObject3);
    }
}


void   TSceneGameIn::Init()
{
    // STATE_STAND -> EVENT_PATROL (시간경과)    -> STATE_MOVE
// STATE_STAND -> EVENT_FINDTARGET(검색범위) -> STATE_ATTACK
// STATE_MOVE  -> EVENT_STOP		->STATE_STAND
// STATE_MOVE  -> EVENT_LOSTTARGET  ->STATE_STAND
// STATE_MOVE  -> EVENT_FINDTARGET  ->STATE_ATTACK
// STATE_ATTACK -> EVENT_LOSTTARGET ->STATE_STAND 
// STATE_ATTACK -> EVENT_STOP       ->STATE_STAND 
    m_fsm.AddStateTransition(STATE_STAND, EVENT_PATROL, STATE_MOVE);
    m_fsm.AddStateTransition(STATE_STAND, EVENT_FINDTARGET, STATE_ATTACK);
    m_fsm.AddStateTransition(STATE_MOVE, EVENT_STOP, STATE_STAND);
    m_fsm.AddStateTransition(STATE_MOVE, EVENT_LOSTTARGET, STATE_STAND);
    m_fsm.AddStateTransition(STATE_MOVE, EVENT_FINDTARGET, STATE_ATTACK);
    m_fsm.AddStateTransition(STATE_ATTACK, EVENT_STOP, STATE_STAND);
    m_fsm.AddStateTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_STAND);

    m_GuiFSM.AddStateTransition(T_DEFAULT, EVENT_SELECT, T_HOVER);
    m_GuiFSM.AddStateTransition(T_HOVER, EVENT_DEFAULT, T_DEFAULT);
    m_GuiFSM.AddStateTransition(T_HOVER, EVENT_SELECT, T_SELECTED);
    m_GuiFSM.AddStateTransition(T_SELECTED, EVENT_DEFAULT, T_DEFAULT);

    CreateSound();
    m_pBitmap1Mask = I_Tex.Load(L"../../data/texture/bitmap2.bmp");
    GameDataLoad(L"SpriteData.txt");

    m_pWorld = std::make_shared<TWorld>(this);
    CreateMap();
    CreateHero();
    CreateNPC();
    CreateUI();
    //CreateEffect();    
}
void   TSceneGameIn::Frame()
{
    m_pMap->Frame();
    m_pHero->Frame();

    m_vCamera.x = m_pHero->m_vPos.x;
    m_vCamera.y = m_pHero->m_vPos.y;

    for (auto data : m_NpcList)
    {
        if (!data->m_bDead)
        {
            data->FrameState(m_pHero.get());
            data->Frame();
        }
    }
    //// collision
    TVector2 vMouse = GetWorldMousePos();
    //TSphere s;
    //s.vCenter = vMouse;
    //s.fRadius = 100.0f;
    //for (UINT iNpc1 = 0; iNpc1 < m_NpcList.size(); iNpc1++)
    //{
    //    if (m_NpcList[iNpc1]->m_bDead) continue;
    //    // m_Sphere by vMouse 
    //    if (g_GameKey.dwLeftClick == KEY_PUSH)
    //    {
    //        if (TCollision::CheckSphereToPoint(
    //            m_NpcList[iNpc1]->m_Sphere, vMouse))
    //        {
    //            m_NpcList[iNpc1]->m_bDead = true;
    //        }
    //    }
    //    // m_Sphere by m_Sphere 
    //    /*if (TCollision::CheckSphereToSphere(
    //        m_NpcList[iNpc1]->m_Sphere,
    //        m_pHero->m_Sphere))
    //    {
    //        m_NpcList[iNpc1]->m_bDead = true;
    //    }*/

    //    for (UINT iNpc2 = 0; iNpc2 < m_NpcList.size(); iNpc2++)
    //    {
    //        if (iNpc1 == iNpc2) continue;
    //        if (m_NpcList[iNpc2]->m_bDead) continue;
    //        // m_rtScreen by m_rtScreen 
    //        if (TCollision::CheckRectToRect(
    //            m_NpcList[iNpc1]->m_rtScreen,
    //            m_NpcList[iNpc2]->m_rtScreen))
    //        {                
    //            //m_NpcList[iNpc1]->m_bDead = true;
    //        }
    //    }
    //}
    for (auto iter = m_pHero->m_pProjectile->m_datalist.begin();
        iter != m_pHero->m_pProjectile->m_datalist.end(); iter++)
    {
        for (UINT iNpc2 = 0; iNpc2 < m_NpcList.size(); iNpc2++)
        {
            if (m_NpcList[iNpc2]->m_bDead) continue;
            // m_rtScreen by m_rtScreen 
            if (TCollision::CheckRectToRect(
                (*iter)->m_rtScreen,
                m_NpcList[iNpc2]->m_rtScreen))
            {
                m_NpcList[iNpc2]->m_bDead = true;
                m_iKillCounter--;
            }
        }
    }
    if (g_GameKey.dwMiddleClick == KEY_HOLD)
    {
        TVector2 v1 = vMouse;
        v1.x = vMouse.x - 20.0f;
        v1.y = vMouse.y - 20.0f;
        TVector2 tEnd = { vMouse.x + 20.0f, vMouse.y + 20.0f };
        AddEffect(v1, tEnd);

    }
    if (g_GameKey.dwRightClick == KEY_PUSH)
    {
        for (int iCell = 0; iCell < m_pMap->m_Cells.size(); iCell++)
        {
            // TRect by vMouse 
            if (TCollision::CheckRectToPoint(m_pMap->m_Cells[iCell].rt, vMouse))
            {
                m_pMap->m_Cells[iCell].iTexID++;
                if (m_pMap->m_Cells[iCell].iTexID > 3)
                {
                    m_pMap->m_Cells[iCell].iTexID = 0;
                }
            }
        }
    }

    for (auto iter = std::begin(m_EffectList); iter != m_EffectList.end();)
    {
        TEffectObj* pObj = (TEffectObj*)iter->get();
        if (pObj->m_bDead == false)
        {
            pObj->Frame();
            iter++;
        }
        else
        {
            m_pWorld->DeleteCollisionExecute(pObj);
            pObj->Release();
            iter = m_EffectList.erase(iter);
        }
    }

    for (UINT iNpc1 = 0; iNpc1 < m_NpcList.size(); iNpc1++)
    {
        if (m_NpcList[iNpc1]->m_bDead)
        {
            m_pWorld->DeleteCollisionExecute(m_NpcList[iNpc1].get());
        };
    }

    for (auto data : m_UiList)
    {
        if (!data->m_bDead)
        {
            data->FrameState(m_pHero.get());
            data->Frame();
        }
    }

    m_pWorld->Frame();
}
void   TSceneGameIn::Render()
{
    TSoundManager::GetInstance().Render();
    m_pMap->Transform(m_vCamera);
    m_pMap->Render(); 

    TDevice::m_pd3dContext->PSSetSamplers(0, 1, TDxState::m_pPointSS.GetAddressOf());
    TDevice::m_pd3dContext->PSSetShaderResources(1, 1, &m_pBitmap1Mask->m_pTexSRV);

    for (auto data : m_NpcList)
    {
        if (data->m_bDead) continue;
        data->Transform(m_vCamera);
        data->Render();
    }

    m_pHero->Transform(m_vCamera);
    m_pHero->Render();

   /* TDevice::m_pd3dContext->PSSetSamplers(0, 1, TDxState::m_pLinearSS.GetAddressOf());
    TDevice::m_pd3dContext->PSSetShaderResources(1, 1, &m_pBitmap1Mask->m_pTexSRV);*/

    for (auto data : m_EffectList)
    {
        data->Transform(m_vCamera);
        data->Render();
    }

    for (auto data : m_UiList)
    {
        if (!data->m_bDead)
        {
            data->Transform(m_vCamera);
            data->Render();
        }
    }
    UINT num10 = m_iKillCounter / 10;
    UINT num01 = m_iKillCounter % 10;
    m_pNum10->m_pTexture = m_pNumber[num10];
    m_pNum01->m_pTexture = m_pNumber[num01];
    m_pNum10->Transform(m_vCamera);
    m_pNum10->Render();
    m_pNum01->Transform(m_vCamera);
    m_pNum01->Render();
    if (m_iKillCounter == 0)
    {
        m_bNextScene = true;
    }
}
void   TSceneGameIn::Release()
{
    for (auto data : m_NpcList)
    {
        data->Release();
    }
    for (auto data : m_EffectList)
    {
        data->Release();
    }
    for (auto data : m_UiList)
    {
        data->Release();
    }
    m_pHero->Release();
    m_pMap->Release();
}



