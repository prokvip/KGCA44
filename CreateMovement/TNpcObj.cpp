#include "TNpcObj.h"
#include "TDevice.h"
void TNpcObj::Frame()
{
	if (m_srtScreen.x > g_ptClientSize.x - 50.0f )
	{
		m_vDir.x *= -1.0f;
		m_srtScreen.x = g_ptClientSize.x - 50.0f;
	}
	if (m_srtScreen.x < 0.0f)
	{
		m_vDir.x *= -1.0f;
		m_srtScreen.x = 0.0f;
	}
	if (m_srtScreen.y > g_ptClientSize.y - 50.0f)
	{
		m_vDir.y *= -1.0f;		
		m_srtScreen.y = g_ptClientSize.y - 50.0f;
	}
	if (m_srtScreen.y < 0.0f)
	{
		m_vDir.y *= -1.0f;
		m_srtScreen.y = 0.0f;
	}
	// v = v + d*s : 직선의 벡터의 방정식
	//m_vPos = m_vPos + m_vDir * (g_fSPF * m_fSpeed);
	m_srtScreen.x = m_srtScreen.x + m_vDir.x * (g_fSPF * m_fSpeed);
	m_srtScreen.y = m_srtScreen.y + m_vDir.y * (g_fSPF * m_fSpeed);


	TVector2 s = { m_srtScreen.x, m_srtScreen.y };
	TVector2 t;
	t.x = m_srtScreen.x + m_srtScreen.w;
	t.y = m_srtScreen.y + m_srtScreen.h;
	m_vScreenList[0] = s;
	m_vScreenList[1] = { t.x, s.y };
	m_vScreenList[2] = { s.x, t.y };
	m_vScreenList[3] = t;
}
void TNpcObj::SetVertexData()
{
	if (m_pTexture == nullptr) return;
	TObject2D::SetVertexData();
	float xSize = m_pTexture->m_TexDesc.Width;
	float ySize = m_pTexture->m_TexDesc.Height;
	TRect rt;
	rt.SetS( 46.0f, 62.0f, 114.0f, 142.0f);
	m_vVertexList[0].t = { rt.x / xSize,rt.y / ySize };
	m_vVertexList[1].t = { rt.w / xSize,rt.y / ySize };
	m_vVertexList[2].t = { rt.x / xSize,rt.h / ySize };
	m_vVertexList[3].t = { rt.w / xSize,rt.h / ySize };
}