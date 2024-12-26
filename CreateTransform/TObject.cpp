#include "TObject.h"
#include "TDevice.h"
void	TObject::Init()
{}
void	TObject::Frame()
{}
void	TObject::Transform(TVector2 vCamera)
{
}
void	TObject::PreRender()
{
	m_pMeshRender->PreRender();
}
void	TObject::Render()
{	
	PreRender();
	if (m_pTexture)
	{
		TDevice::m_pd3dContext->PSSetShaderResources(
			0, 1, &m_pTexture->m_pTexSRV);
	}
	
	if (m_pShader)
	{
		TDevice::m_pd3dContext->VSSetShader(
			m_pShader->m_pVertexShader.Get(), nullptr, 0);
		TDevice::m_pd3dContext->PSSetShader(
			m_pShader->m_pPixelShader.Get(), nullptr, 0);
	}
	PostRender();
}
void	TObject::PostRender()
{
	m_pMeshRender->PostRender();	
}
void	TObject::Release()
{
	
}
bool	TObject::CreateVertexShader()
{
	if (m_LoadResData.texShaderName.empty())
	{
		return true;
	}
	m_pShader = I_Shader.Load(m_LoadResData.texShaderName);
	if (m_pShader == nullptr)
	{
		return false;
	}
	return true;
}
bool	TObject::CreatePixelShader()
{
	if (m_LoadResData.texShaderName.empty())
	{
		return true;
	}
	if (m_pShader && m_pShader->m_pPixelShader == nullptr)
	{
		/*m_pShader = I_Shader.Load(m_LoadResData.texShaderName);
		if (m_pShader == nullptr)
		{
			return false;
		}*/
		return false;
	}
	return true;
}
bool	TObject::Create()
{
	SetVertexData();
	/*if (!CreateVertexBuffer())
	{
		return false;
	}
	SetIndexData();
	if (!CreateIndexBuffer())
	{
		return false;
	}*/
	if (!CreateVertexShader())
	{
		return false;
	}
	if (!CreatePixelShader())
	{
		return false;
	}
	/*if (!CreateInputLayout())
	{
		return false;
	}*/
	return true;
}
bool	TObject::Create(TLoadResData data)
{
	m_LoadResData = data;
	if (!LoadTexture(m_LoadResData.texPathName))
	{
		return false;
	}
	return Create();
}
bool	TObject::Create(TLoadResData data,
						TVector2 s,
						TVector2 t)
{
	m_LoadResData = data;
	m_srtScreen.SetP( s, t );
	
	//m_vScale = { (m_srtScreen.w / 2.0f),(m_srtScreen.w / 2.0f) };
	//m_fRoation = 0.0f;

	m_Sphere.vCenter = m_srtScreen.tCenter;	
	m_Sphere.fRadius = m_srtScreen.fRadius;
	m_vVertexList.resize(4);
	m_vScreenList.resize(4);
	m_vScreenList[0] = { m_srtScreen.x, m_srtScreen.y };
	m_vScreenList[1] = { m_srtScreen.x2, m_srtScreen.y };
	m_vScreenList[2] = { m_srtScreen.x, m_srtScreen.y2 };
	m_vScreenList[3] = { m_srtScreen.x2, m_srtScreen.y2 };
	m_vPos.x = s.x;
	m_vPos.y = s.y;
	if (!LoadTexture(m_LoadResData.texPathName))
	{
		return false;
	}
	return Create();
}

TObject& TObject::SetShader(TShader* pData)
{
	if (pData == nullptr)
	{
		m_pMeshRender->m_pShader = I_Shader.g_pDefaultShader;
	}
	else
	{
		m_pMeshRender->m_pShader = pData;
	}
	return *this;
}
TObject& TObject::SetTexture(TTexture* pData)
{
	m_pMeshRender->m_pTexture = pData;
	return *this;
}
TObject& TObject::SetLayout(TInputLayout* pData)
{
	if (pData == nullptr)
	{
		m_pMeshRender->m_pInputLayout = I_InputLayout.g_pInputLayout;
	}
	else
	{
		m_pMeshRender->m_pInputLayout = pData;
	}
	return *this;
}
bool   TObject::LoadTexture(std::wstring texName)
{
	m_pTexture = I_Tex.Load(texName);
	if (m_pTexture == nullptr)
	{
		return false;
	}
	return true;
}


TObject::TObject()
{
	m_srtScreen.SetS(0.0f, 0.0f, (float)g_ptClientSize.x, (float)g_ptClientSize.y);
	m_vPos.x = 0.0f;
	m_vPos.y = 0.0f;
	m_fSpeed = 100.0f;
}
TObject::~TObject()
{
}
