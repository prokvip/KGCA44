#include "TSceneResult.h"
#include "TGame.h"
TSceneResult::TSceneResult(TGame* p) 
{
    m_pOwner = p;
}
TSceneResult::~TSceneResult() {}
void TSceneResult::ProcessAction(TObject* pObj)
{
    if (m_bSceneChange == true)
    {
        m_pOwner->SetTransition(TSceneEvent::EVENT_NEXT_SCENE);
        return;
    }
   /* if (m_bSceneChange == true)
    {
        m_pOwner->SetTransition(TSceneEvent::EVENT_PREV_SCENE);
        return;
    }*/
    Frame();
    Render();
}
void   TSceneResult::Init()
{
}
void   TSceneResult::Frame()
{
}
void   TSceneResult::Render()
{

}
void   TSceneResult::Release()
{

}