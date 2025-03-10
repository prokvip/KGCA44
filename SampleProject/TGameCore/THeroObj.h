#pragma once
#include "TMapObj.h"
#include "TProjectile.h"
class THeroObj : public TObject2D
{
	TMapObj* m_pMap = nullptr;	
public:
	//using tProjectile = std::shared_ptr<TProjectile>;
	std::shared_ptr<TProjectile>		m_pProjectile;
public:
	void SetMap(TMapObj* pMap) { m_pMap = pMap; }
	virtual void Init() override;
	virtual void Frame() override;
	virtual void Render()override;
	virtual void Release()override;
	virtual void SetVertexData()override;
	void    HitOverlap(TObject* pObj, THitResult hRes) override;
public:
	THeroObj()
	{
		m_fSpeed = 300.0f;
	}
};

