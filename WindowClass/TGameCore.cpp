#include "TGameCore.h"
bool TGameCore::GameRun()
{
    Init();
    while (m_bRun)
    {        
        if(!MessageProcess())
        {
            Frame();
            Render();
        }
    }	
	Release();
	return true;
}