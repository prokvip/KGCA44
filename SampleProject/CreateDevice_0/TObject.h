#pragma once
#include "TStd.h"
struct TVertex2
{
	float  x;
	float  y;

};
class TObject
{
	ID3D11Buffer*		m_pVertexBuffer=nullptr;	
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3DBlob*			m_pCode;
	ID3D11PixelShader*  m_pPixelShader = nullptr;
	ID3D11InputLayout*  m_pInputLayout = nullptr;

	std::vector<TVertex2>    m_vVertexList;
public:
	virtual bool	Create() ; // ����
		virtual bool	CreateVertexBuffer(); // ����
		virtual bool	CreateVertexShader(); // ����
		virtual bool	CreatePixelShader(); // ����
		virtual bool	CreateInputLayout(); // ����
public:
	virtual void	Init();
	virtual void	Frame();
	virtual void	Render();
	virtual void	Release();
};

class TObject2D : public TObject
{
public:
	virtual bool	Create() override; // ����
	virtual void	Init()override;
	virtual void	Frame()override;
	virtual void	Render() override;
	virtual void	Release()override;
};