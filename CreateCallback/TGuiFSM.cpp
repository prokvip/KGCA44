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
	if (m_pOwner->m_iSelectState == TSelectState::T_HOVER)
	{
		m_pOwner->SetTransition(T_SelectEvent::EVENT_SELECT);
		return;
	}
}
void THoverActionGui::ProcessAction(TObject* pObj)
{
	if (m_pOwner->m_iSelectState == TSelectState::T_DEFAULT)
	{
		m_pOwner->SetScale(
			m_pOwner->m_StateData[T_SelectEvent::EVENT_DEFAULT].
			vDefaultScale.x,
			m_pOwner->m_StateData[T_SelectEvent::EVENT_DEFAULT].
			vDefaultScale.y);
		m_pOwner->SetTransition(T_SelectEvent::EVENT_DEFAULT);
		return;
	}
	float fAngle = m_pOwner->m_StateData[T_SelectEvent::EVENT_SELECT].
		vDefaultScale.y + 5.0f;
	m_pOwner->SetScale(m_pOwner->m_vScale.x, fAngle);
}
void TActiveActionGui::ProcessAction(TObject* pObj)
{
	m_pOwner->SetRotation(g_fGT);
}
void TSelectedActionGui::ProcessAction(TObject* pObj)
{	
	m_pOwner->SetRotation(g_fGT);
}


TSelectedActionGui::TSelectedActionGui(TControlGUI* p) : TGuiState(p) {
	m_iEnemyState = 0;
}
TSelectedActionGui::~TSelectedActionGui() {}