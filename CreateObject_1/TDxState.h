#pragma once
#include <d3d11.h>
class TDxState
{
public:
	static ID3D11SamplerState* m_pLinearSS;
	static ID3D11SamplerState* m_pPointSS;
	static void Create();
	static void Release();
};
