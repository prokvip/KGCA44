#pragma once
#include "TScene.h"

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
using RECT_ARRAY = std::vector<RECT>;
class TSceneGameIn : public TScene
{
	TFiniteStateMachine      m_fsm;
	TGUIFSM					 m_GuiFSM;
	TVector2        m_vCamera = { 400.0f, 300.0f };
	TTexture* m_pBitmap1Mask = nullptr;
	using tObject = std::shared_ptr<TObject2D>;
	using tNpc = std::shared_ptr<TNpcObj>;
	using tUI = std::shared_ptr<TControlGUI>;

	std::shared_ptr<TMapObj>	m_pMap = nullptr;
	std::shared_ptr<THeroObj>	m_pHero = nullptr;
	std::vector<tNpc>			m_NpcList;
	std::vector< tUI>			m_UiList;
	std::list<tObject>			m_EffectList;
	TSound* m_pSound = nullptr;
	TSound* m_pSoundEffect = nullptr;
	std::vector<RECT_ARRAY>  m_rtSpriteList;
	std::vector<T_STR_VECTOR> m_szSpriteList;
public:
	void   AddEffect(TVector2 vPos, TVector2 tEnd);
	bool   GameDataLoad(W_STR filename);
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
public:
	virtual void ProcessAction(TObject* pObj);
public:
	TSceneGameIn(TGame* p);
	TSceneGameIn() { m_iState = TSceneState::SCENE_INGAME; };
	virtual ~TSceneGameIn();
public:
	bool CreateSound();
	bool CreateMap();
	bool CreateHero();
	bool CreateNPC();
	bool CreateEffect();
	bool CreateUI();
	TVector2 GetWorldMousePos();
};

