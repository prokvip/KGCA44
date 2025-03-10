#pragma once
#include "TEngine.h"
#include "AActor.h"
class Sample : public TEngine
{
	std::shared_ptr<AActor> m_pActor;
	UStaticMeshComponent* Load(std::wstring filename);
	
public:
	void Init() override;
	void Tick() override;
	void Render() override;
	void Release() override;
};

