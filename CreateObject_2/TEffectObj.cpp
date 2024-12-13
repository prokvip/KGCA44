#include "TEffectObj.h"
#include "TDevice.h"
TVertex2 TEffectObj::ScreenToNDC(float x, float y, POINT size)
{	
	TVertex2 ret = { x, y };
	ret.x = ( x / size.x) * 2.0f - 1.0f; // 0 ~1
	ret.y = -((y / size.y) * 2.0f - 1.0f);
	return ret;
}
void TEffectObj::Frame()
{
	float fSpeed = 100.0f;	
	TVertex2 s = ScreenToNDC(m_rtScreen.x, m_rtScreen.y, g_WindowSize);
	TVertex2 e = ScreenToNDC(
		m_rtScreen.x + m_rtList[m_iAnimFrame].right,
		m_rtScreen.y + m_rtList[m_iAnimFrame].bottom, g_WindowSize);
	m_vVertexList[0].v = s;
	m_vVertexList[1].v = { e.x, s.y };
	m_vVertexList[2].v = { s.x, e.y };
	m_vVertexList[3].v = e;
	
	float xSize = 400;
	float ySize = 300;
	static UINT  iFrame = 0;
	static float fTime = 0.0f;
	fTime += g_fSPF;
	//float fStep = spriteTime  / spriteFrame;
	if (fTime > 0.1f)
	{
		m_iAnimFrame++;
		fTime -= 0.1f;
		if (m_iAnimFrame >= m_rtList.size() ) m_iAnimFrame = 0;
	}
	TRect rt = { m_rtList[m_iAnimFrame].left,
		m_rtList[m_iAnimFrame].top,
		m_rtList[m_iAnimFrame].right,
		m_rtList[m_iAnimFrame].bottom };
	m_vVertexList[0].t = { rt.x / xSize,rt.y / ySize };
	m_vVertexList[1].t = { (rt.x + rt.w) / xSize,rt.y / ySize };
	m_vVertexList[2].t = { rt.x / xSize,(rt.y + rt.h) / ySize };
	m_vVertexList[3].t = { (rt.x + rt.w) / xSize,(rt.y + rt.h) / ySize };

	TDevice::m_pd3dContext->UpdateSubresource(
		m_pVertexBuffer, 0, nullptr,
		&m_vVertexList.at(0), 0, 0);
}
void TEffectObj::SetVertexData()
{
	TObject::SetVertexData();
	float xSize = 400;
	float ySize = 300;
	TRect rt = { m_rtList[0].left,
		m_rtList[0].top,
		m_rtList[0].right,
		m_rtList[0].bottom };
	m_vVertexList[0].t = { rt.x / xSize,rt.y / ySize };
	m_vVertexList[1].t = { (rt.x+rt.w) / xSize,rt.y / ySize };
	m_vVertexList[2].t = { rt.x / xSize,(rt.y +rt.h) / ySize };
	m_vVertexList[3].t = { (rt.x + rt.w) / xSize,(rt.y + rt.h) / ySize };
}