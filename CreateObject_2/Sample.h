#pragma once
#include "TGameCore.h"
#include "TMapObj.h"
#include "THeroObj.h"
#include "TEffectObj.h"
#include "TSound.h"
using RECT_ARRAY = std::vector<RECT>;
class Sample : public TGameCore
{
	using tObject = std::shared_ptr<TObject>;
	std::vector<tObject>    m_ObjList;
	TSound* m_pSound = nullptr;
	TSound* m_pSoundEffect = nullptr;
	std::vector<RECT_ARRAY>  m_rtSpriteList;
public:
	bool GameDataLoad(W_STR filename);
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};
