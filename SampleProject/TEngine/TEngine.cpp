#include "TEngine.h"
#include "TDxState.h"
TCamera* TEngine::g_pCamera = nullptr;
void   TEngine::SetCamera(TCamera* pCamera)
{
    if (pCamera == nullptr)
    {
        g_pCamera = m_pSceneCamera.get();
        return;
    }
    g_pCamera = pCamera;
}
void   TEngine::CoreInit()
{
    m_DxDevice.Init();
    m_GameTimer.Init();
    m_Input.Init();
    m_DxWrite.Init();
    // 3d(RT) : 2d(RT) ����
    IDXGISurface* pBackBuffer;
    HRESULT hr = m_DxDevice.m_pSwapChain->GetBuffer(
        0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);
    if (SUCCEEDED(m_DxWrite.Create(pBackBuffer)))
    {
        pBackBuffer->Release();
    }

    TDxState::Create();

    I_Shader.Init();
    if (I_Shader.g_pDefaultShader != nullptr)
    {
        I_InputLayout.Init(I_Shader.g_pDefaultShader->m_pCode.Get());
    }

    CreateDefaultShapes();
    auto pMaterial = std::make_shared<UMaterial>();
    pMaterial->Load(L"../../data/shader/sky.txt",
                    L"../../data/texture/kgca08.bmp");
    m_SkyObj = std::make_shared<TSkyObject>();
    m_SkyObj->Load(GetShape(L"box"));
    m_SkyObj->GetMesh()->SetMaterial(pMaterial);

    m_SMLine = std::make_shared<AActor>();
    m_SMLine->Init();
    m_SMLine->SetMesh(GetShape(L"line"));
    auto lineMaterial = std::make_shared<UMaterial>();
    lineMaterial->Load(L"../../data/shader/pnct.txt",L"../../data/texture/kgca08.bmp");
    m_SMLine->GetMesh()->SetMaterial(lineMaterial);

    m_pSceneCamera = std::make_shared<TCamera>();
    SetCamera(m_pSceneCamera.get());

    TVector3 vCameraPos = TVector3(0, 0, -10.0f);
    TVector3 vCameraTarget = TVector3(0, 0, 0.0f);
    TVector3 vCameraUp = TVector3(0, 1.0f, 0.0f);
    m_pSceneCamera->CreateViewMatrix(vCameraPos, vCameraTarget, vCameraUp);

    float fAspect = (float)g_ptClientSize.x / (float)g_ptClientSize.y;
    float fFovY = (float)T_Pi * 0.25f;
    float fNearZ = 1.0f;
    float fFarZ = 1000.0f;
    m_pSceneCamera->CreateProjMatrix(fFovY, fAspect, fNearZ, fFarZ);

    Init();
}
void   TEngine::CoreFrame() 
{       
    m_GameTimer.Frame();
    m_Input.Frame();
    m_DxWrite.Frame();
    m_DxDevice.Frame();
    m_SkyObj->Tick();

    if (m_Input.KeyCheck('V') == KEY_PUSH)
    {
        TDevice::m_bWireFrame = !TDevice::m_bWireFrame;
    }
    if (m_Input.KeyCheck('B') == KEY_PUSH)
    {
        TDevice::m_DepthEnable = !TDevice::m_DepthEnable;
    }
    if (g_pCamera == m_pSceneCamera.get())
    {       
        m_pSceneCamera->Tick();
    }
    Tick();
}
void   TEngine::CoreRender() 
{
    m_DxDevice.PreRender();    
    m_SkyObj->m_matOffset = TMatrix::Identity();
    m_SkyObj->m_vScale = { 100,100,100 };
    m_SkyObj->m_vRotation = { 0, 0, 0.0f };
    m_SkyObj->m_vPosition = { 0,0,0 };
   // m_SkyObj->UpdateVector();
    m_SkyObj->Render();
    
    m_DxDevice.SetDefaultState();

    {
        Render();        

        TDevice::m_pd3dContext->IASetPrimitiveTopology(
            D3D_PRIMITIVE_TOPOLOGY_LINELIST);
        m_SMLine->m_vScale = { 1000,1,1 };
        m_SMLine->UpdateVector();
        m_SMLine->Render();
        m_SMLine->m_vScale = { 1,1000,1 };
        m_SMLine->UpdateVector();
        m_SMLine->Render();
        m_SMLine->m_vScale = { 1,1,1000 };
        m_SMLine->UpdateVector();
        m_SMLine->Render();

        m_DxWrite.PreRender();
            {
                D2D1_RECT_F rt = { 0.0f, 0.0f, 800.0f, 600.0f };
                m_DxWrite.Draw(rt, m_GameTimer.m_szTime);
                rt.top += 25.0f;
                m_DxWrite.Draw(rt, m_Input.m_szTime, 
                                    D2D1::ColorF(1, 0, 0,1));
            
            }

            m_DxWrite.Render();
        m_DxWrite.PostRender();

        //m_Input.Render();
    }
    m_DxDevice.PostRender();

    if (g_GameKey.dwExit == KEY_PUSH)
    {
        m_bRun = false;
    }
    
}
void   TEngine::CoreRelease()
{
    for (auto shape : m_Shapes)
    {
        shape.second->Destroy();
    }
    m_SMLine->Destroy();
    m_SkyObj->Destroy();
    m_GameTimer.Release();
    m_DxDevice.Release();
    m_Input.Release();
    m_DxWrite.Release();
    TDxState::Release();

    Release();
}
void   TEngine::CoreReset()
{
    g_ptDeltaMouse.x = 0;
    g_ptDeltaMouse.y = 0;
    m_GameTimer.Reset();
    m_Input.Reset();
}
bool TEngine::GameRun()
{
    CoreInit();
   
    while (m_bRun)
    {            
        if (!MessageProcess() && m_bActive)
        {
            CoreFrame();
            CoreRender();
            g_nMouseWheelDelta = m_nMouseWheelDelta = 0;
        }
        if (m_bActive == false)
        {
            CoreReset();
        }
    }	
    CoreRelease();
	return true;
}

void TEngine::CreateBoxShapes()
{
    // box
    auto mesh = std::make_shared<UStaticMeshComponent>();
    TVector3 vMin = TVector3(-1, -1, -1.0f);
    TVector3 vMax = TVector3(+1, +1, 1.0f);
    mesh->m_vVertexList.resize(24);
    mesh->m_vIndexList.resize(36);

    mesh->m_vVertexList[0] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[1] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[2] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[3] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));
    // �޸�
    mesh->m_vVertexList[4] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[5] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[6] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[7] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

    // ������
    mesh->m_vVertexList[8] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[9] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[10] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[11] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

    // ����
    mesh->m_vVertexList[12] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[13] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[14] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[15] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

    // ����
    mesh->m_vVertexList[16] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[17] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[18] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[19] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

    // �Ʒ���
    mesh->m_vVertexList[20] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[21] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[22] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[23] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

    UINT iIndex = 0;
    mesh->m_vIndexList[iIndex++] = 0; 	mesh->m_vIndexList[iIndex++] = 1; 	mesh->m_vIndexList[iIndex++] = 2;
    mesh->m_vIndexList[iIndex++] = 0;	mesh->m_vIndexList[iIndex++] = 2; 	mesh->m_vIndexList[iIndex++] = 3;
    mesh->m_vIndexList[iIndex++] = 4; 	mesh->m_vIndexList[iIndex++] = 5; 	mesh->m_vIndexList[iIndex++] = 6;
    mesh->m_vIndexList[iIndex++] = 4;	mesh->m_vIndexList[iIndex++] = 6; 	mesh->m_vIndexList[iIndex++] = 7;
    mesh->m_vIndexList[iIndex++] = 8; 	mesh->m_vIndexList[iIndex++] = 9; 	mesh->m_vIndexList[iIndex++] = 10;
    mesh->m_vIndexList[iIndex++] = 8;	mesh->m_vIndexList[iIndex++] = 10;  mesh->m_vIndexList[iIndex++] = 11;
    mesh->m_vIndexList[iIndex++] = 12;  mesh->m_vIndexList[iIndex++] = 13;  mesh->m_vIndexList[iIndex++] = 14;
    mesh->m_vIndexList[iIndex++] = 12;	mesh->m_vIndexList[iIndex++] = 14;  mesh->m_vIndexList[iIndex++] = 15;
    mesh->m_vIndexList[iIndex++] = 16;  mesh->m_vIndexList[iIndex++] = 17;  mesh->m_vIndexList[iIndex++] = 18;
    mesh->m_vIndexList[iIndex++] = 16;	mesh->m_vIndexList[iIndex++] = 18;  mesh->m_vIndexList[iIndex++] = 19;
    mesh->m_vIndexList[iIndex++] = 20;  mesh->m_vIndexList[iIndex++] = 21;  mesh->m_vIndexList[iIndex++] = 22;
    mesh->m_vIndexList[iIndex++] = 20;	mesh->m_vIndexList[iIndex++] = 22;  mesh->m_vIndexList[iIndex++] = 23;

    mesh->CreateVertexBuffer();
    mesh->CreateIndexBuffer();

    m_Shapes.insert(std::make_pair(L"box", mesh));
}
void TEngine::CreatePlaneShapes()
{
    // box
    auto mesh = std::make_shared<UStaticMeshComponent>();
    mesh->m_vVertexList.resize(4);
    mesh->m_vIndexList.resize(6);

    mesh->m_vVertexList[0] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 0.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[1] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 0.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
    mesh->m_vVertexList[2] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 0.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
    mesh->m_vVertexList[3] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 0.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

    UINT iIndex = 0;
    mesh->m_vIndexList[iIndex++] = 0; 	mesh->m_vIndexList[iIndex++] = 1; 	mesh->m_vIndexList[iIndex++] = 2;
    mesh->m_vIndexList[iIndex++] = 0;	mesh->m_vIndexList[iIndex++] = 2; 	mesh->m_vIndexList[iIndex++] = 3;

    mesh->CreateVertexBuffer();
    mesh->CreateIndexBuffer();

    m_Shapes.insert(std::make_pair(L"plane", mesh));
}
void TEngine::CreateLineShapes()
{
    // box
    auto mesh = std::make_shared<UStaticMeshComponent>();
    TVector3 vMin = TVector3(0, 0, 0.0f);
    TVector3 vMax = TVector3(+1, 1, 1.0f);
    mesh->m_vVertexList.resize(2);
    mesh->m_vIndexList.resize(2);

    mesh->m_vVertexList[0] = PNCT_VERTEX(vMin, TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
    mesh->m_vVertexList[1] = PNCT_VERTEX(vMax, TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));

    UINT iIndex = 0;
    mesh->m_vIndexList[iIndex++] = 0;
    mesh->m_vIndexList[iIndex++] = 1;

    mesh->CreateVertexBuffer();
    mesh->CreateIndexBuffer();

    m_Shapes.insert(std::make_pair(L"line", mesh));
}
void TEngine::CreateDefaultShapes()
{
    CreateBoxShapes();
    CreatePlaneShapes();
    CreateLineShapes();
}
std::shared_ptr<UStaticMeshComponent> TEngine::GetShape(std::wstring name)
{
    auto shape = m_Shapes.find(name);
    if (shape != m_Shapes.end())
    {
        return shape->second;
    }
    return nullptr;
}
