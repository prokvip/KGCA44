#pragma once
#include "TWindow.h"
#include "TDevice.h"
#include "TTime.h"
#include "TInput.h"
#include "TDxWrite.h"
#include "TShader.h"
#include "TTexture.h"
#include "TInputlayout.h"
#include "TCamera.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "TSkyObject.h"
class TEngine : public TWindow
{	
public:
	std::shared_ptr<TSkyObject> m_SkyObj;
	static TCamera* g_pCamera;
	std::shared_ptr<TCamera> m_pSceneCamera;
	TTime		m_GameTimer;
	TInput		m_Input;
	TDevice		m_DxDevice;
	TDxWrite    m_DxWrite;
public:

	std::map<std::wstring, std::shared_ptr<UStaticMeshComponent>>  m_Shapes;
public:
	std::shared_ptr<UStaticMeshComponent> GetShape(std::wstring name);
	void CreateDefaultShapes();
	void CreateBoxShapes();
	void CreatePlaneShapes();
	void CreateLineShapes();
public:
	virtual void   Init() {};
	virtual void   Tick() {};
	virtual void   Render() {};
	virtual void   Release() {};
	virtual void   SetCamera(TCamera* pCamera=nullptr);
public:
	void   CoreInit();
	void   CoreFrame();
	void   CoreRender();
	void   CoreRelease();
	virtual bool   GameRun();
};

