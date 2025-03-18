#pragma once
#include <AActor.h>
#include <fbxsdk.h>
//libfbxsdk - md.lib
//libxml2 - md.lib
//zlib - md.lib
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib,"libxml2-md.lib")
#pragma comment(lib,"zlib-md.lib")


class TFbxImporter
{
public:
	FbxManager*		m_pManager;
	FbxImporter*	m_pImporter;
	FbxScene*		m_pScene;
	FbxNode*		m_pRootNode;
public:
	bool  Load(std::wstring loadfile, AActor& actor);
};

