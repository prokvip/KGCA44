#pragma once
#include "AActor.h"
class TSkyObject : public AActor
{
	std::vector< std::shared_ptr<UMaterial>> m_Materials;
public:
	bool  Load(std::shared_ptr<UStaticMeshComponent>);
	void  Render()  override;
	void  PostRender() override;
};

