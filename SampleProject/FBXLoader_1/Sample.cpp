#include "Sample.h"


void Sample::Init()
{
	std::vector<std::string> list =
	{
		//{"../../data/fbx/SKM_Manny.fbx"},		
		{"../../data/fbx/Turret_Deploy1.fbx"},
		//{"../../data/fbx/MultiCamera/MultiCameras.fbx"},
		/*{"../../data/fbx/box.fbx"},
		{"../../data/fbx/SM_Barrel.fbx"},
		{"../../data/fbx/sphereBox.fbx"},
		{"../../data/fbx/MultiCamera/MultiCameras.fbx"},
		{"../../data/fbx/ship/ship.fbx"},*/
	};

	D3D11_INPUT_ELEMENT_DESC layoutiw[] =
	{
		// 0~8
		{ "POS",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  0, DXGI_FORMAT_R32G32_FLOAT,			0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 16,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT iNumCnt = sizeof(layoutiw) / sizeof(layoutiw[0]);
	
	m_FbxObjs.resize(list.size());
	for (int iObj = 0; iObj < list.size(); iObj++)
	{
		m_FbxObjs[iObj] = std::make_shared<AActor>();
		m_FbxObjs[iObj]->Init();

		auto fbxobj = m_FbxObjs[iObj].get();
		if (m_FbxImporter.Load(list[iObj], fbxobj))
		{
			// 몇개의 오브젝트가 있느냐?
			for (int iMesh = 0; iMesh < m_FbxObjs[iObj]->GetMesh()->m_Childs.size(); iMesh++)
			{
				m_FbxObjs[iObj]->m_CurrentAnimMatrix.resize(m_FbxObjs[iObj]->GetMesh()->m_Childs.size());
				auto child = m_FbxObjs[iObj]->GetMesh()->m_Childs[iMesh];
				if (child->m_bRenderMesh)
				{
					if (child->m_SubChilds.size() == 0)
					{
						if (child->m_vVertexList.size())
						{
							auto pMaterial = std::make_shared<UMaterial>();
							std::wstring texPath = L"../../data/fbx/";
							if (child->m_csTextures.size() == 0)
							{
								texPath += L"kgca08.bmp";
							}
							else
							{
								texPath += child->m_csTextures[0];
							}

							pMaterial->Load(L"../../data/shader/Character.txt", texPath);
							child->SetMaterial(pMaterial);
							// iw
							child->m_vIWList.resize(child->m_vVertexList.size());
							for (int i = 0; i < child->m_vVertexList.size(); i++)
							{
								child->m_vIWList[i].i[0] = iMesh;
								child->m_vIWList[i].w[0] = 1.0f;
							}
							child->CreateVertexBuffer();
							child->CreateIndexBuffer();

							if (pMaterial->m_pShader)
							{
								pMaterial->SetInputLayout(I_InputLayout.Load(
									pMaterial->m_pShader->m_pCode.Get(), layoutiw, iNumCnt, L"PNCT_IW"));
							}
						}

					}
					else
					{
						for (int iSubMaterial = 0;iSubMaterial < child->m_SubChilds.size();iSubMaterial++)
						{
							auto sub = child->m_SubChilds[iSubMaterial];							
							if (sub->m_vVertexList.size() == 0)
							{
								sub->m_bRenderMesh = false;
								continue;
							}
							
							sub->m_vIWList.resize(sub->m_vVertexList.size());
							for (int i = 0; i < sub->m_vVertexList.size(); i++)
							{
								sub->m_vIWList[i].i[0] = iMesh;
								sub->m_vIWList[i].w[0] = 1.0f;
							}
							sub->CreateVertexBuffer();
							sub->CreateIndexBuffer();

							auto pMaterial = std::make_shared<UMaterial>();
							std::wstring texPath = L"../../data/fbx/";
							if (child->m_csTextures[iSubMaterial].empty() == false)
							{
								texPath += child->m_csTextures[iSubMaterial];
								pMaterial->Load(L"../../data/shader/Character.txt", texPath);	
								
							}
							if (pMaterial->m_pShader)
							{
								pMaterial->SetInputLayout(I_InputLayout.Load(
									pMaterial->m_pShader->m_pCode.Get(), layoutiw, iNumCnt, L"PNCT_IW"));
							}
							sub->SetMaterial(pMaterial);
						}
					}
				}
			}
		}
	}
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
	for (auto obj : m_FbxObjs)
	{
		//obj->m_vPosition = { -200.0f + 100.0f * index++,0,0 };
		obj->m_vPosition = { 0,0,0 };
		//obj->m_vRotation.y = g_fGT;
		obj->Tick();
	}
}
void Sample::Render() {

	for (auto obj : m_FbxObjs)
	{
		obj->Render();
	}
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