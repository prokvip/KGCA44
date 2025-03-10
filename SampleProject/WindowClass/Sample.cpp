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
    //  �� ���÷��� �׷���ī��
    IDXGIAdapter* pAdapter = nullptr;
    // �׷��� ī���� �ϵ���� ����(�ִ뼺��)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
    // ȭ�� �׷��Ƚ��� ����� ��Ÿ ���̺귯���� ����ϰڴ�. 
    HMODULE Software = NULL;
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
    UINT FeatureLevels = 1;
    UINT SDKVersion = D3D11_SDK_VERSION;// ��ġ�Ǿ� �ִ� ������ ����ϰڴ�.

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    // ������۸�( ����Ʈ ����, ����� <-> ȭ�����) 
    // �����
    scd.BufferCount = 1;
    scd.BufferDesc.Width = m_WindowSize.x;
    scd.BufferDesc.Height = m_WindowSize.y;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = m_hWnd;
    scd.Windowed = true;
    // �ֻ���
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    // ���ø�.
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
        // ��ȯ��
        &m_pSwapChain,
        &m_pd3dDevice,
        &pFeatureLevel,//D3D_FEATURE_LEVEL_11_0
        &m_pd3dContext);
  
    if (FAILED(hr))
    {
        DX_CHECK(hr, _T(__FUNCTION__));
        return false;
    }

    //RTV ������� �����ּҸ� ��´�.
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
    // ���ӵ�ο�
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