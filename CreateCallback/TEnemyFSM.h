#pragma once
#include "TMapObj.h"
#include "TFiniteState.h"
class TNpcObj;
class TEnemyState
{
public:
	UINT   m_iEnemyState;
	TEnemyState(TNpcObj* p);
	TEnemyState() {};
	virtual ~TEnemyState();
public:
	virtual void ProcessAction(TObject* pObj) = 0;
public:
	TNpcObj* m_pOwner;
};
class TStandAction : public TEnemyState
{
public:
	virtual void ProcessAction(TObject* pObj);
public:
	TStandAction(TNpcObj* p);
	TStandAction() { m_iEnemyState = STATE_STAND; };
	virtual ~TStandAction();
};
class TMoveAction : public TEnemyState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TMoveAction(TNpcObj* p);
	TMoveAction() { m_iEnemyState = STATE_MOVE; };
	virtual ~TMoveAction();
};
class TAttackAction : public TEnemyState
{
public:
	virtual void ProcessAction(TObject* pObj);
	TAttackAction(TNpcObj* p);
	TAttackAction() { m_iEnemyState = STATE_ATTACK; };
	virtual ~TAttackAction();
};


