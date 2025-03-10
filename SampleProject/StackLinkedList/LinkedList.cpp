#include "LinkedList.h"

unsigned int TNode::iKeyIndex = 0;
int          TLinkedlist::m_iCurrentCounter = 0;

TLinkedlist::TLinkedlist()
{
    Initialize();
}
TLinkedlist::~TLinkedlist()
{
    DeInitialize();
}
bool    TLinkedlist::Ascending(TNode* a, TNode* b)
{
    if (a > b)
    {
        return true;
    }
    return false;
}
bool    TLinkedlist::Descending(TNode* a, TNode* b)
{
    if (a < b)
    {
        return true;
    }
    return false;
}
void    TLinkedlist::Show(const TNode* const pNode) const
{    
    if (pNode != nullptr)
    {
        printf("%d ", pNode->iKey);
    }
}
void    TLinkedlist::push_back(TNode* pNewNode)
{
    // pPreNode -> pNewNode - > g_pTail
    TNode* pPreNode = g_pTail->pPrev;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext = g_pTail;
    // pPreNode <- pNewNode <- g_pTail
    g_pTail->pPrev = pNewNode;
    pNewNode->pPrev = pPreNode;

    TLinkedlist::m_iCurrentCounter++;
}
void    TLinkedlist::push_front(TNode* pNewNode)
{
    // g_pHead -> pNewNode - > pPostNode
    TNode* pPostNode = g_pHead->pNext;
    g_pHead->pNext = pNewNode;
    pNewNode->pNext = pPostNode;
    // g_pHead <- pNewNode <- pPostNode
    pPostNode->pPrev = pNewNode;
    pNewNode->pPrev = g_pHead;

    TLinkedlist::m_iCurrentCounter++;
}
void    TLinkedlist::push_back(TNode* pDestNode, TNode* pNewNode)
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
    TNode* pPostNode = pDestNode->pNext;
    pDestNode->pNext = pNewNode;
    pNewNode->pNext = pPostNode;
    // pDestNode <- pNewNode <- pPostNode
    pPostNode->pPrev = pNewNode;
    pNewNode->pPrev = pDestNode;

    TLinkedlist::m_iCurrentCounter++;
}
void    TLinkedlist::push_front(TNode* pDestNode, TNode* pNewNode)
{
    /*if (pDestNode == nullptr || pNewNode == nullptr)
    {
        return false;
    }*/
    assert(pDestNode);
    assert(pNewNode);
    // pPreNode -> pNewNode - > pDestNode
    TNode* pPreNode = pDestNode->pPrev;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext = pDestNode;
    // pPreNode <- pNewNode <- pDestNode
    pDestNode->pPrev = pNewNode;
    pNewNode->pPrev = pPreNode;

    TLinkedlist::m_iCurrentCounter++;
}
void    TLinkedlist::Initialize()
{
    // 가상의 머리노드를 생성해 둔다.
    g_pHead = (TNode*)malloc(sizeof(TNode));
    g_pHead->iKey = -1;
    g_pTail = (TNode*)malloc(sizeof(TNode));
    g_pTail->iKey = -2;

    g_pHead->pNext = g_pTail;
    g_pHead->pPrev = nullptr;
    g_pTail->pNext = nullptr;
    g_pTail->pPrev = g_pHead;

}
void    TLinkedlist::DeInitialize()
{
    free(g_pHead);
    free(g_pTail);
    g_pHead = nullptr;
    g_pTail = nullptr;
}
TNode* TLinkedlist::CreateNode()
{
    TNode* pNewNode = (TNode*)malloc(sizeof(TNode));
    pNewNode->iKey = 0;
    pNewNode->pNext = nullptr;
    pNewNode->pPrev = nullptr;
    return pNewNode;
}
void    TLinkedlist::ShowAll(bool bReverse, void(*Fun)(TNode*,FILE*), FILE* fp)
{
    if (bReverse == false)
    {
        // 단 방향 연결리스트 순회.
        for (TNode* pNode = g_pHead->pNext;
            pNode != g_pTail;
            pNode = pNode->pNext)
        {
            if (Fun != nullptr)
            {
                Fun(pNode,fp);
            }
            else
            {
                Show(pNode);
            }
        }
    }
    else
    {
        for (TNode* pNode = g_pTail->pPrev;
            pNode != g_pHead;
            pNode = pNode->pPrev)
        {
            Show(pNode);
        }
    }
}
TNode* TLinkedlist::Erase(int iKey)
{
    if (iKey < 0) return nullptr;
    TNode* pNode = Find(iKey);
    return Erase(pNode);
}
TNode* TLinkedlist::Erase(TNode* pDeleteNode)
{
    if (g_pHead == pDeleteNode ||
        g_pTail == pDeleteNode) return nullptr;

    TNode* pPreNode = pDeleteNode->pPrev;
    TNode* pPostNode = pDeleteNode->pNext;
    pPreNode->pNext = pPostNode;
    pPostNode->pPrev = pPreNode;
    free(pDeleteNode);

    TLinkedlist::m_iCurrentCounter--;
    return pPreNode;
}
void    TLinkedlist::DeleteAll()
{
    // 해제(신규 추가된 노드를 모두 삭제한다.
    TNode* pNode = g_pTail->pPrev;
    while (pNode != g_pHead)
    {
        pNode = Erase(pNode);
    }
}
TNode* TLinkedlist::Find(int iFindKey, bool bReverse, bool (*Fun)(TNode*))
{
    if (bReverse == false)
    {
        TNode* pNode = g_pHead->pNext;
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
        TNode* pNode = g_pTail->pPrev;
        while (pNode != g_pHead)
        {
            if(Fun != nullptr)
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
TNode* TLinkedlist::Find(bool (*Fun)(TNode*))
{
    if (Fun == nullptr) return nullptr;
    TNode* pNode = g_pHead->pNext;
    while (pNode != g_pTail)
    {
        bool bResult = Fun(pNode);
        if (bResult == true) return pNode;
        pNode = pNode->pNext;
    }    
    return nullptr;
}
bool TLinkedlist::Swap(TNode* aNode, TNode* bNode)
{
    //  H, a, 1 , 2, b -> H<->b,<->1, 2, a
    //  a, 1 , b -> b, 1, a
    //  a, b -> b, a
    TNode* aTemp = aNode;
    TNode* aPrev = aNode->pPrev;
    TNode* aNext = aNode->pNext;
    TNode* bPrev = bNode->pPrev;
    TNode* bNext = bNode->pNext;

    //aPrev -> bNode -> aNext -> aNode -> bNext;
    //aPrev -> bNode -> aNode -> bNext;
    aPrev->pNext = bNode;
    if( aNext == bNode)
    { 
        bNode->pNext = aNode;
    }else
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
void   TLinkedlist::Sort(bool (*Fun)(TNode* a, TNode* b))
{
    if (Fun == nullptr) return;
    // 10, 6, 9, 1, 7, 2, 3
    // 6, 10, 9, 1, 7, 2, 3
    // 6, 3, 9, 1, 7, 2, 10
   
    // 2, 6, 9, 1, 7, 2, 3
    // 2, 6, 9, 1, 7, 2, 3
    TNode* pEnd = g_pTail;
    int iCounter = 0;
    for (int iCnt=0; iCnt < TLinkedlist::m_iCurrentCounter; iCnt++)
    {
        for (TNode* bNode = g_pHead->pNext;
            bNode != pEnd;
            )
        {
            TNode* pNode0 = bNode;
            TNode* pNode1 = bNode->pNext;
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
    printf("\n%d번 비교로 정렬했습니다.", iCounter);
}

// 0 -> 1 -> 2 -> nullptr
// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
// 주)노드를 추가할 때 마다 꼬리를 저장하고 있으면 
//  직접 꼬리노드에 연결할 수 있다.
// new 5 insert : // 4(Tail) -> 5 -> nullptr

/// 가상의 머리노드(g_pHead)를 사전에 생성해 두고 추가하자.
//  실제 데이터 노드는 g_pHead->pNext부터 연결한다.
// g_pHead -> 0 -> 1 -> 2 -> nullptr
// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
// 주)노드를 추가할 때 마다 꼬리를 저장하고 있으면 
//  직접 꼬리노드에 연결할 수 있다.
// new 5 insert : // 4(Tail) -> 5 -> nullptr