#pragma once
#include "TGameCore.h"
#include <d3d11.h>
#include <tchar.h> // _T("") == L""
//#pragma comment(lib,"d3d11.lib") // �Ӽ� �߰����Ӽ� 
class Sample : public TGameCore
{
	// ��ġ �������̽� ȹ��(����)
	ID3D11Device*				m_pd3dDevice = nullptr;
	ID3D11DeviceContext* 		m_pd3dContext = nullptr;
	IDXGISwapChain*				m_pSwapChain = nullptr;
	ID3D11RenderTargetView*		m_pRTV = nullptr;
	D3D11_VIEWPORT				m_MainVP;
public:
	bool   CreateDevice();
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
};

