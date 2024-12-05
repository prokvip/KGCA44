#include "Sample.h"
#include "WICTextureLoader.h"
// 속성->C/C++->일반->추가 포함 디렉토리(./Inc)
void   Sample::Load(std::wstring texName)
{    
    HRESULT hr = DirectX::CreateWICTextureFromFile(
        TDevice::m_pd3dDevice,
        texName.c_str(),
        &m_pTexture,
        &m_pTexSRV   );
    if (FAILED(hr))
    {
        DX_CHECK(hr, _T(__FUNCTION__));
    }
}
void   Sample::Init() 
{
    Load(L"kgcalogo.bmp");

    m_pObject = std::make_shared<TObject2D>();
    if (m_pObject)
    {
        m_pObject->Create();
        m_ObjList.emplace_back(m_pObject);
    }
}
void   Sample::Frame()  
{
    if (g_GameKey.dwWkey == KEY_PUSH)
    {
        INT A = 0;
    }
    if (g_GameKey.dwWkey == KEY_UP)
    {
        INT A = 0;
    }

    for (auto data : m_ObjList)
    {
        data->Frame();
    }
}
void   Sample::Render() 
{    
    TDevice::m_pd3dContext->PSSetShaderResources(
            0, 1, &m_pTexSRV );
    for (auto data : m_ObjList)
    {
        data->Render();
    }
}
void   Sample::Release() 
{
    for (auto data : m_ObjList)
    {
        data->Release();
    }
    if(m_pTexture)m_pTexture->Release();
    if (m_pTexSRV)m_pTexSRV->Release();
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