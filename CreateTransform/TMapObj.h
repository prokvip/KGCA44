#pragma once
#include "TObject2D.h"
struct TCell
{
	TRect  rt;
	UINT   iTexID;
};
//class TMapMeshRender : public TMeshRender
//{
//
//};
class TMapObj : public TObject2D
{
	TTexture* m_pTexs[4];
	UINT  m_iNumRow = 2;
	UINT  m_iNumCol = 2;
	UINT  m_iNumCellRow ;
	UINT  m_iNumCellCol;
	UINT  m_iNumVertex;
	UINT  m_iNumIndex;
	TVector2 m_vCellDistance;
public:
	ComPtr<ID3D11Buffer> m_pVertexBuffer = nullptr;
	ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
	TInputLayout*		 m_pInputLayout = nullptr;
	std::vector<DWORD>	m_vIndexList;
	std::vector<TCell>  m_Cells;
	void	SetCellCounter(UINT iRow=10, UINT iCol=10);
public:
	virtual bool Create() override;
	virtual void SetVertexData() override;
	virtual void SetIndexData() override;
	virtual bool	CreateVertexBuffer();
	virtual bool	CreateIndexBuffer();
	virtual bool	CreateInputLayout(); 
	virtual void UpdateVertexData();
	virtual TObject& SetShader(TShader* pShader = nullptr);
	virtual TObject& SetTexture(TTexture*);
	virtual TObject& SetLayout(TInputLayout* pInputLayout = nullptr);
	virtual void	Transform(TVector2 vCamera);
	virtual void Frame() override;
	virtual void	PreRender()override;
	virtual void	Render()override;
	void PostRender() override;
public:
	TMapObj(UINT iCellX, UINT iCellY);
	TMapObj(TRect rt, UINT iCellX, UINT iCellY);
	TMapObj();
};
