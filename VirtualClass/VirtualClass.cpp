﻿#include <iostream> // stdio.h

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
int main()
{
   

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