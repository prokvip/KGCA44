#pragma once
#include "TWindow.h"
class TGameCore : public TWindow
{	
public:
public:
	virtual void   Init() {};
	virtual void   PreFrame() {};
	virtual void   Frame() {};
	virtual void   PostFrame() {};
	virtual void   PreRender() {};
	virtual void   Render() {};
	virtual void   PostRender() {};
	virtual void   Release() {};
public:
	void   CoreInit();
	void   CoreFrame();
	void   CoreRender();
	void   CoreRelease();
	virtual bool   GameRun();
};

