#pragma once
#include "TEngine.h"
#include "TFbxImporter.h"
//https://aps.autodesk.com/developer/overview/fbx-sdk
class Sample : public TEngine
{
	TFbxImporter   m_FbxImporter;
	AActor		   m_FbxBox;
public:
	public:
	void Init() override;
	void Tick() override;
	void Render() override;
	void Release() override;
};

