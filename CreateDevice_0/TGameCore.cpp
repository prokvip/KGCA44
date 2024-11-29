#include "TGameCore.h"
void   TGameCore::CoreInit()
{
    m_DxDevice.Init();
    m_GameTimer.Init();
    Init();
}
void   TGameCore::CoreFrame() 
{    
    m_DxDevice.Frame();
    m_GameTimer.Frame();
    Frame();
}
void   TGameCore::CoreRender() 
{
    m_DxDevice.Render();
    m_GameTimer.Render();
    Render();
}
void   TGameCore::CoreRelease()
{
    m_GameTimer.Release();
    m_DxDevice.Release();
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
    }	
    CoreRelease();
	return true;
}