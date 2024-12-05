#pragma once
#include "TGameCore.h"
#include "TObject2D.h"
class TMap : public TObject2D
{

};
class THero : public TObject2D
{

};
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

