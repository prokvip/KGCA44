#pragma once

#include "TGuiFSM.h"
struct TStateDataUI
{
	float m_fTimer;
	float m_fDefaultTimer;
	float m_fDistance;
	TVector2 vDefaultScale;
	TVector2 vDefaultPos;
	TVector2 vDefaultRotate;
};
class TControlGUI : public TObject2D
{
public:
	UINT   m_iSelectState = 0;
	TGuiState* m_pAction = nullptr;
	std::vector<TStateDataUI>   m_StateData;
	static std::vector<std::shared_ptr<TGuiState>>  m_pActionList;
	TFiniteStateMachine* m_pFsm = nullptr;
public:
	void SetFSM(TFiniteStateMachine* pFsm);
	void SetTransition(UINT iEvent);
	static void StartFSM();
	void FrameState(TObject* pHero);	
	virtual void Frame() override;
	void	Transform(TVector2 vCamera);
	void    TransformNDC();
	void	SetScale(float sx, float sy);
	virtual void SetVertexData();
	bool    LoadTexture(std::wstring texName)override;
	void    HitSelect(TObject* pObj, THitResult hRet) override;
	bool	Create(TWorld* pWorld, TLoadResData data,TVector2 s,TVector2 e);
	TControlGUI()
	{
		m_fSpeed = 150.0f;
		m_vDir.x = 1.0f;
		m_vDir.y = 1.0f;
	}
};
class TButtonGUI : public TControlGUI
{
public:
	std::vector<TTexture*> m_pTexState;
public:
	void   Frame();
	void   PostRender();
	bool   LoadTexture(std::wstring texName);
};
