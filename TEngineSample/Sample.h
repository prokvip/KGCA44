#pragma once
#include "TGameCore.h"
class Sample : public TGameCore
{
public:
	void Init() override;
	void Frame() override;
	void Render() override;
	void Release() override;
};

