#pragma once
#include "TObject2D.h"
#include "TFiniteState.h"
class TControlGUI;
class TGuiState
{
public:
	UINT   m_iEnemyState;
	TGuiState(TControlGUI* p);
	TGuiState() {};
	virtual ~TGuiState();
public:
	virtual void ProcessAction(TObject* pObj) = 0;
public:
	TControlGUI* m_pOwner;
};
class TDefaultActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
public:
	TDefaultActionGui(TControlGUI* p);
	TDefaultActionGui() { m_iEnemyState = STATE_STAND; };
	virtual ~TDefaultActionGui();
};
class THoverActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	THoverActionGui(TControlGUI* p);
	THoverActionGui() { m_iEnemyState = STATE_MOVE; };
	virtual ~THoverActionGui();
};
class TActiveActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TActiveActionGui(TControlGUI* p);
	TActiveActionGui() { m_iEnemyState = STATE_ATTACK; };
	virtual ~TActiveActionGui();
};
class TSelectedActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TSelectedActionGui(TControlGUI* p);
	TSelectedActionGui() { m_iEnemyState = STATE_ATTACK; };
	virtual ~TSelectedActionGui();
};


