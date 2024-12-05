#pragma once
#include "TVertex.h"
class TObject
{
	ID3D11Buffer*		m_pVertexBuffer=nullptr;	
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3DBlob*			m_pCode;
	ID3D11PixelShader*  m_pPixelShader = nullptr;
	ID3D11InputLayout*  m_pInputLayout = nullptr;

	std::vector<PCT_VERTEX>    m_vVertexList;
public:
	virtual bool	Create() ; // 持失
		virtual bool	CreateVertexBuffer(); // 持失
		virtual bool	CreateVertexShader(); // 持失
		virtual bool	CreatePixelShader(); // 持失
		virtual bool	CreateInputLayout(); // 持失
	virtual void    SetVertexData();
public:
	virtual void	Init();
	virtual void	Frame();
	virtual void	Render();
	virtual void	Release();
};

class TObject2D : public TObject
{
public:
	virtual bool	Create() override; // 持失
	virtual void	Init()override;
	virtual void	Frame()override;
	virtual void	Render() override;
	virtual void	Release()override;
};