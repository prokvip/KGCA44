#pragma once
#include "TVertex.h"
struct TRect
{
	float   x, y;
	float   w, h;
};
class TObject
{
	ID3D11Buffer*		m_pVertexBuffer=nullptr;	
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3DBlob*			m_pCode;
	ID3D11PixelShader*  m_pPixelShader = nullptr;
	ID3D11InputLayout*  m_pInputLayout = nullptr;
	ID3D11Resource*		m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTexSRV = nullptr;
	std::vector<PCT_VERTEX>    m_vVertexList;
	TRect				m_rtScreen;
public:
	virtual bool	Create();   
	virtual bool	Create(std::wstring texPath); 
	virtual bool	Create(std::wstring texPath,
		TVertex2 s,		// ȭ����ǥ ����
		TVertex2 t) ;   // ȭ����ǥ ��
		virtual bool	CreateVertexBuffer(); // ����
		virtual bool	CreateVertexShader(); // ����
		virtual bool	CreatePixelShader(); // ����
		virtual bool	CreateInputLayout(); // ����
	virtual void    SetVertexData();
	virtual bool    LoadTexrture(std::wstring texName);
public:
	virtual void	Init();
	virtual void	Frame();
	virtual void	Render();
	virtual void	Release();
public:
	TObject();
	virtual ~TObject();
};
