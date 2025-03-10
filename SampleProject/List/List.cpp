#include <windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <atlconv.h>  // A2W
using namespace std;
// 연결리스트
static std::wstring to_mw(const std::string& _src)
{
    USES_CONVERSION;
    return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
    USES_CONVERSION;
    return std::string(W2A(_src.c_str()));
};
static std::wstring mtw(std::string str)
{
    std::wstring ret = std::wstring(str.begin(), str.end());
    return  ret;
}
static std::string wtm(std::wstring str)
{
    return  std::string(str.begin(), str.end());
}

template <typename S> 
void print(const S& s) 
{
    cout << s.size() << " elements: ";
    for (const auto& p : s) 
    {
        cout << "(" << p << ") ";
    }

    cout << endl;
}
struct TData
{
    int iData;
    TData(const TData& c)
    {
        iData = c.iData;
        std::cout << "copy" << iData << std::endl;
    }
    TData& operator =(const TData& a)
    {
        iData = a.iData;
        std::cout << "TData&=" << iData << std::endl;
        return *this;
    }
    TData& operator =(const TData&& a)
    {
        iData = a.iData;
        std::cout << "TData&&=" << iData << std::endl;
        return *this;
    }
    TData(TData&& c)
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
class Cmp
{
public:
    bool operator()(int val)
    {
        return (val % 2) == 1;
    }
};
bool CmpFun(int val)
{
    return (val % 10) == 0;
}
int main()
{
    std::setlocale(LC_ALL, "");

    // 영문,숫자,기호 1byte 표현 가능
    // 한글,중일아 2byte 표현 가능
    // 싱글바이트,멀티바이트,유니코드
    // 1Byte     , 한글2+영문1  무조건 2바이트
    std::string     multibyte;
    //basic_string<char, char_traits<char>
    multibyte = "한글abc";//7
    std::wstring    unicodebyte;
    //basic_string<wchar_t, char_traits<wchar_t>,
    unicodebyte = L"한글abc"; //  _T("한글abc") #include <tchar.h?
    // [하][ㄴ][그][ㄹ][a][0][b][0][c][0]


    int iMSize = multibyte.size();
    int iUSize = unicodebyte.size();

    std::wstring s1 = std::wstring( multibyte.begin(),
                                    multibyte.end());
    std::string s2 = std::string(unicodebyte.begin(),
                                unicodebyte.end());
    std::wstring s3 = to_mw(multibyte);
    std::string s4 = to_wm(unicodebyte);

    char szData[] = "aa";
    wchar_t szData2[] = L"aa";
    if (szData2 == L"aa")
    {

    }
    std::wstring szText(L"aaaa");
    std::wstring szSum(szText.begin(), szText.end());

    const char* pStringPointer1 = multibyte.c_str();
    const wchar_t* pStringPointer2 = unicodebyte.c_str();
    std::cout << pStringPointer1 << std::endl;
    std::wcout << unicodebyte << std::endl;
    std::wcout << pStringPointer2 << std::endl;

    std::vector<std::wstring> szList;  
    szList.push_back(L"aaa");
    szList.push_back(L"bbb");
    std::wstring sum = szList[0] +szList[1];
    std::wcin >> unicodebyte;
    for (auto data : szList)
    {
        //std::cout << data << " ";
        std::wcout << data << " ";
    }

    list<int> c1{ 10,11 };
    list<int> c2{ 20,21,22 };
    list<int> c3{ 30,31 };
    list<int> c4{ 40,41,42,43 };
    list<int> c5{ 1,4,5,40,41,42,43 };
    c5.remove(5);
    c5.remove_if(Cmp());
    c5.remove_if(CmpFun);


    auto& list40 = c1;
    using KGCA = TData;
    list<KGCA>::value_type AnInt;// TData AnInt;
    AnInt.iData = 5;
    AnInt = 8;


    list<int>::iterator where_iter;
    list<int>::iterator first_iter;
    list<int>::iterator last_iter;

    cout << "Beginning state of lists:" << endl;
    cout << "c1 = ";
    print(c1);
    cout << "c2 = ";
    print(c2);
    cout << "c3 = ";
    print(c3);
    cout << "c4 = ";
    print(c4);

    where_iter = c2.begin();
    ++where_iter; // start at second element
    c2.splice(where_iter, c1);
    cout << "After splicing c1 into c2:" << endl;
    cout << "c1 = ";
    print(c1);
    cout << "c2 = ";
    print(c2);

    first_iter = c3.begin();
    first_iter++;
    c2.splice(where_iter, c3, first_iter);
    cout << "After splicing the first element of c3 into c2:" << endl;
    cout << "c3 = ";
    print(c3);
    cout << "c2 = ";
    print(c2);

    first_iter = c4.begin();
    last_iter = c4.end();
    // set up to get the middle elements
    //++first_iter;
    --last_iter;
    c2.splice(where_iter, c4, first_iter, last_iter);
    cout << "After splicing a range of c4 into c2:" << endl;
    cout << "c4 = ";
    print(c4);
    cout << "c2 = ";
    print(c2);

    // 인덱싱 지원 안함.
    std::list<int> vecList20(10);
    
    for (int i = 0; i < 10; i++)
    {
        vecList20.push_back(rand() % 100);
        //vecList20.push_front(rand() % 100);
    }
    vecList20.push_back(24);
    std::greater<int> mypred;
    //vecList20.unique();
    vecList20.unique(mypred);

    vecList20.reverse();
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    vecList20.sort();
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    //std::sort(vecList20.begin(), vecList20.end(), std::less<>());
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    /*std::sort(vecList20.begin(), vecList20.end(), 
        std::greater<>());*/
    for (auto data : vecList20)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    auto iFindIter = std::find(vecList20.begin(), vecList20.end(), 24);
    if (iFindIter != vecList20.end())
    {
        std::cout << *iFindIter << " ";
    }

    std::list<TData> vecList12;
    //vecList12.reserve(10);
    vecList12.emplace_back(1);
    vecList12.emplace_back(2);
    vecList12.emplace_back(3);
    vecList12.emplace_back(4);
    vecList12.emplace(vecList12.begin(), 5);
    vecList12.insert(vecList12.end(), 6);




    std::list<TData> vecList19(vecList12.begin(), vecList12.end());
    std::list<TData> vecList18(1);
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


    std::list<TData> vecList16 = vecList12;
    auto vecList17 = vecList16;
    auto h = 3;
    auto f = 3.14;
    auto s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    char ss[] = "dddddddddd";
    std::cout << h << f << s;

    vecList12.pop_back();
    if(!vecList12.empty())
    {
        auto tData3 = vecList12.front();
    }    
    vecList12.emplace_back();
    TData& pFront = vecList12.front();
    TData& pBack = vecList12.back();
    // 배열의 시작주소 반환
   ///* TData* datapointer = &vecList12.at(0);
   // TData* pDataPointer = vecList12.data();
   // pDataPointer++;
   // std::cout << (pDataPointer)->iData << " ";
   // pDataPointer++;
   // std::cout << (pDataPointer)->iData << " ";*/
    //std::list<TData>::reverse_iterator iter12;
    for (auto iter = vecList12.rbegin();
        iter != vecList12.rend();
        iter++)
    {
        std::cout << iter->iData << " ";
    }
    const int j = 3;
    int k = j;
    std::list<TData>::const_iterator citer12;
    for (citer12 = vecList12.begin();
        citer12 != vecList12.end();
        citer12++)
    {
        std::cout << citer12->iData << " ";
    }

   
    std::list<TData> vecList13 = vecList12;
    std::list<TData> vecList14(vecList12);
    std::list<TData> vecList15;
    vecList15 = vecList12;

    std::list<TData> vecList11;
    vecList11.emplace_back(1);
    vecList11.emplace_back(TData(1));


    std::list<TData> vecList10;
    vecList10.push_back(TData(1));

    std::list<TData> vecList9;
    vecList9.emplace_back(TData(1));
    vecList9.emplace_back(TData(2));
    // TNode
    std::list<TData>::iterator iter9;
    for (iter9 = vecList9.begin();
        iter9 != vecList9.end();
        )
    {
        iter9 = vecList9.erase(iter9);
    }

    std::list<TData> vecList8;
    vecList8.emplace_back(TData(1));
    vecList8.emplace_back(TData(2));
    // TNode
    std::list<TData>::iterator iter;
    for (iter = vecList8.begin();
        iter != vecList8.end();
        iter++)
    {
        std::cout << iter->iData;
    }
    vecList8.erase(vecList8.begin());
    int iSize = vecList8.size();

    std::list<TData*> vecList7;
    for (int i = 0; i < 5; i++)
    {
        vecList7.push_back(new TData(i));        
    }
    for (auto data : vecList7)
    {
        delete data;
    }
    std::cout << "size=" << vecList7.size();
    vecList7.clear();

    


  

    std::list<int> vecList1;
    for (int i = 0; i < 30; i++)
    {
        vecList1.push_back(i);        
    }
    std::cout << "size=" << vecList1.size();

    std::list<int> vecList2;
    vecList2.resize(10);// array[10]
    for (int i = 0; i < 10; i++)
    {
        vecList1.push_front(i);
    }
    vecList2.push_back(99);
    std::cout << "size=" << vecList2.size();

}
