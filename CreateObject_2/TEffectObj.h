#pragma once
#include "TObject2D.h"
struct TEffectData
{
	std::vector<RECT>   m_rtList;
	UINT			    m_iNumAnimFrame = 0;
	float				m_fLifeTime = 1.0f;
	float				m_fOffsetTime = 1.0f;
	bool			    m_bLoop = false;
};
class TEffectObj :   public TObject2D
{
	TEffectData		m_Data;// 초기데이터
public:	
	std::vector<RECT>   m_rtList;
	UINT			m_iNumAnimFrame = 0;
	UINT			m_iAnimFrame = 0;
	float			m_fLifeTime = 1.0f;
	float			m_fOffsetTime = 1.0f;
	bool			m_bLoop = false;
	bool			m_bDead = false;
	float			m_fCurrentTime = 0.0f;
public:
	virtual void SetData(TEffectData data);
	virtual void Frame() override;
	virtual void SetVertexData();
};

