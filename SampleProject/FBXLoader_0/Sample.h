#pragma once
#include "TEngine.h"
#include "TFbxImporter.h"
//https://aps.autodesk.com/developer/overview/fbx-sdk
// FBX file -> Loader -> Engine
// Tool에서 출력 -> FBX file -> Loader -> Export(**.asset) 
// 엔진에서 로딩 -> Export Loader -> Engine

class Sample : public TEngine
{
	TFbxImporter   m_FbxImporter;
	std::vector<std::shared_ptr<AActor>>   m_FbxObjs;
public:
	public:
	void Init() override;
	void Tick() override;
	void Render() override;
	void Release() override;
};

