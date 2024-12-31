#pragma once
#include "TObject2D.h"
#include "TFiniteState.h"
class TControlGUI;
class TGuiState
{
public:
	UINT   m_iState = 0;
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
	TDefaultActionGui(TControlGUI* p) ;
	TDefaultActionGui() { m_iState = TSelectState::T_DEFAULT; };
	virtual ~TDefaultActionGui();
};
class THoverActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	THoverActionGui(TControlGUI* p);
	THoverActionGui() { m_iState = TSelectState::T_HOVER; };
	virtual ~THoverActionGui();
};
class TActiveActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TActiveActionGui(TControlGUI* p);
	TActiveActionGui() { m_iState = TSelectState::T_ACTIVE; };
	virtual ~TActiveActionGui();
};
class TSelectedActionGui : public TGuiState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TSelectedActionGui(TControlGUI* p);
	TSelectedActionGui() { m_iState = TSelectState::T_SELECTED; };
	virtual ~TSelectedActionGui();
};


