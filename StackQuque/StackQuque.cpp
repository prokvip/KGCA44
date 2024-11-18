#include <iostream>
#include <stack>
#include <queue>
struct TData
{
    int* pData = nullptr;
    int iValue;
    // 대입연산자
    void operator = (const TData& c)
    {
        iValue = c.iValue;
        pData = new int;
        *pData = *c.pData;
    }
    // 이동대입연산자
    void operator = ( TData&& c)
    {
        iValue = c.iValue;
        pData = c.pData;
        c.pData = nullptr;
    }
    TData(const TData& c)
    {
        this->iValue = c.iValue;
        pData = new int;
        *pData = *c.pData;

       // pData = c.pData;
    }
    TData()
    {
        iValue = -1;
        pData = new int;
        *pData = 9;
    }
    // 이동생성자
    TData(TData && c)
    {
        iValue = c.iValue;
        pData = c.pData;

        c.iValue = -1;
        c.pData = nullptr;
    }
    TData(int i)
    {
        pData = new int;
        *pData = 9;
        iValue = i;
    }
    ~TData()
    {
        iValue = -1;
        delete pData;
        pData = nullptr;
    }
};
TData GetDataCopy(int iValue)
{
    TData newData(iValue);
    return newData;
}
TData GetDataMove(int iValue)
{
    TData newData(iValue);
    return std::move(newData);
}
TData&& GetDataMoveMove(int iValue)
{
    //TData newData(iValue);
    return iValue;// std::move(newData);
}

int main()
{
    std::stack<TData> s2;
    TData data(1);    
    int k = 4;
    int& r = k;
    //int& k = 3;
    int&& u = 4;
    TData a = GetDataMoveMove(6);
    //TData datacopy = data;    
    //TData datacopy2;
    //datacopy2 = data;
    //// 참조
    //TData& datacopy3 = data;
    s2.push(data);
    s2.push(TData(6));
    s2.push(GetDataCopy(6));   

    s2.push(GetDataMove(7));
    //s2.push(GetDataMoveMove(8));

    // 생성자를 통해서 직접 컨테이너에 넣는다.
    s2.emplace();
    s2.emplace(  6  );    
    s2.emplace(data);
    s2.emplace(TData(2));
    s2.emplace(std::move(data));
    s2.emplace(GetDataCopy(6));
    s2.emplace(GetDataMove(7));
    //s2.emplace(GetDataMoveMove(7));
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::stack<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    std::stack<int> s1;
    for (int i = 0; i < 3; i++)
    {
        s1.push(i);
    }
    s.swap(s1);

    for (int i = 0; i < 10; i++)
    {
        std::cout << s.top() << " " << s.size() << std::endl;
        s.pop();
    }
    std::cout << "Empty = " << s.empty() << std::endl;
    
    std::queue<int> q;
    for (int i = 0; i < 10; i++)
    {
        q.push(i);
    }
    while(!q.empty())
    {
        std::cout << q.front() << " " << q.back() << std::endl;
        q.pop();
    }
    std::cout << "Empty = " << s.empty() << std::endl;

    std::cout << "Hello World!\n";
}
