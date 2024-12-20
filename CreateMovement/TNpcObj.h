#pragma once
#include "TObject2D.h"
class TNpcObj : public TObject2D
{
public:
	virtual void Frame() override;
	virtual void SetVertexData();
	TNpcObj()
	{
		m_fSpeed = 150.0f;
		m_vDir.x = 1.0f;
		m_vDir.y = 1.0f;
	}
};

