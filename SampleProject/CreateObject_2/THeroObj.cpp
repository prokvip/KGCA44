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
	float fSpeed = 100.0f;
	if (g_GameKey.dwWkey == KEY_HOLD)
	{
		m_rtScreen.y -= fSpeed * g_fSPF;
	}
	if (g_GameKey.dwSkey == KEY_HOLD)
	{
		m_rtScreen.y += fSpeed * g_fSPF;
	}
	if (g_GameKey.dwAkey == KEY_HOLD)
	{
		m_rtScreen.x -= fSpeed * g_fSPF;
	}
	if (g_GameKey.dwDkey == KEY_HOLD)
	{
		m_rtScreen.x += fSpeed * g_fSPF;
	}
	TVertex2 s = { m_rtScreen.x, m_rtScreen.y };
	// NDC <- Screen
	s.x = m_rtScreen.x / g_WindowSize.x; // 0 ~1
	s.y = m_rtScreen.y / g_WindowSize.y; // 0 ~1
	s.x = s.x * 2.0f - 1.0f;
	s.y = -(s.y * 2.0f - 1.0f);
	TVertex2 t;
	t.x = (m_rtScreen.x + m_rtScreen.w) / g_WindowSize.x;
	t.y = (m_rtScreen.y + m_rtScreen.h) / g_WindowSize.y;
	t.x = t.x * 2.0f - 1.0f;
	t.y = (t.y * 2.0f - 1.0f) * -1.0f;
	m_vVertexList[0].v = s;
	m_vVertexList[1].v = { t.x, s.y };
	m_vVertexList[2].v = { s.x, t.y };
	m_vVertexList[3].v = t;

	// gpu가 담당
	TDevice::m_pd3dContext->UpdateSubresource(
		m_pVertexBuffer, 0, nullptr,
		&m_vVertexList.at(0), 0, 0);
}
void THeroObj::SetVertexData()
{
	TObject::SetVertexData();
	float xSize = 400;
	float ySize = 300;
	TRect rt = { 90.0f, 1.0f, 132.0f, 61.0f };
	m_vVertexList[0].t = { rt.x / xSize,rt.y / ySize };
	m_vVertexList[1].t = { rt.w / xSize,rt.y / ySize };
	m_vVertexList[2].t = { rt.x / xSize,rt.h / ySize };
	m_vVertexList[3].t = { rt.w / xSize,rt.h / ySize };
}