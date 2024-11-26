#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
    /*void operator= (const TCharacter& ch) = delete;
    TCharacter(const TCharacter& ch) = delete;
    TCharacter(const TCharacter* ch) = delete;*/
    /*void operator= (const TCharacter& ch)
    {
        this->m_csName = ch.m_csName;
    }
    void operator= (const TCharacter* ch)
    {
        this->m_csName = ch->m_csName;
    }*/
    /*TCharacter(const TCharacter& ch)
    {
        this->m_csName = ch.m_csName;
    }*/
    TCharacter( TDraw* d, TMove* m) : m_pDraw(d), m_pMove(m)
    {
    }
    TCharacter() = default;
    virtual ~TCharacter() {
        std::cout << " virtual ~TCharacter() {";
    }
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
    TCharacter pObj3;
    TCharacter pObj4 = pObj3;//Character::TCharacter(const TCharacter &)': 삭제된 함수를 참조하려고 합니다.
   // pObj4 = pObj3;//삭제된 함수를 참조하려고 합니다.



    TObject* pObj1 = new TCharacter();
    TObject* pObj2 = pObj1;
    delete pObj1;

    {
        // 공유 : 참조(레버런싱)
        auto obj = std::make_shared<TCharacter>();
        //std::shared_ptr<TCharacter> obj(new TCharacter);
        TCharacter* pChar = obj.get();
     }

    // std::shared_ptr
    {        
        std::shared_ptr<TCharacter> baseobj = nullptr;
        {
            // 공유 : 참조(레버런싱)
            std::shared_ptr<TCharacter> obj = std::make_shared<TCharacter>();
            TCharacter* pChar = obj.get();
            baseobj = obj;
        }
        std::shared_ptr<TCharacter> baseobj2 = baseobj;
        if (baseobj != nullptr)
        {
            std::wcout << baseobj->m_csName;
        }
    }

    // std::unique_ptr
    {
        TCharacter* pCopyPointer = nullptr;
        std::unique_ptr<TCharacter> baseobj = nullptr;
        {
            // 공유 : 참조(레버런싱)
            std::unique_ptr<TCharacter> obj = std::make_unique<TCharacter>();
            obj->m_csName = L"aa";

            TCharacter* pChar = obj.get();
            pCopyPointer = pChar;
            delete pCopyPointer;
            //baseobj = obj;
            baseobj = std::move(obj);
        }
        std::unique_ptr<TCharacter> baseobj2 = std::move(baseobj);
        if (baseobj != nullptr)
        {
            std::wcout << baseobj->m_csName;
        }
    }

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
       draw->m_pMove->Action();
    }
}
