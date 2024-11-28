#pragma once
#include "TGameCore.h"
class Sample : public TGameCore
{
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};

