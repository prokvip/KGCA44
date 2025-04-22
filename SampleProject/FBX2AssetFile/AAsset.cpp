#include "AAsset.h"
bool AAsset::Import(std::wstring szFileName,std::shared_ptr<AAsset>& asset)
{
	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, szFileName.c_str(), L"rb");
	if (err != 0) return false;

	TAssetFileHeader fileHeader;	
	fread(&fileHeader, sizeof(TAssetFileHeader), 1, fp);

	asset->m_iStartFrame = fileHeader.iStartFrame;
	asset->m_iEndFrame = fileHeader.iLastFrame;
	asset->m_szFileName.resize(fileHeader.iLength);
	asset->m_ptNodeList.resize(fileHeader.iNumNodeCounter);

	fread((void*)asset->m_szFileName.data(), sizeof(wchar_t),fileHeader.iLength, fp);	
	fread(&asset->m_ptNodeList.at(0), sizeof(TFbxNode),	fileHeader.iNumNodeCounter, fp);

	auto mesh = std::make_shared<UStaticMeshComponent>();
	mesh->SetOwner(asset.get());

	for (int index = 0; index < fileHeader.iNumNodeCounter; index++)
	{
		auto pair = mesh->m_FbxNodeNames.insert(std::make_pair(asset->m_ptNodeList[index].m_szName, index));
		if (pair.second == false)
		{
			int k = 0;
		}
		mesh->m_FbxParentNameNodes.insert(std::make_pair(asset->m_ptNodeList[index].m_szName,
			asset->m_ptNodeList[index].m_szParentName));
	}

	for (int iMesh =0; iMesh < fileHeader.iNumNodeCounter; iMesh++)
	{
		auto child = std::make_shared<UPrimitiveComponent>();

		TAssetFileHeader childheader;
		fread(&childheader, sizeof(TAssetFileHeader), 1, fp);				
		child->m_bRenderMesh = childheader.isMesh;
		if (childheader.isMesh > 0)
		{
			child->m_matBindPose.resize(childheader.iBindposeMatrix);
			fread(&child->m_matBindPose.at(0),sizeof(TMatrix),childheader.iBindposeMatrix, fp);
		}
		if (childheader.iNumTrack > 0)
		{
			child->m_AnimList.resize(childheader.iNumTrack);
			fread(&child->m_AnimList.at(0),	sizeof(TMatrix), childheader.iNumTrack, fp);
		}
		if (childheader.iNumWeight > 0)
		{
			child->m_matID.resize(childheader.iNumWeight);
			fread(&child->m_matID.at(0), sizeof(UINT), childheader.iNumWeight, fp);
			
			child->m_szNames.resize(childheader.iNumWeight);			
			for (int index = 0; index < childheader.iNumWeight; index++)
			{
				wchar_t name[64] = { 0, };				
				fread(&name, _countof(name), 1, fp);
				child->m_szNames[index] = name;
				child->m_FbxNodeNames.insert(std::make_pair(child->m_szNames[index], index));
				auto pair = mesh->m_FbxNodeNames.insert(std::make_pair(child->m_szNames[index], index));
				if (pair.second==false)
				{
					int k = 0;
				}
			}
		}
		if (childheader.iNumTexture > 0)
		{
			child->m_csTextures.resize(childheader.iNumTexture);
			for (int itex = 0; itex < childheader.iNumTexture; itex++)
			{
				TTexFileHeader texHead;
				fread(&texHead, sizeof(TTexFileHeader), 1, fp);
				fread((void*)child->m_csTextures.data(), sizeof(wchar_t), texHead.iLength, fp);
			}
		}

		if (childheader.isSubMesh > 0)
		{
			for (int isubchild = 0; isubchild < childheader.iSubVertexBufferCounter; isubchild++)
			{
				auto subchild = std::make_shared<UPrimitiveComponent>();
				
				int iSize;
				fread(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					subchild->m_vVertexList.resize(iSize);
					fread(&subchild->m_vVertexList.at(0), sizeof(PNCT_VERTEX), iSize, fp);
				}

				fread(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					subchild->m_vIndexList.resize(iSize);
					fread(&subchild->m_vIndexList.at(0), sizeof(DWORD), iSize, fp);
				}

				fread(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					subchild->m_vIWList.resize(iSize);
					fread(&subchild->m_vIWList.at(0), sizeof(IW_VERTEX), iSize, fp);
				}	
				child->m_SubChilds.emplace_back(subchild);
			}
		}
		else
		{
			int iSize;
			fread(&iSize, sizeof(int), 1, fp);
			if (iSize > 0)
			{
				mesh->m_vVertexList.resize(iSize);
				fread(&mesh->m_vVertexList.at(0),
					sizeof(PNCT_VERTEX), iSize, fp);
			}

			fread(&iSize, sizeof(int), 1, fp);
			if (iSize  > 0)
			{
				mesh->m_vIndexList.resize(iSize);
				fread(&mesh->m_vIndexList.at(0), sizeof(DWORD), iSize, fp);
			}

			
			fread(&iSize, sizeof(int), 1, fp);
			if (iSize > 0)
			{
				mesh->m_vIWList.resize(iSize);
				fread(&mesh->m_vIWList.at(0), sizeof(IW_VERTEX), iSize, fp);
			}
		}
		mesh->m_Childs.emplace_back(child);
	}
	asset->SetMesh(mesh);

	err = fclose(fp);
	if (err != 0) return false;
	_fcloseall();
	//////////////////////////////////////////////////////////////////////////////
	/// 랜더링 데이터 
	D3D11_INPUT_ELEMENT_DESC layoutiw[] =
	{
		// 0~8
		{ "POS",  0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  0, DXGI_FORMAT_R32G32_FLOAT,			0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "TEXCOORD",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",1, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 16,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",2, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 32,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",3, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT iNumCnt = sizeof(layoutiw) / sizeof(layoutiw[0]);

	//////////////////////////////////////////////////////////////////////////
	asset->Init();	
	// 몇개의 오브젝트가 있느냐?
	for (int iMesh = 0; iMesh < asset->GetMesh()->m_Childs.size(); iMesh++)
	{
		asset->m_CurrentAnimMatrix.resize(asset->GetMesh()->m_Childs.size());
		auto child = asset->GetMesh()->m_Childs[iMesh];
		for (int i = 0; i < asset->GetMesh()->m_Childs.size(); i++)
		{
			if (_tcscmp(asset->m_ptNodeList[iMesh].m_szParentName,
				asset->m_ptNodeList[i].m_szName) == 0)
			{
				child->m_pParent = asset->GetMesh()->m_Childs[i].get();
				break;
			}
		}

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
						texPath += L"T_Manny_01_D.PNG";
					}
					else
					{
						texPath += child->m_csTextures[0];
					}

					pMaterial->Load(L"../../data/shader/Character.txt", texPath);
					child->SetMaterial(pMaterial);
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
				for (int iSubMaterial = 0; iSubMaterial < child->m_SubChilds.size(); iSubMaterial++)
				{
					auto sub = child->m_SubChilds[iSubMaterial];
					if (sub->m_vVertexList.size() == 0)
					{
						sub->m_bRenderMesh = false;
						continue;
					}

					sub->CreateVertexBuffer();
					sub->CreateIndexBuffer();

					auto pMaterial = std::make_shared<UMaterial>();
					std::wstring texPath = L"../../data/fbx/";
					if (child->m_csTextures[iSubMaterial].empty() == false)
					{
						texPath += child->m_csTextures[iSubMaterial];
					}
					else
					{
						if (iSubMaterial == 0) texPath += L"T_Manny_02_D.PNG";
						else texPath += L"T_Manny_01_D.PNG";
					}

					pMaterial->Load(L"../../data/shader/Character.txt", texPath);

					if (pMaterial->m_pShader)
					{
						pMaterial->SetInputLayout(I_InputLayout.Load(pMaterial->m_pShader->m_pCode.Get(), layoutiw, iNumCnt, L"PNCT_IW"));
					}
					sub->SetMaterial(pMaterial);
				}
			}
		}
	}	
	return true;
}
bool  AAsset::Export(AAsset* tFile, std::wstring szFileName)
{
	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, szFileName.c_str(), L"wb");
	if (err != 0) return false;
	auto mesh = tFile->GetMesh();
	TAssetFileHeader fileHeader = tFile->m_Header;
	fileHeader.iLength = tFile->m_szFileName.size(); // 파일명 크기
	fileHeader.iNumNodeCounter = mesh->m_Childs.size();
	fileHeader.iVersion = 100;
	fileHeader.matWorld = tFile->m_matWorld;
	fileHeader.iNumTrack = mesh->m_AnimList.size();
	fileHeader.iStartFrame = fileHeader.iStartFrame;
	fileHeader.iLastFrame = fileHeader.iLastFrame;
	fileHeader.iFrameSpeed = 30;
	fileHeader.iBindposeMatrix = tFile->GetMesh()->m_matBindPose.size();

	fwrite(&fileHeader, sizeof(TAssetFileHeader), 1, fp);
	fwrite(tFile->m_szFileName.c_str(), sizeof(wchar_t), fileHeader.iLength, fp);	
	fwrite(&tFile->m_expFbxNodes.at(0), sizeof(TFbxNode), fileHeader.iNumNodeCounter, fp);

	for (auto& mesh : tFile->GetMesh()->m_Childs)
	{
		TAssetFileHeader header;
		ZeroMemory(&header, sizeof(header));	
		_tcscpy_s(header.szName, _countof(header.szName),mesh->m_szName.c_str());
		header.isMesh = mesh->m_bRenderMesh;
		header.iBindposeMatrix = mesh->m_matBindPose.size();
		header.isSubMesh = (mesh->m_SubChilds.size() > 0) ? 1 : 0;
		header.iSubVertexBufferCounter = mesh->m_SubChilds.size();
		header.iSubIndexBufferCounter = 0;
		header.iSubIWVertexBufferCounter = mesh->m_SubChilds.size();
		header.iNumTrack = mesh->m_AnimList.size();
		header.iNumTexture = mesh->m_csTextures.size();
		header.iNumWeight = mesh->m_matID.size();

		fwrite(&header, sizeof(TAssetFileHeader), 1, fp);

		// bindpose
		if (header.isMesh > 0)
		{
			fwrite( &mesh->m_matBindPose.at(0),sizeof(TMatrix),mesh->m_matBindPose.size(), fp);
		}
		if (header.iNumTrack > 0)
		{
			fwrite(&mesh->m_AnimList.at(0), sizeof(TMatrix),header.iNumTrack, fp);
		}
		if (header.iNumWeight > 0)
		{
			fwrite(&mesh->m_matID.at(0), sizeof(UINT), header.iNumWeight, fp);

			wchar_t name[64] = { 0, };
			for (int iname = 0; iname < header.iNumWeight; iname++)
			{
				size_t length = _countof(name);
				_tcscpy_s(name, length, mesh->m_szNames[iname].c_str());
				fwrite(&name, length, 1, fp);
			}
		}
		
		for (auto tex : mesh->m_csTextures )
		{
			TTexFileHeader texHead;
			texHead.iLength = tex.size();
			fwrite(&texHead, sizeof(TTexFileHeader), 1, fp);
			fwrite(tex.c_str(), sizeof(wchar_t), texHead.iLength, fp);
		}

		if (header.isSubMesh > 0)
		{
			for (auto sub : mesh->m_SubChilds)
			{
				int iSize = sub->m_vVertexList.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					fwrite(&sub->m_vVertexList.at(0),
						sizeof(PNCT_VERTEX), iSize, fp);
				}
			
				iSize = sub->m_vIndexList.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					fwrite(&sub->m_vIndexList.at(0), sizeof(DWORD), iSize, fp);
				}
			
				iSize = sub->m_vIWList.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize > 0)
				{
					fwrite(&sub->m_vIWList.at(0), sizeof(IW_VERTEX), iSize, fp);
				}
			}
		}
		else
		{
			int iSize = mesh->m_vVertexList.size();
			fwrite(&iSize, sizeof(int), 1, fp);
			if (iSize > 0)
			{
				fwrite(&mesh->m_vVertexList.at(0),
					sizeof(PNCT_VERTEX), iSize, fp);
			}

			iSize = mesh->m_vIndexList.size();
			fwrite(&iSize, sizeof(int), 1, fp);
			if (iSize > 0)
			{
				fwrite(&mesh->m_vIndexList.at(0), sizeof(DWORD), iSize, fp);
			}

			iSize = mesh->m_vIWList.size();
			fwrite(&iSize, sizeof(int), 1, fp);
			if (iSize > 0)
			{
				fwrite(&mesh->m_vIWList.at(0), sizeof(IW_VERTEX), iSize, fp);
			}
		}
	}
	err = fclose(fp);
	if (err != 0) return false;
	_fcloseall();
	return true;
}