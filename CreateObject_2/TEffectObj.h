#pragma once
#include "TObject2D.h"
class TEffectObj :   public TObject2D
{
public:
	std::vector<RECT>  m_rtList;
	UINT			   m_iAnimFrame = 0;
public:
	TVertex2 ScreenToNDC(float x, float y, POINT size);
	virtual void Frame() override;
	virtual void SetVertexData();
};

