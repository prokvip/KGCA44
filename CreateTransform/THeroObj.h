#pragma once
#include "TMapObj.h"
class THeroObj : public TObject2D
{
	TMapObj* m_pMap = nullptr;
	TMatrix3   m_matScale;
	TMatrix3   m_matRotate;
	TMatrix3   m_matTrans;
	TMatrix3   m_matWorld; // s * r * t
	TVector2   m_vScale = { 1.0f, 1.0f };
	float      m_fAngleRadian = 0.0f;
public:
	void SetMap(TMapObj* pMap) { m_pMap = pMap; }
	virtual void Frame() override;
	virtual void SetVertexData()override;
	virtual void UpdatePosition() override;
	virtual void UpdateScale(float sx, float sy);
	virtual void UpdateRotation(float fRadian);
public:
	void AddPosition(float x, float y);
	void AddPosition(TVector2 v);
	THeroObj()
	{
		m_fSpeed = 300.0f;
	}
};

