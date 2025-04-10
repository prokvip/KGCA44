#pragma once
#include "TMapObj.h"
class THeroObj : public TObject2D
{
	TMapObj* m_pMap = nullptr;	
public:
	void SetMap(TMapObj* pMap) { m_pMap = pMap; }
	virtual void Frame() override;
	virtual void SetVertexData()override;
	void    HitOverlap(TObject* pObj, THitResult hRes) override;
public:
	THeroObj()
	{
		m_fSpeed = 300.0f;
	}
};

