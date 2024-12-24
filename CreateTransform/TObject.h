#pragma once
#include "TCollision.h"
#include "TMeshRender.h"

class TObject
{
public:
	TMeshRender*	m_pMeshRender = nullptr;
public:
	TVector2		m_vPos;
	TVector2		m_vDir;
	float			m_fSpeed;
	bool			m_bDead = false;
	TRect			m_srtScreen;
	TSphere			m_Sphere;
	TLoadResData	m_LoadResData;
	TShader*		m_pShader = nullptr;
	TTexture*		m_pTexture = nullptr;
	std::vector<TVector2>		m_vScreenList;
	std::vector<PCT_VERTEX>		m_vVertexList;
public:
	virtual bool	Create();   
	virtual bool	Create(TLoadResData data);
	virtual bool	Create(TLoadResData data,
		TVector2 s,		// 화면좌표 시작
		TVector2 t) ;   // 화면좌표 끝		
	virtual TObject& SetShader(TShader* pShader = nullptr);
	virtual TObject& SetTexture(TTexture*);
	virtual TObject& SetLayout(TInputLayout* pInputLayout = nullptr);
	virtual bool LoadTexture(std::wstring texName);
	virtual bool	CreateVertexShader();
	virtual bool	CreatePixelShader();
	virtual void    SetVertexData() {};
	virtual void    SetIndexData() {};
public:
	virtual void	Init();
	virtual void	Frame();
	virtual void    Transform(TVector2 vCamera);
	virtual void	PreRender();
	virtual void	Render();
	virtual void	PostRender();
	virtual void	Release();
public:
	TObject();
	virtual ~TObject();
};
