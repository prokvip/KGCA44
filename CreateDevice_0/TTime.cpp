#include "TTime.h"
#include <windows.h>
void    TTime::Init()
{   
    m_StartClock = std::clock();
    m_EndClock = std::clock();
    m_fTmpTimer = 0.0f;
}
void    TTime::Frame()
{
    m_iGameFrame++;
	m_EndClock = std::clock();         
    m_fSecondPerFrame = (m_EndClock - m_StartClock) / (double)CLOCKS_PER_SEC;
    m_fGameTimer += m_fSecondPerFrame;
    m_fTmpTimer += m_fSecondPerFrame;    
    if (m_fTmpTimer > 1.0)
    {
#ifdef _DEBUG
        m_szTime = std::to_wstring(m_fGameTimer);
        m_szTime += L" ";
        m_szTime += std::to_wstring(m_fSecondPerFrame);
        m_szTime += L" ";
        m_szTime += std::to_wstring(m_iGameFrame);
        m_szTime += L"\n";        
#endif
        m_fTmpTimer -= 1.0;
        m_iGameFrame = 0;
    }
    m_StartClock= m_EndClock;
}
void    TTime::Render()
{
#ifdef _DEBUG
    OutputDebugString(m_szTime.c_str());
#endif
}
void    TTime::Release()
{

}