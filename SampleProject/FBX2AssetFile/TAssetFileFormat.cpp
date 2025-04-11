#include "TAssetFileFormat.h"
bool  TAssetFileFormat::Export(TAssetFileFormat* tFile, std::wstring szFileName)
{
	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, szFileName.c_str(), L"wb");
	if (err != 0) return false;

	TAssetFileHeader fileHeader = tFile->m_Header;
	fileHeader.iLength = tFile->m_szFileName.size(); // 파일명 크기
	fileHeader.iChildNodeCounter = tFile->m_ChildList.size();
	fileHeader.iVersion = 100;
	fileHeader.matWorld = tFile->m_matWorld;
	fileHeader.iNumTrack = tFile->m_pAnimationMatrix.size();
	fileHeader.iStartFrame = fileHeader.iStartFrame;
	fileHeader.iLastFrame = fileHeader.iLastFrame;
	fileHeader.iFrameSpeed = fileHeader.iFrameSpeed;

	fwrite(&fileHeader, sizeof(TAssetFileHeader), 1, fp);
	fwrite(tFile->m_szFileName.c_str(), sizeof(wchar_t), fileHeader.iLength, fp);

	// TNode 
	//fwrite(&tFile->m_ptNodeList.at(0), sizeof(TFbxNode), fileHeader.iNumNodeCounter, fp);

	// bone matrix
	// 71
	if (fileHeader.iLastFrame > 0)
	{
		for (int iBone = 0; iBone < tFile->m_pBoneAnimMatrix.size(); iBone++)
		{
			fwrite(&tFile->m_pBoneAnimMatrix[iBone].at(0),
				sizeof(T::TMatrix), fileHeader.iLastFrame, fp);
		}
	}


	for (auto mesh : tFile->m_ChildList)
	{
		TAssetFileHeader header = mesh->m_Header;
		header.iLength = mesh->m_szTexFileList.size(); // 텍스처 개수
		header.iChildNodeCounter = mesh->m_ChildList.size();
		header.matWorld = mesh->m_matWorld;
		header.isSubMesh = (mesh->m_vSubMeshVertexList.size() > 0) ? 1 : 0;
		header.iSubVertexBufferCounter = mesh->m_vSubMeshVertexList.size();
		header.iSubIndexBufferCounter = mesh->m_vSubMeshIndexList.size();
		header.iSubIWVertexBufferCounter = mesh->m_vSubMeshIWVertexList.size();
		header.iNumTrack = mesh->m_pAnimationMatrix.size();
		header.iStartFrame = fileHeader.iStartFrame;
		header.iLastFrame = fileHeader.iLastFrame;
		header.iFrameSpeed = fileHeader.iFrameSpeed;
		fwrite(&header, sizeof(TAssetFileHeader), 1, fp);

		// Bindpose matrix
		int iSize = mesh->m_matBindPose.size();
		fwrite(&iSize, sizeof(int), 1, fp);
		if (iSize <= 0) continue;
		fwrite(&mesh->m_matBindPose.at(0),
			sizeof(T::TMatrix), iSize, fp);

		//fwrite(&mesh->m_pAnimationMatrix, sizeof(T::TMatrix), header.iNumTrack, fp);
		for (int iFrame = 0; iFrame < header.iNumTrack; iFrame++)
		{
			fwrite(&mesh->m_pAnimationMatrix[iFrame], sizeof(T::TMatrix), 1, fp);
		}

		for (auto tex : mesh->m_szTexFileList)
		{
			TTexFileHeader texHead;
			texHead.iLength = tex.size();
			fwrite(&texHead, sizeof(TTexFileHeader), 1, fp);
			fwrite(tex.c_str(), sizeof(wchar_t), texHead.iLength, fp);
		}
		if (header.isSubMesh > 0)
		{
			for (auto sub : mesh->m_vSubMeshVertexList)
			{
				int iSize = sub.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize <= 0) continue;
				fwrite(&sub.at(0), sizeof(PNCT_VERTEX), sub.size(), fp);
			}
			for (auto sub : mesh->m_vSubMeshIndexList)
			{
				int iSize = sub.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize <= 0) continue;
				fwrite(&sub.at(0), sizeof(DWORD), sub.size(), fp);
			}
			for (auto sub : mesh->m_vSubMeshIWVertexList)
			{
				int iSize = sub.size();
				fwrite(&iSize, sizeof(int), 1, fp);
				if (iSize <= 0) continue;
				fwrite(&sub.at(0), sizeof(IW_Vertex), sub.size(), fp);
			}
		}
		else
		{
			int iLen = mesh->m_vVertexList.size();
			fwrite(&iLen, sizeof(int), 1, fp);
			if (iLen != 0)
			{
				fwrite(&mesh->m_vVertexList.at(0), sizeof(PNCT_VERTEX), mesh->m_vVertexList.size(), fp);
			}

			iLen = mesh->m_vIndexList.size();
			fwrite(&iLen, sizeof(int), 1, fp);
			if (iLen != 0)
			{
				fwrite(&mesh->m_vIndexList.at(0), sizeof(DWORD), mesh->m_vIndexList.size(), fp);
			}
			// index + weight
			iLen = mesh->m_vIWVertexList.size();
			fwrite(&iLen, sizeof(int), 1, fp);
			if (iLen != 0)
			{
				fwrite(&mesh->m_vIWVertexList.at(0), sizeof(IW_Vertex),
					mesh->m_vIWVertexList.size(), fp);
			}
		}
	}
	err = fclose(fp);
	if (err != 0) return false;
	_fcloseall();
	return true;
}