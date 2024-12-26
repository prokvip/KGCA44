#include "THeroObj.h"
#include "TDevice.h"
void THeroObj::UpdateScale(float sx, float sy)
{
	//float sx = (cosf(g_fGT) * 0.5f + 0.5f) * 1000.0f;
	//float sy = (cosf(g_fGT) * 0.5f + 0.5f) * 1000.0f;
	static TVector2 m_vScale = { (m_srtScreen.w / 2.0f),(m_srtScreen.h / 2.0f) };
	m_matScale.Scale(m_vScale.x +sx , m_vScale.y + sy );
}
void THeroObj::UpdateRotation(float fRadian)
{
	m_fAngleRadian = fRadian;
	m_matRotate.Rotate(m_fAngleRadian);
}
void THeroObj::UpdatePosition()
{
	//m_matTrans.Trans(m_vPos);
	/*float fTimerSclase = (cosf(g_fGT) * 0.5f + 0.5f) * 1000.0f;
	m_matScale.Scale((m_srtScreen.w/2.0f)+ fTimerSclase,
					 (m_srtScreen.h/2.0f)+ fTimerSclase);
	m_matRotate.Rotate(g_fGT);*/

	m_matWorld = m_matScale * m_matRotate * m_matTrans;
	for (int i = 0; i < 4; i++)
	{		
		m_vScreenList[i] =
			m_pMeshRender->m_vScreenList[i] * 
			m_matWorld;
	}
	//m_srtScreen.SetP(m_vScreenList[0], m_vScreenList[3]);
	////m_srtScreen.SetS(m_vPos, { m_srtScreen.w, m_srtScreen.h });
	//m_Sphere.vCenter = m_srtScreen.tCenter;
	//m_Sphere.fRadius = m_srtScreen.fRadius;
}
void THeroObj::Frame()
{
	// *시간의 동기화
	// 1000 frame = 1초 동안에 100이동하자.
				// 100 * 0.001f;
	// 100 frame  = 1초 동안에 100이동하자.
				// 100 * 0.01f;
	// 10 frame  = 1초 동안에 100이동하자.
				// 100 * 0.1f;
	TVector2 vAdd;
	if (g_GameKey.dwWkey == KEY_HOLD)
	{
		vAdd.y = -m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwSkey == KEY_HOLD)
	{
		vAdd.y = m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwAkey == KEY_HOLD)
	{
		vAdd.x = -m_fSpeed * g_fSPF;
	}
	if (g_GameKey.dwDkey == KEY_HOLD)
	{
		vAdd.x = m_fSpeed * g_fSPF;
	}

	AddPosition(vAdd);
	UpdateScale(cosf(g_fGT)*10.0f, cosf(g_fGT)*10.0f);
	UpdateRotation(g_fGT);
	UpdatePosition();
}
void THeroObj::AddPosition(float x, float y)
{
	m_vPos.x += x;
	m_vPos.y += y;
	m_matTrans._31 = m_vPos.x;
	m_matTrans._32 = m_vPos.y;
}
void THeroObj::AddPosition(TVector2 v)
{
	AddPosition(v.x, v.y);
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