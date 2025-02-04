#pragma once
#include "TObject.h"
#include "TSceneIntro.h"
#include "TSceneLobby.h"
#include "TSceneGameIn.h"
#include "TSceneResult.h"

class TNextBtn : public TButtonGUI
{
public:
	void    HitSelect(TObject* pObj, THitResult hRet)
	{
		m_iSelectState = hRet.iState;
		if (m_iSelectState == T_SELECTED)
		{
			m_pWorld->m_pScene->m_bNextScene = true;
		}
	};
};
class TPrevBtn : public TButtonGUI
{
public:
	void    HitSelect(TObject* pObj, THitResult hRet)
	{
		m_iSelectState = hRet.iState;
		if (m_iSelectState == T_SELECTED)
		{
			m_pWorld->m_pScene->m_bPrevScene = true;
		}
	};
};

class TSceneFSM : public TFiniteStateMachine
{

};

class TGame : public TObject
{
public:
	TScene* m_pAction = nullptr;
	static std::vector<std::shared_ptr<TScene>>  m_pActionList;
	TFiniteStateMachine* m_pFsm = nullptr;
public:
	virtual void SetFSM(TFiniteStateMachine* pFsm);
	static  void CreateActionFSM();
	virtual void SetTransition(UINT iEvent);
	virtual void FrameState(TObject* pHero);
public:
	void		Init();
	void		Frame();
	void		Render();
	void		Release();
};

