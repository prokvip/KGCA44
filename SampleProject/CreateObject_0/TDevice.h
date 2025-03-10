#pragma once
#include "TStd.h"
class TDevice
{
public:
    // 장치 인터페이스 획득(생성)
    static ID3D11Device*           m_pd3dDevice;  // 생성
    static ID3D11DeviceContext*    m_pd3dContext; // 운영,관리
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

