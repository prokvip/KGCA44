#include "TGameCore.h"
void   TGameCore::CoreInit()
{
    m_DxDevice.Init();
    m_GameTimer.Init();
    m_Input.Init();
    Init();
}
void   TGameCore::CoreFrame() 
{     
    m_DxDevice.Frame();
    m_GameTimer.Frame();
    m_Input.Frame();
    Frame();
}
void   TGameCore::CoreRender() 
{
    m_DxDevice.Render();
    m_GameTimer.Render();
    m_Input.Render();
    Render();
    if (g_GameKey.dwExit == KEY_PUSH)
    {
        m_bRun = false;
    }
}
void   TGameCore::CoreRelease()
{
    m_GameTimer.Release();
    m_DxDevice.Release();
    m_Input.Release();
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