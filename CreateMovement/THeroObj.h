#pragma once
#include "TObject2D.h"
class THeroObj : public TObject2D
{
public:
	virtual void Frame() override;
	virtual void SetVertexData();
};

