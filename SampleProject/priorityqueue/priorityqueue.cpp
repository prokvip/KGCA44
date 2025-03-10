#include <iostream>
#include <queue>
#include <map>
template<typename T>
void Print(T& q)
{
    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
}
struct TJob
{
    int iPriority = 0;
    bool operator()(TJob& a, TJob& b)
    {
        return a.iPriority < b.iPriority;
    }
    void Fun()
    {

    }
    TJob() = default;
    TJob(int i) : iPriority(i) {}
};
struct cmp
{
    bool operator()(TJob& a, TJob& b)
    {
        return a.iPriority < b.iPriority;
    }
};
class TItem;
typedef std::multimap<int, TItem*> priority_map;

class TItem
{
public:
    void   add(priority_map& quque)
    {
        m_pQueue = &quque;
        m_Iter = quque.insert(std::make_pair(m_iPriority,this));
    }
    void   SetPriority(int priority)
    {
        m_iPriority = priority;
        if (m_pQueue)
        {
            priority_map& queue = *m_pQueue;
            this->remove();
            this->add(queue);
        }
    }
    void   remove()
    {
        m_pQueue->erase(m_Iter);
        m_pQueue = nullptr;
        m_Iter = priority_map::iterator();
    }
    int     Get() { return m_iPriority; }
    void    Set(int i) { m_iPriority = i; }
private:
    int             m_iPriority;
    std::wstring    m_szData;
    priority_map*   m_pQueue;
    priority_map::iterator  m_Iter;
};
int main()
{
    priority_map  pMapCopy;
    TItem* item = new TItem;
    auto iter = pMapCopy.insert(std::make_pair(item->Get(), item));
    item->Set(1);
    int ip = iter->second->Get() ;
    iter->second->Set(ip);
    pMapCopy.erase(iter);
    auto iter = pMapCopy.insert(std::make_pair(item->Get(), item));

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>

    priority_map  pMap; 

    TItem* i0 = new TItem;
    i0->add(pMap);
    i0->SetPriority(1);

    TItem* i1 = new TItem;
    i1->add(pMap);
    //i1->SetPriority(4);
    TItem* i2 = new TItem;
    i2->add(pMap);
    //i2->SetPriority(2);

    i0->SetPriority(9);

    for (auto data : pMap)
    {
        delete data.second;
    }
    pMap.clear();


    std::priority_queue< TJob, 
        std::vector<TJob>, TJob>  joblist;

    TJob a(4);
    TJob b(5);
    TJob c(1);
    TJob d(8);
    joblist.push(c);
    joblist.push(a);
    joblist.push(b);
    joblist.push(d);

    TJob job = joblist.top();
    job.Fun();

    // 우선순위 큐
    std::priority_queue<int> q;
    for (int i = 0; i < 10; i++)
    {
        q.push(rand() % 100);
    }
    int iValue = q.top();
    q.push(100);
    iValue = q.top();
    Print(q);
    std::cout << "Hello World!\n";
}
