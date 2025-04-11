#pragma once
#include <AActor.h>
#include <fbxsdk.h>
#include "TAssetFileFormat.h"
//libfbxsdk - md.lib
//libxml2 - md.lib
//zlib - md.lib
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib,"libxml2-md.lib")
#pragma comment(lib,"zlib-md.lib")

class TFbxImporter
{
public:
	FbxManager* m_pManager;
	FbxImporter* m_pImporter;
	FbxScene* m_pScene;
	FbxNode* m_pRootNode;
	std::vector<FbxMesh*>  m_FbxMeshs;
	T::TMatrix     DxConvertMatrix(T::TMatrix m);
	T::TMatrix     ConvertAMatrix(FbxAMatrix& m);
public:
	bool  Load(std::string loadfile, TAssetFileFormat* actor);
	void  PreProcess(FbxNode* pNode);
	void  ParseMesh(
		FbxMesh* fbxmesh, TAssetFileFormat* actor);
	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet,
		int vertexIndex, int uvIndex, FbxVector2& uv);
	FbxColor ReadColor( FbxMesh* mesh,
						DWORD dwVertexColorCount,
						FbxLayerElementVertexColor* pVertexColorSet,
						DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh,
		DWORD dwVertexNormalCount, FbxLayerElementNormal* VertexNormalSets,
		int controlPointIndex, int iVertexIndex);
	void  Destroy();

	std::string ParseMaterial(FbxSurfaceMaterial* pSurface);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial*);

	void        GetAnimation(FbxNode* node, TAssetFileFormat* actor);
};

