#pragma once
#include "THost.h"
class TSelectModel
{
public:
	SOCKET		m_Sock;
public:
	virtual bool  Init() = 0;
	virtual bool  Run() = 0;
};

class TAsyncSelect : public TSelectModel
{
public:
	virtual bool  Init() { return true; }
	virtual bool  Run() { return true; }
};

class TStdSelect : public TSelectModel
{
public:
	virtual bool  Init() { return true; }
	virtual bool  Run() { return true; }
};

class TEventSelect : public TSelectModel
{
	std::vector<WSAEVENT>  m_EventArray;
public:
	virtual bool  Init();
	virtual bool  Run();
};
