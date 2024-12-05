#pragma once
#include "TGameCore.h"
#include "TObject.h"
class Sample : public TGameCore
{
	using tObject = std::shared_ptr<TObject>;
	tObject					m_pObject=nullptr;
	std::vector<tObject>    m_ObjList;
	ID3D11Resource* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTexSRV = nullptr;
public:
	virtual void   Load(std::wstring texName);
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};

