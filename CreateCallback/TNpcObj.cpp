#include "TNpcObj.h"
#include "TDevice.h"
void TNpcObj::Frame()
{
	TVector2 vAdd = m_vPos;
	if (m_vPos.x > m_pMap->m_rtScreen.v2.x - m_rtScreen.vh.x)
	{
		m_vDir.x *= -1.0f;
		vAdd.x = m_pMap->m_rtScreen.v2.x - m_rtScreen.vh.x;
	}
	if (m_vPos.x < m_pMap->m_rtScreen.v1.x + m_rtScreen.vh.x)
	{
		m_vDir.x *= -1.0f;
		vAdd.x = m_pMap->m_rtScreen.v1.x + m_rtScreen.vh.x;
	}
	if (m_vPos.y > m_pMap->m_rtScreen.v2.y - m_rtScreen.vh.y)
	{
		m_vDir.y *= -1.0f;		
		vAdd.y = m_pMap->m_rtScreen.v2.y - m_rtScreen.vh.y;
	}
	if (m_vPos.y < m_pMap->m_rtScreen.v1.y + m_rtScreen.vh.y)
	{
		m_vDir.y *= -1.0f;
		vAdd.y = m_pMap->m_rtScreen.v1.y + m_rtScreen.vh.y;
	}
	// v = v + d*s : 직선의 벡터의 방정식
	m_vPos = vAdd + m_vDir * (g_fSPF * m_fSpeed);
	SetPosition(m_vPos);

}
void TNpcObj::SetVertexData()
{
	if (m_pTexture == nullptr) return;
	TObject2D::SetVertexData();
	float xSize = m_pTexture->m_TexDesc.Width;
	float ySize = m_pTexture->m_TexDesc.Height;
	TRect rt;
	rt.SetP( 46.0f, 62.0f, 114.0f, 142.0f);
	m_vVertexList[0].t = { rt.v1.x / xSize,rt.v1.y / ySize };
	m_vVertexList[1].t = { rt.v2.x / xSize,rt.v1.y / ySize };
	m_vVertexList[2].t = { rt.v1.x / xSize,rt.v2.y / ySize };
	m_vVertexList[3].t = { rt.v2.x / xSize,rt.v2.y / ySize };
}