#pragma once
#include "TObject2D.h"
struct TCell
{
	TRect  rt;
	UINT   iTexID;
};
class TMapMeshRender : public TMeshRender
{
public:
	virtual void	SetVertexData() override;
	virtual void	SetIndexData() override;
	virtual bool	CreateVertexBuffer()override;
	virtual bool	CreateIndexBuffer()override;
	virtual bool	CreateInputLayout()override;
	virtual void	PreRender()override;
	virtual void	Render()override;
	virtual void    PostRender() override;
};
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
	std::vector<TCell>  m_Cells;
	void	SetCellCounter(UINT iRow=10, UINT iCol=10);
public:
	virtual bool Create(TWorld* pWorld) override;
	virtual void Transform(TVector2 vCamera)override;
	virtual void Frame() override;
	virtual void PreRender()override;
	virtual void Render()override;
	virtual void PostRender() override;
public:
	TMapObj(UINT iCellX, UINT iCellY);
	TMapObj(TRect rt, UINT iCellX, UINT iCellY);
	TMapObj();
};

