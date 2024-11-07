#include <iostream> // stdio.h
struct TItem
{
    int iData;
    friend std::ostream& operator << (std::ostream& os, TItem& a);
};
std::ostream& operator << (std::ostream& os, TItem& a)
{
    return os;
}
template <class T>
class TItemMgr
{
public:
};
template <class T>
class TManager
{
public:
    TItemMgr<T> list;
public:
    //friend std::ostream&  operator << (std::ostream& os, TManager<T>& a);
    friend std::ostream&  operator << (std::ostream& os, TItemMgr<T>& a);
};
//error LNK2019: "void __cdecl operator<<(int,class TManager<int> &)" (??6@YAXHAEAV?$TManager@H@@@Z)main 함수에서 참조되는 확인할 수 없는 외부 기호
//template <class T>
//std::ostream& operator << (std::ostream& os, TManager<T>& a)
//{
//    return os;
//}
template <class T>
std::ostream& operator << (std::ostream& os, TItemMgr<T>& a)
{
    return os;
}
class AMgr
{
public:    
    TManager<int> list;
    friend std::ostream& operator << (std::ostream& os, AMgr& a);
    friend std::ostream& operator << (std::ostream& os, TManager<int>& a);
};
std::ostream& operator << (std::ostream& os, AMgr& a)
{
    return os;
}
std::ostream& operator << (std::ostream& os, TManager<int>& a)
{
    return os;
}
class Parent
{
public :
    int  iValueB = 20;
    int  iValueA = 10;    
    virtual void    Draw()
    {
        std::cout << "Parent!\n";
    }
    // vTable 포인터 =  Draw : 0xfff00000
     virtual ~Parent()
    {
        std::cout << "Parent 해제자!\n";
    }
};
class Child1 : public Parent
{
public:
    int jValue;
    // 가상테이블의 주소가 변경된다.
    void    Draw() {
        std::cout << "Child1!\n";
    }
    ~Child1()
    {
        std::cout << "Child1 해제자!\n";
    }
};
class Child2 : public Parent
{
public:
    int jValue;
    // 가상테이블의 주소가 변경된다.
    void    Draw() {
        std::cout << "Child2!\n";
    }
    ~Child2()
    {
        std::cout << "Child2 해제자!\n";
    }
};
class Child3 
{
public:
    int jValue;
    // 가상테이블의 주소가 변경된다.
    void    Draw() {
        std::cout << "Child2!\n";
    }
    ~Child3()
    {
        std::cout << "Child2 해제자!\n";
    }
};
const int Fun1()
{
    const int ret = 3;
    return ret;
}

int ret = 3;
const int& Fun2()
{    
    return ret;
}
int main()
{
    int& i =const_cast<int&>(Fun2());
    const int& j = Fun2();
    int& k = const_cast<int&>(j);

    AMgr mgr;
    std::cout << mgr;

    TItem* a = reinterpret_cast<TItem*>(&mgr);
    //
    TItem item;
    std::cout << item;

    TManager<TItem>  tmgr;
    //std::cout << tmgr;
    std::cout << mgr.list;

    std::cout << tmgr.list;
    

    //Parent* p = new Parent;   //Parent pParent;
    //char* i = (char*)p;

    //void* pointArray[10];
    //int* iValueA = (int*)&i[8];
    //for (int j = 0; j < 10; j++)
    //{
    //    pointArray[j] = &i[j];
    //}
    //
    //int* iV = (int*)(i += 8);
    //int* i = (int*)&p;

    Parent* pChildList[3] = { 0, };
    int iParentSize = sizeof(Parent);
    int iChildSize = sizeof(Child1);
    //error C2259: 'Parent': 추상 클래스를 인스턴스화할 수 없습니다.
    pChildList[0] = new Parent;   //Parent pParent;
    //error C2259: 'Child': 추상 클래스를 인스턴스화할 수 없습니다.
    pChildList[1] = new Child1;
    pChildList[2] = new Child2;

    // 안전하다.
    Child2* pData1 = (Child2*)pChildList[2];   //new Child2;
    std::cout << pData1->iValueB << std::endl;
    std::cout << pData1->jValue << std::endl;

    Child3* pChild3 = new Child3;
    //error C2440: '초기화 중': 'Child3 *'에서 'Child2 *'(으)로 변환할 수 없습니다.
   // Child2* pDataChild10 = static_cast<Child3*>(pChild3);   //new Parent;
    //Child2* pDataChild11 = dynamic_cast<Child3*>(pChild3);   //new Parent;
    // 컴파일 타임에서 캐스팅 여부를 판단한다.
    Child2* pDataChild1 = static_cast<Child2*>(pChildList[2]);   //new Parent;
    if (pDataChild1 != nullptr)
    {
        std::cout << pDataChild1->iValueB << std::endl;
        std::cout << pDataChild1->jValue << std::endl;
    }

    Child2* pDataChild2 = dynamic_cast<Child2*>(pChildList[2]);   //new Parent;
    if (pDataChild2 != nullptr)
    {
        std::cout << pDataChild2->iValueB << std::endl;
        std::cout << pDataChild2->jValue << std::endl;
    }
    // 불안전하다.
    Child2* pData2 = (Child2*)pChildList[0];   //new Parent;
    std::cout << pData2->iValueB << std::endl;
    std::cout << pData2->jValue << std::endl;

    Child2* pDataChild3 = static_cast<Child2*>(pChildList[2]);   //new Parent;
    if (pDataChild3 != nullptr)
    {
        std::cout << pDataChild3->iValueB << std::endl;
        std::cout << pDataChild3->jValue << std::endl;
    }

    // 런타임에서 캐스팅 여부를 판단할 수 있다.
    Child2* pData3 = dynamic_cast<Child2*>(pChildList[0]);   //new Parent;
    if (pData3 != nullptr)
    {
        std::cout << pData3->iValueB << std::endl;
        std::cout << pData3->jValue << std::endl;
    }

    for (int i = 0; i < 3; i++)
    {
        pChildList[i]->Draw();
    }
    for (int i = 0; i < 3; i++)
    {
        delete pChildList[i];
    }
}
