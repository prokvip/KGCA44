#include "Sample.h"
void DX_CHECK(HRESULT hr, const TCHAR* function)
{
    if (FAILED(hr))
    {
        LPWSTR output;
        WCHAR buffer[256] = { 0, };
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | 
            FORMAT_MESSAGE_IGNORE_INSERTS | 
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, hr, 
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&output, 0, NULL);
        wsprintf(buffer, L"File=%ls\nLine=%d\nFuction=%ls", _T(__FILE__), __LINE__, function);
        std::wstring msg = buffer;
        msg += L"\n";
        msg += output;

        std::wstring title = L"ERROR(";
        title += std::to_wstring(hr);
        title += L")";
        MessageBox(NULL, msg.c_str(),
            title.c_str(), MB_OK);
    }
}
bool   Sample::CreateDevice()
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
    UINT FeatureLevels = 1;
    UINT SDKVersion = D3D11_SDK_VERSION;// 설치되어 있는 버전을 사용하겠다.

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
        &m_pSwapChain,
        &m_pd3dDevice,
        &pFeatureLevel,//D3D_FEATURE_LEVEL_11_0
        &m_pd3dContext);
  
    if (FAILED(hr))
    {
        DX_CHECK(hr, _T(__FUNCTION__));
        return false;
    }

    //RTV 백버퍼의 시작주소를 얻는다.
    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
                        (LPVOID*)&pBackBuffer);
        if (FAILED(hr))
        {
            DX_CHECK(hr, _T(__FUNCTION__));
            return false;
        }
        hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL,
                            &m_pRTV);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        DX_CHECK(hr, _T(__FUNCTION__));
        return false;
    }
    // viewport
    m_MainVP.Width = (FLOAT)m_WindowSize.x;
    m_MainVP.Height = (FLOAT)m_WindowSize.y;
    m_MainVP.MinDepth = 0.0f;
    m_MainVP.MaxDepth = 1.0f;
    m_MainVP.TopLeftX = 0;
    m_MainVP.TopLeftY = 0;

    m_pd3dContext->RSSetViewports(1, &m_MainVP);
    m_pd3dContext->OMSetRenderTargets(1, &m_pRTV, NULL);
}
void   Sample::Init() 
{
    if (!CreateDevice())
    {

    }
}
void   Sample::Frame()  
{
    int a = 0;
}
void   Sample::Render() 
{    
    float ClearColor[] = {0.0f, 0.0f,0.0f, 1.0f};
    m_pd3dContext->ClearRenderTargetView(m_pRTV, ClearColor);
    // 게임드로우
    m_pSwapChain->Present(0, 0);
}
void   Sample::Release() 
{
    if (m_pRTV)m_pRTV->Release();
    if (m_pd3dDevice)m_pd3dDevice->Release();
    if (m_pd3dContext)m_pd3dContext->Release();
    if (m_pSwapChain)m_pSwapChain->Release();
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