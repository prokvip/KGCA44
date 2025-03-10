#pragma once
#include "TWindow.h"
#include "TTime.h"
#include "TInput.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
class TGameCore : public TWindow
{	
	TTime		m_GameTimer;
	TInput		m_Input;
public:
	virtual void   Init() {};
	virtual void   Frame() {};
	virtual void   Render() {};
	virtual void   Release() {};
public:
	void   CoreInit();
	void   CoreFrame();
	void   CoreRender();
	void   CoreRelease();
	virtual bool   GameRun();
};

