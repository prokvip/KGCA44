#include "TGameCore.h"

void   TGameCore::CoreInit()
{  
    Init();
}
void   TGameCore::CoreFrame() 
{   
    PreFrame();
    Frame();
    PostFrame();
}
void   TGameCore::CoreRender() 
{
    PreRender();    
    Render();
    PostRender();
}
void   TGameCore::CoreRelease()
{ 
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