#pragma once
#include "TEngine.h"
// Scene Camera( First Persion Character camera)
class Sample : public TEngine
{
public:
	public:
	void Init() override;
	void Tick() override;
	void Render() override;
	void Release() override;
};

