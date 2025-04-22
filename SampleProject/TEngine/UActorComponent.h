#pragma once
#include "UObject.h"
class AActor;
class UActorComponent
{
public:
	std::wstring m_szName;
	std::wstring m_szParentName;
	AActor* m_pOwner=nullptr;
	void SetOwner(AActor* pOwner) { m_pOwner = pOwner; }
};

