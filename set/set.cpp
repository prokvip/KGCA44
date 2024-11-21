#include <iostream>
#include <set>
int main()
{
    std::set<int>  s0;
    s0.insert(5);
    s0.insert(3);
    s0.insert(3);
    s0.insert(1);
    //s0.emplace_hint(s0.end(), 6);
    //s0.emplace_hint(s0.end(), 1);

    std::multiset<int>  s1;
    s1.insert(5);
    s1.insert(3);
    s1.insert(3);
    s1.insert(1);
    // 기존
    auto iter4 = s1.emplace_hint(s1.begin(),1);
    // 신규
    auto iter5 = s1.emplace_hint(s1.end(),9);
    std::multiset<int>::iterator data = s1.find(3);
    if (data != s1.end())
    {
        std::cout << *data;
    }
    s1.emplace(33);
    auto iter = s1.find(5);
    // 복사, 이동 지원되지 않는다.
    auto iter2 = s1.emplace_hint(iter, 9);
    iter2++;
    iter2++;
         iter2 = s1.emplace_hint(iter2, 9);
    int icnt9 = std::count(iter2, s1.end(), 9);
    iter2++;
    iter2++;
    auto iter3 = s1.emplace_hint(iter, 5);
    iter3++;
    iter3++;
    int icnt3 = std::count(s1.begin(), s1.end(), 3);
    std::cout << "Hello World!\n";
}
