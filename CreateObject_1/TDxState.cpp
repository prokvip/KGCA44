#include "TDxState.h"
#include "TDevice.h"
ID3D11SamplerState* TDxState::m_pLinearSS =nullptr;
ID3D11SamplerState* TDxState::m_pPointSS = nullptr;

void  TDxState::Create()
{
	D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW= D3D11_TEXTURE_ADDRESS_WRAP;    
	HRESULT hr = TDevice::m_pd3dDevice->CreateSamplerState(&sd, &m_pLinearSS);
	if (FAILED(hr))
	{

	}
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = TDevice::m_pd3dDevice->CreateSamplerState(&sd, &m_pPointSS);
	if (FAILED(hr))
	{

	}
}

void  TDxState::Release()
{
	if (m_pLinearSS)m_pLinearSS->Release();
	if (m_pPointSS)m_pPointSS->Release();
}