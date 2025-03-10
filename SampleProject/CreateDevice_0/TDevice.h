#pragma once
#include "TStd.h"
class TDevice
{
public:
    // ��ġ �������̽� ȹ��(����)
    static ID3D11Device*           m_pd3dDevice;  // ����
    static ID3D11DeviceContext*    m_pd3dContext; // �,����
    static IDXGISwapChain*         m_pSwapChain;
    static ID3D11RenderTargetView* m_pRTV;
    static D3D11_VIEWPORT			m_MainVP;
public:
    bool   CreateDevice();
    void   Init();
    void   Frame();
    void   PreRender();
    void   Render();
    void   PostRender();
    void   Release();
};

