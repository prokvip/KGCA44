#pragma once
#include "TCollision.h"
#include "TMeshRender.h"

class TObject
{
public:
	TMeshRender*	m_pMeshRender = nullptr;
public:
	TMatrix3   m_matScale;
	TMatrix3   m_matRotate;
	TMatrix3   m_matTrans;
	TMatrix3   m_matWorld; // s * r * t
	TVector2   m_vScale = { 1.0f, 1.0f };
	float      m_fAngleRadian = 0.0f;
	TVector2		m_vPos;
	TVector2		m_vDir;
	float			m_fSpeed;
	bool			m_bDead = false;
	TRect			m_rtScreen;
	TSphere			m_Sphere;
	TLoadResData	m_LoadResData;
	TShader*		m_pShader = nullptr;
	TTexture*		m_pTexture = nullptr;
	std::vector<TVector2>		m_vScreenList;
	std::vector<PCT_VERTEX>		m_vVertexList;
public:
	virtual void SetScale(float sx, float sy);
	virtual void SetRotation(float fRadian);
	virtual void SetPosition(TVector2 p);
	virtual void AddPosition(float x, float y);
	virtual void AddPosition(TVector2 v);
	virtual void AddScale(float x, float y);
	virtual void AddScale(TVector2 v);
	virtual void AddRotation(float angle);
public:
	virtual bool	Create();   
	virtual bool	Create(TLoadResData data);
	virtual bool	Create(TLoadResData data,
		TVector2 s,		// ȭ����ǥ ����
		TVector2 t) ;   // ȭ����ǥ ��		
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
