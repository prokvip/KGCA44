#pragma once
#include "TStd.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")
class TSound
{
public:
	FMOD::System*  m_pSystem = nullptr;
	FMOD::Sound*   m_pSound = nullptr;
	FMOD::Channel* m_pChannel = nullptr;

	float  m_fVolume = 0.5f;
	std::wstring  m_csBuffer;
public:
	void	Play(bool bLoop = true);
	void	PlayEffect(bool bLoop = false);
	void	Stop();
	void	Paused();
	void	VolumeUp(float fVolume);
	void	VolumeDown(float fVolume);
public:
	virtual bool		Load(std::wstring filename);
	virtual void		Init();
	virtual void		Frame();
	virtual void		Render();
	virtual void		Release();
};

