#include "TGuiFSM.h"
#include "TControlGUI.h"
TGuiState::TGuiState(TControlGUI* p) : m_pOwner(p) {

}
TGuiState::~TGuiState() {}
TDefaultActionGui::TDefaultActionGui(TControlGUI* p) : TGuiState(p) {
	m_iEnemyState = 0;
}
TDefaultActionGui::~TDefaultActionGui() {}
THoverActionGui::THoverActionGui(TControlGUI* p) : TGuiState(p) {
	m_iEnemyState = 1;
}
THoverActionGui::~THoverActionGui() {}

TActiveActionGui::TActiveActionGui(TControlGUI* p) : TGuiState(p) {
	m_iEnemyState = 2;
}
TActiveActionGui::~TActiveActionGui() {}

void TDefaultActionGui::ProcessAction(TObject* pObj)
{
	m_pOwner->m_StateData[m_iEnemyState].m_fTimer -= g_fSPF;
	if (m_pOwner->m_StateData[m_iEnemyState].m_fTimer < 0.0f)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_PATROL);
	}
	m_pOwner->SetRotation(0);
}
void THoverActionGui::ProcessAction(TObject* pObj)
{
	// 공격범위 판단 -> 상태전이
	// 고격범위 탈출 -> 상태전이
	float fDistance = (pObj->m_vPos - m_pOwner->m_vPos).Length();
	if (fDistance < m_pOwner->m_StateData[m_iEnemyState].m_fDistance)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_FINDTARGET);
		return;
	}
	// v = v + d*s : 직선의 벡터의 방정식
	TVector2 vMove = m_pOwner->m_vPos +
		m_pOwner->m_vDir * (g_fSPF * m_pOwner->m_fSpeed);
	m_pOwner->SetPosition(vMove);
	m_pOwner->SetRotation(T_Pi);
}
void TActiveActionGui::ProcessAction(TObject* pObj)
{
	// 공격범위 판단 -> 상태전이
	// 고격범위 탈출 -> 상태전이
	m_pOwner->m_StateData[m_iEnemyState].m_fTimer -= g_fSPF;
	if (m_pOwner->m_StateData[m_iEnemyState].m_fTimer < 0.0f)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_STOP);
		return;
	}
	float fDistance = (pObj->m_vPos - m_pOwner->m_vPos).Length();
	if (fDistance > m_pOwner->m_StateData[m_iEnemyState].m_fDistance)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_LOSTTARGET);
		return;
	}

	TVector2 vDir = (pObj->m_vPos - m_pOwner->m_vPos);
	m_pOwner->m_vDir = vDir.Normal();
	TVector2 vMove = m_pOwner->m_vPos +
		m_pOwner->m_vDir * (g_fSPF * m_pOwner->m_fSpeed);
	m_pOwner->SetPosition(vMove);
	m_pOwner->SetRotation(g_fGT);
}
void TSelectedActionGui::ProcessAction(TObject* pObj)
{
	// 공격범위 판단 -> 상태전이
	// 고격범위 탈출 -> 상태전이
	m_pOwner->m_StateData[m_iEnemyState].m_fTimer -= g_fSPF;
	if (m_pOwner->m_StateData[m_iEnemyState].m_fTimer < 0.0f)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_STOP);
		return;
	}
	float fDistance = (pObj->m_vPos - m_pOwner->m_vPos).Length();
	if (fDistance > m_pOwner->m_StateData[m_iEnemyState].m_fDistance)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_LOSTTARGET);
		return;
	}

	TVector2 vDir = (pObj->m_vPos - m_pOwner->m_vPos);
	m_pOwner->m_vDir = vDir.Normal();
	TVector2 vMove = m_pOwner->m_vPos +
		m_pOwner->m_vDir * (g_fSPF * m_pOwner->m_fSpeed);
	m_pOwner->SetPosition(vMove);
	m_pOwner->SetRotation(g_fGT);
}


TSelectedActionGui::TSelectedActionGui(TControlGUI* p) : TGuiState(p) {
	m_iEnemyState = 0;
}
TSelectedActionGui::~TSelectedActionGui() {}