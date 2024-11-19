
#include <iostream>
#include <vector>
// 재할당 되는 배열
// 1) 연속적인 메모리를 할당한다.
// 2) 할당된 메모리 뒤로 할당하려고 하지만 
// // 뒤에 메모리가 부족하면 
// 3) 다른 곳으로 이동(메모리 할당해서)한다.
struct TData
{
    int iData;
    TData(const TData& c)
    {
        iData = c.iData;
        std::cout << "copy" << iData <<  std::endl;
    }
    TData& operator =(const TData& a)
    {
        iData = a.iData;
        std::cout << "=" << iData << std::endl;
        return *this;
    }
    TData( TData&& c)
    {
        iData = c.iData;
        std::cout << "Move" << iData << std::endl;
    }
    TData()
    {
        iData = -1;
    }
    TData(int i) : iData(i) {
        std::cout << "TData" << iData << std::endl;
    }
    ~TData()
    {
        std::cout << "~TData" << iData << std::endl;
    }
};
int main()
{
    std::vector<TData> vecList12;
    vecList12.reserve(10);
    vecList12.emplace_back(1);
    vecList12.emplace_back(2);
    vecList12.emplace_back(3);
    vecList12.emplace_back(4);
    vecList12.emplace(vecList12.begin(),5);

    std::vector<TData> vecList13 = vecList12;
    std::vector<TData> vecList14(vecList12);
    std::vector<TData> vecList15;
    vecList15 = vecList12;

    std::vector<TData> vecList11;
    vecList11.emplace_back(1);
    vecList11.emplace_back(TData(1));
   

    std::vector<TData> vecList10;
    vecList10.push_back(TData(1));

    std::vector<TData> vecList9;
    vecList9.emplace_back(TData(1));
    vecList9.emplace_back(TData(2));
    // TNode
    std::vector<TData>::iterator iter9;
    for (iter9 = vecList9.begin();
        iter9 != vecList9.end();
        )
    {
        iter9 = vecList9.erase(iter9);
    }

    std::vector<TData> vecList8;
    vecList8.emplace_back(TData(1));
    vecList8.emplace_back(TData(2));
    // TNode
    std::vector<TData>::iterator iter;
    for (iter = vecList8.begin();
        iter != vecList8.end();
        iter++)
    {
        std::cout << iter->iData;
    }
    vecList8.erase(vecList8.begin());
    int iSize = vecList8.size();

    std::vector<TData*> vecList7;
    for (int i = 0; i < 5; i++)
    {
        vecList7.push_back(new TData(i));
        std::cout << "capacity=" << vecList7.capacity() << std::endl;
    }
    for (int i = 0; i < vecList7.size(); i++)
    {
        delete vecList7[i];
    }
    std::cout << "size=" << vecList7.size();
    vecList7.clear();

    std::vector<int> vecList6;
    vecList6.assign(30, 1);
    for (int i = 0; i < 30; i++)
    {
        vecList6[i] = i;
        vecList6.push_back(i);
        std::cout << "capacity=" << vecList6.capacity() << std::endl;
    }
    std::cout << "size=" << vecList6.size();
    vecList6.clear();

    std::vector<int> vecList5(30, 1);
    for (int i = 0; i < 30; i++)
    {
        vecList5[i] = i;
        vecList5.push_back(i);
        std::cout << "capacity=" << vecList5.capacity() << std::endl;
    }
    std::cout << "size=" << vecList5.size();

    std::vector<int> vecList4(30);    
    for (int i = 0; i < 30; i++)
    {
        vecList4[i] = i;
        vecList4.push_back(i);
        std::cout << "capacity=" << vecList4.capacity() << std::endl;
    }
    std::cout << "size=" << vecList4.size();

    std::vector<int> vecList3;
    vecList3.reserve(10);// 예약
    for (int i = 0; i < 30; i++)
    {
        vecList3[i] = i;
        vecList3.push_back(i);
        std::cout << "capacity=" << vecList3.capacity() << std::endl;
    }
    std::cout << "size=" << vecList3.size();

    std::vector<int> vecList1;
    for (int i = 0; i < 30; i++)
    {
        vecList1.push_back(i);
        std::cout << "capacity=" << vecList1.capacity() << std::endl;
    }
    std::cout << "size=" << vecList1.size();

    std::vector<int> vecList2;
    vecList2.resize(10);// array[10]
    for (int i = 0; i < 10; i++)
    {
        vecList2[i] = i;
    }
    vecList2.push_back(99);
    std::cout << "size=" << vecList2.size();
    
}
