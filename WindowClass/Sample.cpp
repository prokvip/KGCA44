#include "Sample.h"
void   Sample::Init() 
{
    D3D_FEATURE_LEVEL pFeatureLevel;
    //  주 디스플레이 그래픽카드
    IDXGIAdapter* pAdapter = nullptr;
    // 그래픽 카드의 하드웨어 성능(최대성능)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
    // 화면 그래픽스의 기능을 기타 라이브러리로 사용하겠다. 
    HMODULE Software = NULL;
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
    UINT FeatureLevels=1;
    UINT SDKVersion= D3D11_SDK_VERSION;// 설치되어 있는 버전을 사용하겠다.

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    // 더블버퍼링( 프런트 버퍼, 백버퍼 <-> 화면버퍼) 
    // 백버퍼
    scd.BufferCount = 1;
    scd.BufferDesc.Width = m_WindowSize.x;
    scd.BufferDesc.Height = m_WindowSize.y;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = m_hWnd;
    scd.Windowed = true;
    // 주사율
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    // 샘플링.
    scd.SampleDesc.Count = 1;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        pAdapter,
        DriverType,
        Software,
        Flags,
        &pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        &scd,
        // 반환값
        &m_pdSwapChain,
        &m_pd3dDevice,
        &pFeatureLevel,//D3D_FEATURE_LEVEL_11_0
        &m_pd3dContext);

    if (FAILED(hr))
    {

    }
}
void   Sample::Frame()  
{
    int a = 0;
}
void   Sample::Render() 
{
    int a = 0;
}
void   Sample::Release() 
{
    int a = 0;
}

//GameStart(800, 600);
int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    Sample sample;
    sample.SetWindowClass(hInstance);
    sample.SetWindow();
    sample.GameRun();    
}