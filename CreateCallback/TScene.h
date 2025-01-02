#pragma once
#include "TStd.h"
#include "TWorld.h"
#include "TSound.h"
#include "TFiniteState.h"
class TGame;
class TScene
{
	static std::vector<std::shared_ptr<TScene>>  m_pActionList;
public:
	bool		  m_bSceneChange = false;
	std::shared_ptr<TWorld>  m_pWorld;
public:
	UINT   m_iState = 0;
	TScene(TGame* p);
	TScene();
	virtual ~TScene();
public:
	virtual void ProcessAction(TObject* pObj) = 0;
public:
	TGame* m_pOwner=nullptr;
public:
	virtual void   Init() = 0;
	virtual void   Frame() = 0;
	virtual void   Render() = 0;
	virtual void   Release() = 0;
};

