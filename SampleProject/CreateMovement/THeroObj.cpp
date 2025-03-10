#include "THeroObj.h"
#include "TDevice.h"
void THeroObj::Frame()
{
	// *시간의 동기화
	// 1000 frame = 1초 동안에 100이동하자.
				// 100 * 0.001f;
	// 100 frame  = 1초 동안에 100이동하자.
				// 100 * 0.01f;
	// 10 frame  = 1초 동안에 100이동하자.
				// 100 * 0.1f;
	if (g_GameKey.dwWkey == KEY_HOLD)
	{
		m_vPos.y -= m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwSkey == KEY_HOLD)
	{
		m_vPos.y += m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwAkey == KEY_HOLD)
	{
		m_vPos.x -= m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwDkey == KEY_HOLD)
	{
		m_vPos.x += m_fSpeed * g_fSPF;
	}

	UpdatePosition();
}
void THeroObj::SetVertexData()
{
	if (m_pTexture == nullptr) return;
	TObject2D::SetVertexData();
	float xSize = m_pTexture->m_TexDesc.Width;
	float ySize = m_pTexture->m_TexDesc.Height;
	TRect rt;
	rt.SetS(90.0f, 1.0f, 132.0f, 61.0f );
	m_vVertexList[0].t = { rt.x / xSize,rt.y / ySize };
	m_vVertexList[1].t = { rt.w / xSize,rt.y / ySize };
	m_vVertexList[2].t = { rt.x / xSize,rt.h / ySize };
	m_vVertexList[3].t = { rt.w / xSize,rt.h / ySize };
}