#include <iostream>
#include <string>
#include <vector>
class TComponent
{
public:
    std::wstring m_csName;
    // map, char, ui, sound, image
};

class TObject
{
public:
    std::wstring m_csName;
    // map, char, ui, sound, image
    virtual ~TObject() {}
};


class TDraw : public TComponent
{
public:
    virtual void Draw() = 0;
};
class TDrawUI : public TDraw
{
public:
    virtual void Draw() override {};
};
class TDrawInGame : public TDraw
{
public:
    virtual void Draw() override {};
};
class TMove : public TComponent 
{
public:
    virtual void  Action() =0;
};
class TMoveWalk : public TMove
{
public:
    virtual void  Action() override {}
};
class TMoveFly : public TMove
{
public:
    virtual void  Action() override {}
};

class TCharacter : public TObject
{
public:
    // 포함관계
    TDraw*       m_pDraw = nullptr;
    TMove*       m_pMove = nullptr;
    TCharacter( TDraw* d, TMove* m) : m_pDraw(d), m_pMove(m)
    {}
    virtual ~TCharacter() {}
};
class THero : public TCharacter
{
public:
    THero(TDraw* d, TMove* m) : TCharacter(d,m)
    {}
};
class TNpc : public TCharacter
{
public:
    TNpc(TDraw* d, TMove* m) : TCharacter(d, m)
    {}
};
class TUserInterface : public TObject
{
public:
    TDraw* m_pDraw = nullptr;    
    TUserInterface() 
    {}
};
int main()
{
    TCharacter  hero1(new TDrawInGame, new TMoveWalk);
    TCharacter  npc1(new TDrawInGame, new TMoveFly);
    TCharacter  ui1(new TDrawUI, nullptr);

    TObject* hero = new THero(new TDrawInGame, new TMoveWalk);
    TObject* npc  = new TNpc(new TDrawInGame, new TMoveFly);
    TObject* ui   = new TUserInterface();
    std::vector<TObject*>  m_GameObjects;
    m_GameObjects.emplace_back(hero);
    m_GameObjects.emplace_back(npc);
    m_GameObjects.emplace_back(ui);

    for (auto obj : m_GameObjects)
    {
       //TCharacter* draw = (TCharacter*)(obj);
       TCharacter* draw = dynamic_cast<TCharacter*>(obj);
       draw->m_pDraw->Draw();
    }
}
