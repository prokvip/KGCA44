#pragma once
#include "TStd.h"
class TDevice
{
    // ��ġ �������̽� ȹ��(����)
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pd3dContext = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D11RenderTargetView* m_pRTV = nullptr;
    D3D11_VIEWPORT				m_MainVP;
public:
    bool   CreateDevice();
    void   Init();
    void   Frame();
    void   Render();
    void   Release();
};
