#include <iostream> // stdio.h

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

    for (int i = 0; i < 3; i++)
    {
        pChildList[i]->Draw();
    }
    for (int i = 0; i < 3; i++)
    {
        delete pChildList[i];
    }
}
