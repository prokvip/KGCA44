
#include <iostream>
#include <vector>
#include <algorithm>
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
    std::vector<int> vecList20(10);
    for (int i = 0; i < 10; i++)
    {
        vecList20[i] = rand() % 100;   
    }
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    std::sort(vecList20.begin(), vecList20.end(), std::less<>());
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    std::sort(vecList20.begin(), vecList20.end(), std::greater<>());
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    auto iFindIter = std::find(vecList20.begin(), vecList20.end(), 14);
    if (iFindIter != vecList20.end())
    {
        std::cout << *iFindIter << " ";
    }

    std::vector<TData> vecList12;
    vecList12.reserve(10);
    vecList12.emplace_back(1);
    vecList12.emplace_back(2);
    vecList12.emplace_back(3);
    vecList12.emplace_back(4);
    vecList12.emplace(vecList12.begin(),5);
    vecList12.insert(vecList12.end(), 6);


    

    std::vector<TData> vecList19(vecList12.begin(), vecList12.end());
    std::vector<TData> vecList18(1);
    //vecList18.assign(vecList12.begin(), vecList12.end());
    vecList12.swap(vecList18);

    for (auto data : vecList12)
    {
        data.iData = 10;
        std::cout << data.iData << " ";
    }
    for (auto data : vecList12)
    {
        std::cout << data.iData << " ";
    }
    /*for (auto& data : vecList12)
    {
        data.iData = 9;
        std::cout << data.iData << " ";
    }*/
    for (auto data : vecList12)
    {
        std::cout << data.iData << " ";
    }


    std::vector<TData> vecList16 = vecList12;
    auto vecList17 = vecList16;
    auto h = 3;
    auto f = 3.14;
    auto s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    char ss[] = "dddddddddd";
    std::cout << h << f << s;

    vecList12.pop_back();
    TData& data = vecList12.at(1);
    TData& pFront = vecList12.front();
    TData& pBack  = vecList12.back();
    // 배열의 시작주소 반환
    TData* datapointer = &vecList12.at(0);
    TData* pDataPointer = vecList12.data();
    pDataPointer++;
    std::cout << (pDataPointer)->iData << " ";
    pDataPointer++;
    std::cout << (pDataPointer)->iData << " ";
    //std::vector<TData>::reverse_iterator iter12;
    for (auto iter = vecList12.rbegin();
        iter != vecList12.rend();
        iter++)
    {
        std::cout << iter->iData << " ";
    }
    const int j = 3;
    int k = j;
    std::vector<TData>::const_iterator citer12;
    for (citer12 = vecList12.begin();
        citer12 != vecList12.end();
        citer12++)
    {
        std::cout << citer12->iData << " ";
    }
    
    std::vector<TData>::iterator iter120 = vecList12.begin();
    std::cout << (iter120++)->iData << " ";
    std::cout << (iter120--)->iData << " ";
    std::cout << (iter120)->iData << " ";

    while (!vecList12.empty())
    {
        vecList12.erase(vecList12.begin());
        // error
        //vecList12.erase(vecList12.end());
    }

    // 배열의 시작 주소
    TData* pData = &vecList12.at(0);
    

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
        //vecList8.emplace_back(3);
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
