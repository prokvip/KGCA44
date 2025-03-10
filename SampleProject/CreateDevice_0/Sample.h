#pragma once
#include "TGameCore.h"
#include "TObject.h"
class Sample : public TGameCore
{
	TObject*				m_pObject=nullptr;
	std::vector<TObject*>   m_ObjList;
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};

