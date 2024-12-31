#include "TControlGUI.h"
#include "TDevice.h"

std::vector<std::shared_ptr<TGuiState>> TControlGUI::m_pActionList;

void    TControlGUI::HitOverlap(TObject* pObj, THitResult hRet)
{
	//m_bDead = true;
};
bool	TControlGUI::Create(TWorld* pWorld, TLoadResData data,
	TVector2 s,
	TVector2 e)
{
	m_LoadResData = data;
	m_rtScreen.SetP(s, e);
	SetScale(m_rtScreen.vh.x, m_rtScreen.vh.y);
	SetRotation(m_fAngleRadian);
	SetPosition(m_rtScreen.vc);

	m_vVertexList.resize(4);
	m_vScreenList.resize(4);

	if (!LoadTexture(m_LoadResData.texPathName))
	{
		return false;
	}
	return TObject2D::Create(pWorld);
}
void TControlGUI::Frame()
{	
}
void TControlGUI::SetVertexData()
{
	if (m_pTexture == nullptr) return;
	TObject2D::SetVertexData();
	float xSize = m_pTexture->m_TexDesc.Width;
	float ySize = m_pTexture->m_TexDesc.Height;

	m_vVertexList = m_pMeshRender->m_vVertexList;
	/*TRect rt;
	rt.SetP(90.0f, 1.0f, 132.0f, 61.0f);
	m_vVertexList[0].t = { rt.v1.x / xSize,rt.v1.y / ySize };
	m_vVertexList[1].t = { rt.v2.x / xSize,rt.v1.y / ySize };
	m_vVertexList[2].t = { rt.v1.x / xSize,rt.v2.y / ySize };
	m_vVertexList[3].t = { rt.v2.x / xSize,rt.v2.y / ySize };*/
}
void	TControlGUI::Transform(TVector2 vCamera)
{
	TObject::Transform(vCamera);
	TransformNDC();
	TDevice::m_pd3dContext->UpdateSubresource(
		m_pMeshRender->m_pVertexBuffer.Get(), 0, nullptr,
		&m_vVertexList.at(0), 0, 0);
}
void TControlGUI::SetScale(float sx, float sy)
{
	m_vScale.x = sx;
	m_vScale.y = sy;
	m_matScale.Scale(m_vScale);
	m_rtScreen.Size(m_vScale * 2.0f);
	m_Sphere.vCenter = m_rtScreen.vc;
	m_Sphere.fRadius = m_rtScreen.fR;

	m_vPos = m_rtScreen.vc;
	m_matTrans.Trans(m_vPos);
}
void    TControlGUI::TransformNDC()
{
	for (UINT i = 0; i < m_vVertexList.size(); i++)
	{
		TVector2 ndc = ScreenToNDC(
			m_vScreenList[i].x,
			m_vScreenList[i].y, g_ptClientSize);
		m_vVertexList[i].v = ndc;
	}
}
void TControlGUI::SetFSM(TFiniteStateMachine* pFsm)
{
	m_pFsm = pFsm;
	//m_StateData.resize(T_ActionState::STATE_COUNT);
	//m_StateData[T_ActionState::STATE_STAND].m_fTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_STAND].m_fDefaultTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_STAND].m_fDistance = 100.0f;
	//m_StateData[T_ActionState::STATE_MOVE].m_fTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_MOVE].m_fDefaultTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_MOVE].m_fDistance = 100.0f;
	//m_StateData[T_ActionState::STATE_ATTACK].m_fTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_ATTACK].m_fDefaultTimer = 3.0f;
	//m_StateData[T_ActionState::STATE_ATTACK].m_fDistance = 100.0f;
	//m_pAction = m_pActionList[0].get();
}
void TControlGUI::StartFSM()
{
	if (m_pActionList.size()) return;
	//std::shared_ptr<TEnemyState> stand =
	//	std::make_shared<TStandAction>();
	//std::shared_ptr<TEnemyState> move =
	//	std::make_shared<TMoveAction>();
	//std::shared_ptr<TEnemyState> attack =
	//	std::make_shared<TAttackAction>();
	//m_pActionList.emplace_back(stand);
	//m_pActionList.emplace_back(move);
	//m_pActionList.emplace_back(attack);
}
void TControlGUI::SetTransition(UINT iEvent)
{
	_ASSERT(m_pFsm);
	UINT iOutput = m_pFsm->GetOutputState(
		m_pAction->m_iEnemyState, iEvent);
	m_pAction = m_pActionList[iOutput].get();
}
void TControlGUI::FrameState(TObject* pHero)
{
	m_pAction->m_pOwner = this;
	m_pAction->ProcessAction(pHero);
}