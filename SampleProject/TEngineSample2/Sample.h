#pragma once
#include "TEngine.h"
// 전후좌우 카메라.
class Sample : public TEngine
{
	std::shared_ptr<TCamera> m_pGameCamera;
	std::shared_ptr<AActor> m_SMHero;
	std::vector< std::shared_ptr<UMaterial>> m_Materials;
	std::shared_ptr<AActor> m_SMBox;
	std::shared_ptr<AActor> m_SMPlane;
	std::shared_ptr<AActor> m_SMLine;
public:
	public:
	void Init() override;
	void Tick() override;
	void Render() override;
	void Release() override;
};

