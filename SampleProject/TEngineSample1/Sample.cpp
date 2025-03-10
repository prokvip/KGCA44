#include "Sample.h"
UStaticMeshComponent* Sample::Load(std::wstring filename)
{
	UStaticMeshComponent* mesh = new UStaticMeshComponent();
	TVector3 vMin = TVector3(-1, -1, -1.0f);
	TVector3 vMax = TVector3(+1, +1, 1.0f);
	mesh->m_vVertexList.resize(24);
	mesh->m_vIndexList.resize(36);
	
	mesh->m_vVertexList[0] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	mesh->m_vVertexList[1] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	mesh->m_vVertexList[2] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	mesh->m_vVertexList[3] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));
	// µÞ¸é
	mesh->m_vVertexList[4] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	mesh->m_vVertexList[5] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	mesh->m_vVertexList[6] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	mesh->m_vVertexList[7] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	mesh->m_vVertexList[8] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	mesh->m_vVertexList[9] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	mesh->m_vVertexList[10] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	mesh->m_vVertexList[11] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ¿ÞÂÊ
	mesh->m_vVertexList[12] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	mesh->m_vVertexList[13] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	mesh->m_vVertexList[14] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	mesh->m_vVertexList[15] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	// À­¸é
	mesh->m_vVertexList[16] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	mesh->m_vVertexList[17] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	mesh->m_vVertexList[18] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	mesh->m_vVertexList[19] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ¾Æ·§¸é
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

	return mesh;
}

void Sample::Init()
{
	m_pActor = std::make_shared<AActor>();
	m_pActor->Init();
	auto data = Load(L"box.fbx");
	m_pActor->SetMesh(data);
	//m_pActor->SetMesh(Load("Sphere.fbx"));
	auto pMaterial = std::make_shared<UMaterial>();
	pMaterial->Load(L"../../data/shader/pnct.txt",
		L"../../data/texture/gg.bmp");
	m_pActor->GetMesh()->SetMaterial(pMaterial);


	/*m_pSceneCamera->CreateViewMatrix(
		{ 10, 0, 0.0f },
		{ 0, 0, 0.0f },
		{ 0, 1.0f, 0.0f });
	float fAspect = (float)g_ptClientSize.x / (float)g_ptClientSize.y;
	m_pSceneCamera->CreateProjMatrix(
		(float)T_Pi * 0.25f, fAspect, 1.0f, 1000.0f);*/
}
void Sample::Tick() 
{
	m_pActor->Tick();
}
void Sample::Render() {
	m_pActor->Render();
}
void Sample::Release() {
	m_pActor->Destroy();
}

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