#include "TEnemyFSM.h"
#include "TNpcObj.h"
TEnemyState::TEnemyState(TNpcObj* p) : m_pOwner(p) {

}
TEnemyState::~TEnemyState() {}
TStandAction::TStandAction(TNpcObj* p) : TEnemyState(p) {
	m_iEnemyState = 0;
}
TStandAction::~TStandAction() {}
TMoveAction::TMoveAction(TNpcObj* p) : TEnemyState(p) {
	m_iEnemyState = 1;
}
TMoveAction::~TMoveAction() {}

TAttackAction::TAttackAction(TNpcObj* p) : TEnemyState(p) {
	m_iEnemyState = 2;
}
TAttackAction::~TAttackAction() {}

void TStandAction::ProcessAction(TObject* pObj)
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
void TMoveAction::ProcessAction(TObject* pObj)
{
	// ���ݹ��� �Ǵ� -> ��������
	// ���ݹ��� Ż�� -> ��������
	float fDistance = (pObj->m_vPos - m_pOwner->m_vPos).Length();
	if (fDistance < m_pOwner->m_StateData[m_iEnemyState].m_fDistance)
	{
		m_pOwner->m_StateData[m_iEnemyState].m_fTimer =
			m_pOwner->m_StateData[m_iEnemyState].m_fDefaultTimer;
		m_pOwner->SetTransition(T_ActionEvent::EVENT_FINDTARGET);
		return;
	}
	// v = v + d*s : ������ ������ ������
	TVector2 vMove = m_pOwner->m_vPos +
		m_pOwner->m_vDir * (g_fSPF * m_pOwner->m_fSpeed);
	m_pOwner->SetPosition(vMove);
	m_pOwner->SetRotation(T_Pi);
}
void TAttackAction::ProcessAction(TObject* pObj)
{
	// ���ݹ��� �Ǵ� -> ��������
	// ���ݹ��� Ż�� -> ��������
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