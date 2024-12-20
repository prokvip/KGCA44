#pragma once
#include "TCollision.h"
#include "TDxState.h"
#include "TSound.h"
#include "TTexture.h"
#include "TInputLayout.h"
struct TLoadResData
{
	std::wstring texPathName;
	std::wstring texShaderName;

};
class TObject
{
public:
	ComPtr<ID3D11Buffer> m_pVertexBuffer=nullptr;	
	ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
	TShader*			m_pShader = nullptr;	
	//TShader*			m_pPixelShader = nullptr;
	TTexture*			m_pTexture = nullptr;
	TInputLayout*		m_pInputLayout = nullptr;
	std::vector<TVector2>		m_vScreenList;
	std::vector<PCT_VERTEX>		m_vVertexList;
	std::vector<DWORD>			m_vIndexList;
	TRect						m_srtScreen;
	TLoadResData				m_LoadResData;
public:
	TObject& SetShader(TShader* pShader= nullptr);
	TObject& SetTexture(TTexture* );
	TObject& SetLayout(TInputLayout* pInputLayout=nullptr);
	//virtual bool SetLayout( TShader* pShader,
	//						g_VertexLayout[0]);
	virtual bool	Create();   
	virtual bool	Create(TLoadResData data);
	virtual bool	Create(TLoadResData data,
		TVector2 s,		// 拳搁谅钎 矫累
		TVector2 t) ;   // 拳搁谅钎 场
		virtual bool	CreateVertexBuffer(); // 积己
		virtual bool	CreateIndexBuffer(); // 积己
		virtual bool	CreateVertexShader(); // 积己
		virtual bool	CreatePixelShader(); // 积己
		virtual bool	CreateInputLayout(); // 积己
	virtual void    SetVertexData();
	virtual void    SetIndexData();
	virtual bool    LoadTexrture(std::wstring texName);
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
