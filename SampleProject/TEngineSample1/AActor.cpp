#include "AActor.h"
#include "TDevice.h"
#include "TEngine.h"

AActor::AActor() {
	m_vScale = { 1,1,1 };
	CreateConstantBuffer();
};
 AActor::~AActor() {};
void AActor::SetMesh(UStaticMeshComponent* mesh)
{
	Mesh = mesh;
}
bool	AActor::CreateConstantBuffer()
{
	// 화면좌표계  <-> 변환  <-> 직각좌표계
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(cbData);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_cbData;
	HRESULT hr = TDevice::m_pd3dDevice->CreateBuffer(
		&bd, &sd, m_pConstantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
void AActor::Init() {
}
void AActor::Tick() 
{
	
	if (Mesh != nullptr) Mesh->Tick();
}
void AActor::Render() 
{	
	m_matScale.Scale(m_vScale);
	m_matRotation.RotateY(m_vRotation.y);
	m_matTrans.Trans(m_vPosition);
	m_matWorld = 
		m_matOffset *
		m_matScale * 
		m_matRotation * 
		m_matTrans *
		m_matParent;

	m_cbData.matView = TMatrix::Transpose(TEngine::g_pCamera->m_matView);
	m_cbData.matProj = TMatrix::Transpose(TEngine::g_pCamera->m_matProj);
	m_cbData.matWorld = TMatrix::Transpose(m_matWorld);

	TDevice::m_pd3dContext->UpdateSubresource(
		m_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
	// 0번 레지스터에 셰이더상수 m_pConstantBuffer를 연결
	TDevice::m_pd3dContext->VSSetConstantBuffers(
		0, 1, m_pConstantBuffer.GetAddressOf());
	if (Mesh != nullptr)
	{
		Mesh->Render();
	}
}
void AActor::Destroy() {
	if (Mesh != nullptr) Mesh->Destroy();
}