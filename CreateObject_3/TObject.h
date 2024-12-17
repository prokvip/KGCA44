#pragma once
#include "TVertex.h"
#include "TDxState.h"
#include "TSound.h"
#include "TTexture.h"
#include "TInputLayout.h"
struct TRect
{
	float   x, y;
	float   w, h;
};
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
	std::vector<PCT_VERTEX>    m_vVertexList;
	std::vector<DWORD>		   m_vIndexList;
	TRect						m_rtScreen;
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
		TVertex2 s,		// 拳搁谅钎 矫累
		TVertex2 t) ;   // 拳搁谅钎 场
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
	virtual void	PreRender();
	virtual void	Render();
	virtual void	PostRender();
	virtual void	Release();
public:
	TObject();
	virtual ~TObject();
};
