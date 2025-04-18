#include "TDxState.h"
#include "TDevice.h"
ID3D11SamplerState* TDxState::m_pLinearSS =nullptr;
ID3D11SamplerState* TDxState::m_pPointSS = nullptr;
ID3D11BlendState* TDxState::m_pAlphaBlend = nullptr;
void  TDxState::Create()
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = TRUE;
	bd.RenderTarget[0].BlendEnable  =TRUE;

	// rgb 혼합연산( 알파블랜딩 공식 )
	// 컬러(rgb)결과 = SRC * 소스알파값 + DEST * 1-소스알파값
	//  A = 0; A = 1  A=0.5
	// SRC컬러 : 픽쉘쉐이더의 결과값
	// DEST컬러 : 이미 출력되어 있는 백버퍼 컬러
	// 컬러(rgb)결과 = SRC * 1 + DEST * 0
	//     Final R = SRC.r * 1 + DEST.r * 0
	//     Final G = SRC.g * 1 + DEST.g * 0
	//     Final B = SRC.b * 1+ DEST.b * 0
	//        소스컬러 * SrcBlend 
	//                  +             BlendOp
	//        대상컬러 * DestBlend
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// A 알파값 연산
	//  Final A = SRC.a * 1 + DEST.a * 0
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha= D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask = 
		D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = TDevice::m_pd3dDevice->CreateBlendState(&bd,
		&m_pAlphaBlend);
	if (FAILED(hr))
	{

	}
	/// <summary>
	/// 샘플러 상태
	/// </summary>
	D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW= D3D11_TEXTURE_ADDRESS_WRAP;    
	 hr = TDevice::m_pd3dDevice->CreateSamplerState(&sd, &m_pLinearSS);
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
	if (m_pAlphaBlend)m_pAlphaBlend->Release();
}