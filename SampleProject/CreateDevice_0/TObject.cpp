#include "TObject.h"
#include "TDevice.h"
void	TObject::Init()
{}
void	TObject::Frame()
{}
void	TObject::Render()
{
	TDevice::m_pd3dContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pd3dContext->PSSetShader(m_pPixelShader, nullptr, 0);
	TDevice::m_pd3dContext->IASetInputLayout(m_pInputLayout);

	// 정점버퍼에서 Offsets에서 시작하여
	// Strides크기로 정점을 정점쉐이더로 전달해라.
	UINT Strides = sizeof(TVertex2);
	UINT Offsets = 0;
	TDevice::m_pd3dContext->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&Strides,
		&Offsets);
	TDevice::m_pd3dContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pd3dContext->Draw(m_vVertexList.size(), 0);
}
void	TObject::Release()
{
	if (m_pCode) m_pCode->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pInputLayout) m_pInputLayout->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
}
bool	TObject::Create() 
{
	if (!CreateVertexBuffer())
	{
		return false;
	}
	if (!CreateVertexShader())
	{
		return false;
	}
	if (!CreatePixelShader())
	{
		return false;
	}
	if (!CreateInputLayout())
	{
		return false;
	}
	return true;
}
bool	TObject::CreateVertexBuffer() 
{
	// 화면좌표계(x,y)
	// v1:0,0      ->      v2:800, 0
	//   |	     400,300
	// v3:0,600            v3:800,600
	// 
	// 직각좌표계(x,y)	
	// v1:-400,300    ->       v2:400, 400
	//              0,0
	// v3:0,-300               v3:400,-300

	// 화면좌표계  <-> 변환  <-> 직각좌표계


	// 정규화장치(NDC)좌표계(x,y)	
	// v1:-1,1     0,1       v2:1, 1
	//    -1,0     0,0          1, 0
	// v3:1,-1     0,-1      v3:1,-1
	// 화면좌표계  <-> 변환  <-> 직각좌표계
	// 직각좌표계  <-> 변환  <-> NDC좌표계
	// NDC좌표계  <-> 변환  <-> 직각좌표계
	m_vVertexList.resize(6);
	m_vVertexList[0].x = -1.0f; m_vVertexList[0].y = 1.0f;
	m_vVertexList[1].x = 1.0f; m_vVertexList[1].y = 1.0f;
	m_vVertexList[2].x = -1.0f; m_vVertexList[2].y = -1.0f;

	m_vVertexList[3]= m_vVertexList[1];
	m_vVertexList[4].x = 1.0f; m_vVertexList[4].y = -1.0f;
	m_vVertexList[5]= m_vVertexList[2];


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(TVertex2)*6;
	// 읽고쓰기권한 설정(CPU X,X, GPU 0,0)
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_vVertexList.at(0);
	HRESULT hr = TDevice::m_pd3dDevice->CreateBuffer(
		&bd, &sd,	&m_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool	TObject::CreateVertexShader() 
{
	// hlsl  컴파일
	ID3DBlob* pErrorCode = nullptr;
	HRESULT hr = D3DCompileFromFile(L"VertexShader.txt",
						nullptr,nullptr, 
						"VS","vs_5_0",0,0,		
						&m_pCode,
						&pErrorCode);
	if (FAILED(hr))
	{
		MessageBoxA(g_hWnd, 
					 (char*)pErrorCode->GetBufferPointer(),
					"ERROR", MB_OK);
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreateVertexShader(
		m_pCode->GetBufferPointer(),
		m_pCode->GetBufferSize(),
		nullptr,
	&m_pVertexShader);
	if (FAILED(hr))
	{
		DX_CHECK(hr, _T(__FUNCTION__));
		return false;
	}
		
	if (pErrorCode) pErrorCode->Release();
	return true;
}
bool	TObject::CreatePixelShader() 
{
	// hlsl  컴파일
	ID3DBlob* pCode = nullptr;
	ID3DBlob* pErrorCode = nullptr;
	HRESULT hr = D3DCompileFromFile(L"VertexShader.txt",
		nullptr, nullptr,
		"PS", "ps_5_0", 0, 0,
		&pCode,
		&pErrorCode);
	if (FAILED(hr))
	{
		MessageBoxA(g_hWnd,
			(char*)pErrorCode->GetBufferPointer(),
			"ERROR", MB_OK);
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreatePixelShader(
		pCode->GetBufferPointer(),
		pCode->GetBufferSize(),
		nullptr,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		DX_CHECK(hr, _T(__FUNCTION__));
		return false;
	}

	if (pCode) pCode->Release();
	if (pErrorCode) pErrorCode->Release();
	return true;
}
bool	TObject::CreateInputLayout() 
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "KGCA",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT szNumCounter = sizeof(layout) / sizeof(layout[0]);
		
	HRESULT hr = TDevice::m_pd3dDevice->CreateInputLayout(
		layout,
		szNumCounter,
		m_pCode->GetBufferPointer(),
		m_pCode->GetBufferSize(),
	&m_pInputLayout);
	if (FAILED(hr))
	{
		DX_CHECK(hr, _T(__FUNCTION__));
		return false;
	}
	return true;
}

bool	TObject2D::Create()
{
	TObject::Create();
	return true;
}
void	TObject2D::Init()
{}
void	TObject2D::Frame() {
	TObject::Frame();
}
void	TObject2D::Render() {
	TObject::Render();
}
void	TObject2D::Release() {
	TObject::Release();
}