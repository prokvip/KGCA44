#pragma once
#include "TCharacter.h"
//#define  _CRT_SECURE_NO_WARNINGS
/// ����� ���Ḯ��Ʈ,  
// g_pHead(realData)
// g_pHead(virtualData)->realData
// g_pHead(V) ->realData-> g_pTail(V)
// realData -> g_pTail( ��κ� �ڿ� ����)

template <class T>
struct TNode
{
    T       data;
    int     iKey;
    TNode* pNext;
    TNode* pPrev;
    // ������ Ű ����
    static  unsigned int iKeyIndex;
    friend std::ostream& operator <<(std::ostream& os, TNode<T>& a)
    {
        os << a.data;
        return  os;
    }
    friend std::ostream& operator <<(std::ostream& os, TNode<T>* a) 
    {
        os << a->data;
        return os;
    }
    ~TNode()
    {
    }
};

template <class T>
unsigned int TNode<T>::iKeyIndex = 0;

template<class T>
class TLinkedlist
{
protected:
    TNode<T>* g_pHead;
    TNode<T>* g_pTail;
public:
    TNode<T>* begin() { return g_pHead->pNext; }
    TNode<T>* end() { return g_pTail; }
    // ����� ����� ���� ����
    static  int m_iCurrentCounter;   

    int   Size() { return m_iCurrentCounter; }
    // �ڷῡ ó���� �ֿ���
    // �ʱ�ȭ, ����, ġȯ, �ڷ����, �ڷ�����, ���, ����, �˻�, ����, ����, �ε�, ����
    void    Show(TNode<T>* pNode);

    //void    push_back(T* pNewData, int iKey = -1);
    void    push_back(T  data, int iKey = -1);
public:
    TNode<T>* operator[](int index);
protected:
    void    push_back(TNode<T>* pNewNode);
    void    push_front(TNode<T>* pNewNode);
    void    push_back(TNode<T>* pDestNode, TNode<T>* pNewNode);
    void    push_front(TNode<T>* pDestNode, TNode<T>* pNewNode);
public:
    void    Initialize();
    void    DeInitialize();
    
    void   ShowAll( bool bReverse = false, 
                    void (*Fun)(TNode<T>*, FILE*) = nullptr,
                    FILE* fp = nullptr);
    TNode<T>* Erase(int iKey);
    TNode<T>* Erase(TNode<T>* pDeleteNode);
    void    DeleteAll();
    TNode<T>* Find(int iFindKey, bool bReverse = false,
                bool (*Fun)(TNode<T>*)=nullptr);
    TNode<T>* Find(bool (*Fun)(TNode<T>*) = nullptr);
    bool   Swap(TNode<T>* aNode, TNode<T>* bNode);
    void   Sort(bool (*Fun)(TNode<T>* a, TNode<T>* b) = Ascending);

    friend std::ostream& operator <<(std::ostream& os, TLinkedlist<T>& a)
    {
        for (TNode<T>* pNode = a.begin();
            pNode != a.end();
            pNode = pNode->pNext)
        {
            if (pNode != nullptr)
            {
                os << *pNode;
                os << pNode;
                os << pNode->data;               
            }
        }
        return os;
    }
    friend std::ostream& operator <<(std::ostream& os, TLinkedlist<T>* a)
    {
        for (TNode<T>* pNode = a->begin();
            pNode != a->end();
            pNode = pNode->pNext)
        {
            if (pNode != nullptr)
            {
                os << *pNode;
                os << pNode;
                os << pNode->data;
            }
        }
        return os;
    }
   
public:
    static TNode<T>* CreateNode();
    static bool    Ascending(TNode<T>* a, TNode<T>* b);
    static bool    Descending(TNode<T>* a, TNode<T>* b);
public:
    TLinkedlist();
    ~TLinkedlist();
};

template<class T>
int          TLinkedlist<T>::m_iCurrentCounter = 0;

template<class T>
TNode<T>* TLinkedlist<T>::operator[](int iKey)
{
    TNode<T>* pRetNode = nullptr;
    for (TNode<T>* pNode = g_pHead->pNext;
        pNode != g_pTail;
        pNode = pNode->pNext)
    {
        if (pNode->iKey == iKey)
        {
            pRetNode = pNode;
            break;
        }
    }
    return pRetNode;
}


template<class T>
TLinkedlist<T>::TLinkedlist()
{
    Initialize();
}
template<class T>
TLinkedlist<T>::~TLinkedlist()
{
    DeInitialize();
}
template<class T>
bool    TLinkedlist<T>::Ascending(TNode<T>* a, TNode<T>* b)
{
    if (a > b)
    {
        return true;
    }
    return false;
}
template<class T>
bool    TLinkedlist<T>::Descending(TNode<T>* a, TNode<T>* b)
{
    if (a < b)
    {
        return true;
    }
    return false;
}
template<class T>
void    TLinkedlist<T>::Show(TNode<T>* pNode)
{
    if (pNode != nullptr)
    {
        printf("%d ", pNode->iKey);
    }
}
//template<class T>
//void    TLinkedlist<T>::push_back(T* pNewData, int iKey)
//{
//    TNode<T>* pNewNode = CreateNode();
//    if (pNewNode != nullptr)
//    {
//        pNewNode->data = pNewData;
//        pNewNode->iKey = iKey;
//        if (iKey < 0)
//        {
//            pNewNode->iKey = ++TNode<TStudent>::iKeyIndex;
//        }
//        push_back(pNewNode);
//    }
//}
template<class T>
void    TLinkedlist<T>::push_back(T pNewData, int iKey)
{
    TNode<T>* pNewNode = CreateNode();
    if (pNewNode != nullptr)
    {
        pNewNode->data = pNewData;
        pNewNode->iKey = iKey;
        if (iKey < 0)
        {
            pNewNode->iKey = ++TNode<TStudent>::iKeyIndex;
        }
        push_back(pNewNode);
    }
}
template<class T>
void    TLinkedlist<T>::push_back(TNode<T>* pNewNode)
{
    //error C2440: '�ʱ�ȭ ��': 'TNodeBase *'���� 'T *'(��)�� ��ȯ�� �� �����ϴ�.
    // pPreNode -> pNewNode - > g_pTail
    TNode<T>* pPreNode = g_pTail->pPrev;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext = g_pTail;
    // pPreNode <- pNewNode <- g_pTail
    g_pTail->pPrev = pNewNode;
    pNewNode->pPrev = pPreNode;

    TLinkedlist::m_iCurrentCounter++;
}
template<class T>
void    TLinkedlist<T>::push_front(TNode<T>* pNewNode)
{
    // g_pHead -> pNewNode - > pPostNode
    T* pPostNode = g_pHead->pNext;
    g_pHead->pNext = pNewNode;
    pNewNode->pNext = pPostNode;
    // g_pHead <- pNewNode <- pPostNode
    pPostNode->pPrev = pNewNode;
    pNewNode->pPrev = g_pHead;

    TLinkedlist::m_iCurrentCounter++;
}
template<class T>
void    TLinkedlist<T>::push_back(TNode<T>* pDestNode, TNode<T>* pNewNode)
{
#ifdef _DEBUG
    if (pDestNode == nullptr || pNewNode == nullptr)
    {
        return;
    }
#endif
    assert(pDestNode);
    assert(pNewNode);
    // pDestNode -> pNewNode - > pPostNode
    TNode<T>* pPostNode = pDestNode->pNext;
    pDestNode->pNext = pNewNode;
    pNewNode->pNext = pPostNode;
    // pDestNode <- pNewNode <- pPostNode
    pPostNode->pPrev = pNewNode;
    pNewNode->pPrev = pDestNode;

    TLinkedlist::m_iCurrentCounter++;
}
template<class T>
void    TLinkedlist<T>::push_front(TNode<T>* pDestNode, TNode<T>* pNewNode)
{
    /*if (pDestNode == nullptr || pNewNode == nullptr)
    {
        return false;
    }*/
    assert(pDestNode);
    assert(pNewNode);
    // pPreNode -> pNewNode - > pDestNode
    TNode<T>* pPreNode = pDestNode->pPrev;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext = pDestNode;
    // pPreNode <- pNewNode <- pDestNode
    pDestNode->pPrev = pNewNode;
    pNewNode->pPrev = pPreNode;

    TLinkedlist::m_iCurrentCounter++;
}
template<class T>
void    TLinkedlist<T>::Initialize()
{
    // ������ �Ӹ���带 ������ �д�.
    g_pHead = new TNode<T>;
    g_pHead->iKey = -1;
    g_pTail = new TNode<T>;
    g_pTail->iKey = -2;

    g_pHead->pNext = g_pTail;
    g_pHead->pPrev = nullptr;
    g_pTail->pNext = nullptr;
    g_pTail->pPrev = g_pHead;

}
template<class T>
void    TLinkedlist<T>::DeInitialize()
{
    delete g_pHead;
    delete g_pTail;
    g_pHead = nullptr;
    g_pTail = nullptr;
}
template<class T>
TNode<T>* TLinkedlist<T>::CreateNode()
{
    TNode<T>* pNewNode = new TNode<T>;
    pNewNode->iKey = 0;
    pNewNode->pNext = nullptr;
    pNewNode->pPrev = nullptr;
    return pNewNode;
}
template<class T>
void    TLinkedlist<T>::ShowAll(bool bReverse, void(*Fun)(TNode<T>*, FILE*), FILE* fp)
{
    if (bReverse == false)
    {
        // �� ���� ���Ḯ��Ʈ ��ȸ.
        for (TNode<T>* pNode = g_pHead->pNext;
            pNode != g_pTail;
            pNode = pNode->pNext)
        {
            if (Fun != nullptr)
            {
                Fun(pNode, fp);
            }
            else
            {
                Show(pNode);
            }
        }
    }
    else
    {
        for (TNode<T>* pNode = g_pTail->pPrev;
            pNode != g_pHead;
            pNode = pNode->pPrev)
        {
            Show(pNode);
        }
    }
}
template<class T>
TNode<T>* TLinkedlist<T>::Erase(int iKey)
{
    TNode<T>* pNode = Find(iKey);
    return Erase(pNode);
}
template<class T>
TNode<T>* TLinkedlist<T>::Erase(TNode<T>* pDeleteNode)
{
    TNode<T>* pPreNode = pDeleteNode->pPrev;
    TNode<T>* pPostNode = pDeleteNode->pNext;
    pPreNode->pNext = pPostNode;
    pPostNode->pPrev = pPreNode;
    delete pDeleteNode;

    TLinkedlist::m_iCurrentCounter--;
    return pPostNode;
}
template<class T>
void    TLinkedlist<T>::DeleteAll()
{
    // ����(�ű� �߰��� ��带 ��� �����Ѵ�.
    TNode<T>* pNode = g_pTail->pPrev;
    while (pNode != g_pHead)
    {
        pNode = Erase(pNode);
    }
}
template<class T>
TNode<T>* TLinkedlist<T>::Find(int iFindKey, bool bReverse, bool (*Fun)(TNode<T>*))
{
    if (bReverse == false)
    {
        TNode<T>* pNode = g_pHead->pNext;
        while (pNode != g_pTail)
        {
            if (Fun != nullptr)
            {
                bool bResult = Fun(pNode);
                if (bResult == true) return pNode;
            }
            else
            {
                if (pNode->iKey == iFindKey)
                {
                    return pNode;
                }
            }
            pNode = pNode->pNext;
        }
    }
    else
    {
        TNode<T>* pNode = g_pTail->pPrev;
        while (pNode != g_pHead)
        {
            if (Fun != nullptr)
            {
                bool bResult = Fun(pNode);
                if (bResult == true) return pNode;
            }
            else
            {
                if (pNode->iKey == iFindKey)
                {
                    return pNode;
                }
            }
            pNode = pNode->pPrev;
        }
    }
    return nullptr;
}
template<class T>
TNode<T>* TLinkedlist<T>::Find(bool (*Fun)(TNode<T>*))
{
    if (Fun == nullptr) return nullptr;
    TNode<T>* pNode = g_pHead->pNext;
    while (pNode != g_pTail)
    {
        bool bResult = Fun(pNode);
        if (bResult == true) return pNode;
        pNode = pNode->pNext;
    }
    return nullptr;
}
template<class T>
bool TLinkedlist<T>::Swap(TNode<T>* aNode, TNode<T>* bNode)
{
    //  H, a, 1 , 2, b -> H<->b,<->1, 2, a
    //  a, 1 , b -> b, 1, a
    //  a, b -> b, a
    TNode<T>* aTemp = aNode;
    TNode<T>* aPrev = aNode->pPrev;
    TNode<T>* aNext = aNode->pNext;
    TNode<T>* bPrev = bNode->pPrev;
    TNode<T>* bNext = bNode->pNext;

    //aPrev -> bNode -> aNext -> aNode -> bNext;
    //aPrev -> bNode -> aNode -> bNext;
    aPrev->pNext = bNode;
    if (aNext == bNode)
    {
        bNode->pNext = aNode;
    }
    else
    {
        bNode->pNext = aNext;
    }

    aNext->pNext = aNode;
    aNode->pNext = bNext;

    //aPrev <- bNode <- aNext <- aNode <- bNext;
    //aPrev <- bNode <- aNode <- bNext;
    bNext->pPrev = aNode;
    if (aNext == bNode)
    {
        aNode->pPrev = bNode;
    }
    else
    {
        aNode->pPrev = aNext;
    }
    aNext->pPrev = bNode;
    bNode->pPrev = aPrev;
    return true;
}
template<class T>
void   TLinkedlist<T>::Sort(bool (*Fun)(TNode<T>* a, TNode<T>* b))
{
    if (Fun == nullptr) return;
    // 10, 6, 9, 1, 7, 2, 3
    // 6, 10, 9, 1, 7, 2, 3
    // 6, 3, 9, 1, 7, 2, 10

    // 2, 6, 9, 1, 7, 2, 3
    // 2, 6, 9, 1, 7, 2, 3
    TNode<T>* pEnd = g_pTail;
    int iCounter = 0;
    for (int iCnt = 0; iCnt < TLinkedlist::m_iCurrentCounter; iCnt++)
    {
        for (TNode<T>* bNode = g_pHead->pNext;
            bNode != pEnd;
            )
        {
            TNode<T>* pNode0 = bNode;
            TNode<T>* pNode1 = bNode->pNext;
            if (pNode1 == g_pTail) break;
            if (Fun(pNode0, pNode1))
            {
                Swap(pNode0, pNode1);
                bNode = pNode0;
            }
            else
            {
                bNode = bNode->pNext;
            }
            iCounter++;
        }
        pEnd = pEnd->pPrev;
    }
    printf("\n%d�� �񱳷� �����߽��ϴ�.", iCounter);
}

// 0 -> 1 -> 2 -> nullptr
// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
// ��)��带 �߰��� �� ���� ������ �����ϰ� ������ 
//  ���� ������忡 ������ �� �ִ�.
// new 5 insert : // 4(Tail) -> 5 -> nullptr

/// ������ �Ӹ����(g_pHead)�� ������ ������ �ΰ� �߰�����.
//  ���� ������ ���� g_pHead->pNext���� �����Ѵ�.
// g_pHead -> 0 -> 1 -> 2 -> nullptr
// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
// ��)��带 �߰��� �� ���� ������ �����ϰ� ������ 
//  ���� ������忡 ������ �� �ִ�.
// new 5 insert : // 4(Tail) -> 5 -> nullptr