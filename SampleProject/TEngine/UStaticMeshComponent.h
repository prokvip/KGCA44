#pragma once
#include "UMeshComponent.h"

class UStaticMeshComponent :  public UMeshComponent
{
public:
	std::vector<std::shared_ptr<UPrimitiveComponent>>    m_Childs;
public:
	virtual void   Init();
	virtual void   Tick();
	virtual void   Render();
	virtual void   Destroy();
	void SetOwner(AActor* pOwner)
	{
		m_pOwner = pOwner;
	}
};

