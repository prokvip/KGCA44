#include "Sample.h"

void Sample::Init()
{
	//std::vector<std::string> list =
	//{
	//	//{"../../data/fbx/Turret_Deploy1.fbx"},
	//	//{"../../data/fbx/MultiCamera/MultiCameras.fbx"},
	//	/*{"../../data/fbx/box.fbx"},
	//	{"../../data/fbx/SM_Barrel.fbx"},
	//	{"../../data/fbx/sphereBox.fbx"},
	//	{"../../data/fbx/MultiCamera/MultiCameras.fbx"},
	//	{"../../data/fbx/ship/ship.fbx"},*/
	//};
	std::vector<std::string> list =
	{
		//{"../../data/fbx/Man.fbx"},
		//{"../../data/fbx/Man.fbx"},
		{"../../data/fbx/SKM_Manny.fbx"},
		{"../../data/fbx/MM_Idle.fbx"},
		{"../../data/fbx/MM_Walk_Fwd.fbx"},
		//{"../../data/fbx/MM_Run_Fwd.fbx"},
		/*{"../../data/fbx/MM_run.fbx"},
		{"../../data/fbx/MM_walk.fbx"},
		{"../../data/fbx/Man.fbx"},	*/
	};
	std::vector<std::wstring> assetlist =
	{
		/*{L"../../data/fbx/Man.asset"},
		{L"../../data/fbx/Man.asset"},*/
		{L"../../data/fbx/SKM_Manny.asset"},
		{L"../../data/fbx/MM_Idle.asset"},
		{L"../../data/fbx/MM_Walk_Fwd.asset"},				
	};
	// asset 출력
	/*for (int iObj = 0; iObj < list.size(); iObj++)
	{
		auto asset= std::make_shared<AAsset>();
		m_FbxImporter.reset();
		if (m_FbxImporter.Load(list[iObj], asset.get()))
		{
			AAsset::Export(asset.get(), assetlist[iObj]);
		}
	}*/
	//// asset 로드
	for (int iObj = 0; iObj < list.size(); iObj++)
	{
		auto asset = std::make_shared<AAsset>();
		if(AAsset::Import(assetlist[iObj], asset ))
		{			
		}
		m_FbxObjs.emplace_back(asset);
	}	

	m_FbxObjs[0]->m_pCurrentAnimation = m_FbxObjs[1].get();
	//g_pCamera->m_fPitch = T_Pi * 0.25f;
	g_pCamera->CreateViewMatrix(
		{ 0, 0, -100.0f },
		{ 0, 0, 0.0f },
		{ 0, 1.0f, 0.0f });
	float fAspect = (float)g_ptClientSize.x / (float)g_ptClientSize.y;
	g_pCamera->CreateProjMatrix((float)T_Pi * 0.25f, fAspect, 1.0f, 1000.0f);
}
void Sample::Tick()
{
	int index = 0;
	m_FbxObjs[0]->Tick();
	//for (auto obj : m_FbxObjs)
	//{
	//	//obj->m_vPosition = { -200.0f + 100.0f * index++,0,0 };
	//	obj->m_vPosition = { 0,0,0 };
	//	//obj->m_vRotation.y = g_fGT;
	//	obj->Tick();
	//}
}
void Sample::Render() {

	m_FbxObjs[0]->Render();
	/*for (auto obj : m_FbxObjs)
	{
		obj->Render();
	}*/
}
void Sample::Release()
{
	for (auto obj : m_FbxObjs)
	{
		obj->Destroy();
	}
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