#pragma once
#include "TGameCore.h"
#include "TObject.h"
class Sample : public TGameCore
{
	using tObject = std::shared_ptr<TObject>;
	std::vector<tObject>    m_ObjList;
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};

