#pragma once
struct VS_Out
{
	float4 p : SV_POSITION;
	float4 c : COLOR;
	float2 t : TEXCOORD0;
};
// ret(R,G,B,A)
struct PS_Out
{
	float4 c : SV_TARGET;
};


Texture2D  g_txDiffuseA : register(t0);// SRV
SamplerState   sample : register(s0);
