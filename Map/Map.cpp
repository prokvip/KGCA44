//#define  _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <iostream>
#include <map>
#include <unordered_map>
//#include <hash_map>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <algorithm>
class TData
{
public:
    int   iValue = 0;
    TData(int k) : iValue(k) {}
};

int main()
{
    std::setlocale(LC_ALL, "");
    /*std::hash_map<std::wstring, int >    listHash;
    listHash.insert(std::make_pair(L"홍1", 4));
    listHash.insert(std::make_pair(L"홍2", 4));
    for (int i = 0; i < listHash.size(); i++)
    {
        std::wcout << listHash.at(L"홍1");
    }*/
    std::unordered_map<std::wstring, int >    listUnorder;

    std::map<std::wstring, int, 
        std::greater<std::wstring>>     mapList;
    mapList.insert(std::make_pair(L"홍1", 2));
    mapList.insert(std::make_pair(L"홍2", 1));


    std::unordered_map<std::wstring, int>     list44;
   
    list44.insert(std::make_pair(L"홍1", 1));
    list44.insert(std::make_pair(L"홍1", 2));
    std::cout << list44.bucket_count() << " 버킷 개수 ";
    std::cout << list44.bucket(L"홍1") << "키 값에 대한 버킷 번호";
    std::cout << list44.bucket_size(list44.bucket(L"홍1")) << "버킷크기";

    std::unordered_multimap<std::wstring, int>     listUnorderMulti;
    listUnorderMulti.insert(std::make_pair(L"홍1", 1));
    listUnorderMulti.insert(std::make_pair(L"홍1", 2));

    std::multimap<std::wstring, int>     listMul;
    listMul.insert(std::make_pair(L"홍1", 1));
    listMul.insert(std::make_pair(L"홍1", 2));

    // std::pair<키(중복되면 않된다.), 값> 구성된다.
    // std::map은 대규모 조회, 검색  BST , HASH
    // 추가하는 순서로 순회되지 않는다.
    // 인덱싱 지원( vector ) 
    //std::map<int, int>              list;
    std::map<std::wstring, int>     list;
    /*std::map<std::wstring, TData>   list;
    std::map<int, TData>            list;
    std::map<int, TData*>           list;*/

    // 주의 : 추가의 용도로는 사용하지 말자
    //        검색의 용도로는 상관없다.(인덱싱)
  /*  list[L"홍1"] = 99;
    list[L"홍1"] = 55;
    list[L"홍2"] = 88;
    list[L"홍3"] = 77;*/
    std::pair<std::wstring, int> inData;
    inData.first = L"홍3";
    inData.second = 3;
    list.insert(inData);
    list.insert(std::make_pair(L"홍1", 1));
    list.insert(std::make_pair(L"홍2", 2));
    
    for (int i = 0; i < 100; i++)
    {
        std::wstring key = L"홍";
        // 정수, 실수 문자열로 변환하는 함수.
        key += std::to_wstring(i);
        int value = rand() % 100;
        list.insert(std::make_pair(key, value));
    }
    int iValue = list[L"홍1"];
    // 이터레이터, 인덱싱지원(배열첨자)
    for (auto data : list)
    {
        std::wcout << data.first << " " ;  // 키
        std::cout << data.second << std::endl;  // 값
    }


    std::map<int, TData*>   dataMap;
    int iKey = 0;
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 != 0) continue;        
        TData* pNewData = new TData(i);
        dataMap.insert(std::make_pair(iKey++, pNewData));
    }
    TData* pFind = dataMap[399];
    if (pFind != nullptr)
    {
        std::wcout << pFind->iValue << " ";  // 키
    }
    auto iter = dataMap.find(30);
    if (iter != dataMap.end())
    {
        auto pData = iter->second;
        if (pData != nullptr)
        {
            std::wcout << pData->iValue << " ";         
        }
        //std::wcout << iter->first << " ";  // 키
        //std::wcout << iter->second->iValue << " ";  // 키
    }

    for (int iSize = 0; iSize < dataMap.size(); iSize++)
    {
        std::cout << dataMap[iSize]->iValue << std::endl;
    }

    for (int iSize = 0; iSize < dataMap.size(); iSize++)
    {
        delete dataMap[iSize];
    }
    dataMap.clear();
    std::cout << "Hello World!\n";
}
