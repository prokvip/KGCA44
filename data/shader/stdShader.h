#pragma once
// »ó¼ö	
cbuffer cb0 : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
}
struct VS_In
{
	float3 p : POS;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEX;
};
struct VS_Out
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD0;
};
// ret(R,G,B,A) 
struct PS_Out
{
	float4 c : SV_TARGET;
};


Texture2D  g_txDiffuseA : register(t0);// SRV
Texture2D  g_txMaskA    : register(t1);// SRV
SamplerState   sample   : register(s0);
