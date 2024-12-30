#pragma once
#include "TGameCore.h"
#include "TWorld.h"
#include "TSound.h"
#include "TFiniteState.h"
using RECT_ARRAY = std::vector<RECT>;
class Sample : public TGameCore
{
	TFiniteStateMachine      m_fsm;
	std::shared_ptr<TWorld>  m_pWorld;
	TVector2        m_vCamera = { 400.0f, 300.0f };
	TTexture*		m_pBitmap1Mask = nullptr;
	using tObject = std::shared_ptr<TObject2D>;
	using tNpc = std::shared_ptr<TNpcObj>;
	
	std::shared_ptr<TMapObj>	m_pMap = nullptr;
	std::shared_ptr<THeroObj>	m_pHero = nullptr;
	std::vector<tNpc>			m_NpcList;
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
	bool CreateSound();
    bool CreateMap();
    bool CreateHero();
	bool CreateNPC();
    bool CreateEffect();
	TVector2 GetWorldMousePos();
};

