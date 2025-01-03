#include "THeroObj.h"
#include "TDevice.h"
void    THeroObj::HitOverlap(TObject* pObj, THitResult hRes)
{
	
};
void THeroObj::Init()
{
	TObject2D::Init();
	m_pProjectile = std::make_shared<TProjectile>(m_pWorld);
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

	if (g_GameKey.dwLeftClick == KEY_PUSH)
	{
		TVector2 vHalf = { 50.0f, 50.0f };
		TVector2 vStart = m_vPos - vHalf;
		TVector2 vEnd = m_vPos + vHalf;
		m_pProjectile->AddEffect(vStart, vEnd);
	}
	m_pProjectile->Frame(m_vPos);
}
void THeroObj::Render()
{
	TObject2D::Render();
	m_pProjectile->Render(m_vCamera);
}
void THeroObj::Release ()
{
	TObject2D::Release();
	m_pProjectile->Release();
}
void THeroObj::SetVertexData()
{
	if (m_pTexture == nullptr) return;
	float xSize = m_pTexture->m_TexDesc.Width;
	float ySize = m_pTexture->m_TexDesc.Height;
	TRect rt;
	rt.SetP(90.0f, 1.0f, 132.0f, 61.0f );
	m_vVertexList[0].t = { rt.v1.x / xSize,rt.v1.y / ySize };
	m_vVertexList[1].t = { rt.v2.x / xSize,rt.v1.y / ySize };
	m_vVertexList[2].t = { rt.v1.x / xSize,rt.v2.y / ySize };
	m_vVertexList[3].t = { rt.v2.x / xSize,rt.v2.y / ySize };	
}