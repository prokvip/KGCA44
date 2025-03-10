#include "TGameCore.h"
void   TGameCore::CoreInit()
{
    m_GameTimer.Init();
    Init();
}
void   TGameCore::CoreFrame() 
{
    m_GameTimer.Frame();
    Frame();
}
void   TGameCore::CoreRender() 
{
    m_GameTimer.Render();
    Render();
}
void   TGameCore::CoreRelease()
{
    m_GameTimer.Release();
    Release();
}
bool TGameCore::GameRun()
{
    CoreInit();
    while (m_bRun)
    {        
        if(!MessageProcess())
        {
            CoreFrame();
            CoreRender();
        }
        Sleep(100);
    }	
    CoreRelease();
	return true;
}