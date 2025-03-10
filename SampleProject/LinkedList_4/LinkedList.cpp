#include "LinkedList.h"
//Sample.obj : error LNK2005 : "struct TNode * g_pHead" (? g_pHead@@3PEAUTNode@@EA)이(가) LinkedList.obj에 이미 정의되어 있습니다.
TNode* g_pHead;
TNode* g_pTail;
void    Show(TNode* pNode)
{
    if (pNode != nullptr)
    {
        printf("%d ", pNode->iValue);
    }
}
void    push_back(TNode* pNewNode)
{
    // pPreNode -> pNewNode - > g_pTail
    TNode* pPreNode = g_pTail->pPrev;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext = g_pTail;
    // pPreNode <- pNewNode <- g_pTail
    g_pTail->pPrev = pNewNode;
    pNewNode->pPrev = pPreNode;
}
void    push_front(TNode* pNewNode)
{
    // g_pHead -> pNewNode - > pPostNode
    TNode* pPostNode = g_pHead->pNext;
    g_pHead->pNext = pNewNode;
    pNewNode->pNext = pPostNode;
    // g_pHead <- pNewNode <- pPostNode
    pPostNode->pPrev = pNewNode;
    pNewNode->pPrev = g_pHead;
}
void    push_back(TNode* pDestNode, TNode* pNewNode)
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
}
void    push_front(TNode* pDestNode, TNode* pNewNode)
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
}
void    Initialize()
{
    // 가상의 머리노드를 생성해 둔다.
    g_pHead = (TNode*)malloc(sizeof(TNode));
    g_pHead->iValue = -1;
    g_pTail = (TNode*)malloc(sizeof(TNode));
    g_pTail->iValue = -2;

    g_pHead->pNext = g_pTail;
    g_pHead->pPrev = nullptr;
    g_pTail->pNext = nullptr;
    g_pTail->pPrev = g_pHead;

}
void    Release()
{
    free(g_pHead);
    free(g_pTail);
    g_pHead = nullptr;
    g_pTail = nullptr;
}
TNode* CreateNode(int iValue)
{
    TNode* pNewNode = (TNode*)malloc(sizeof(TNode));
    pNewNode->iValue = iValue;
    pNewNode->pNext = nullptr;
    pNewNode->pPrev = nullptr;
    return pNewNode;
}
void    ShowAll(bool bReverse, void(*Fun)(TNode*))
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
                Fun(pNode);
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
TNode* Erase(int iValue)
{
    TNode* pNode = Find(iValue);
    return Erase(pNode);
}
TNode* Erase(TNode* pDeleteNode)
{
    TNode* pPreNode = pDeleteNode->pPrev;
    TNode* pPostNode = pDeleteNode->pNext;
    pPreNode->pNext = pPostNode;
    pPostNode->pPrev = pPreNode;
    free(pDeleteNode);
    return pPreNode;
}
void    DeleteAll()
{
    // 해제(신규 추가된 노드를 모두 삭제한다.
    TNode* pNode = g_pTail->pPrev;
    while (pNode != g_pHead)
    {
        pNode = Erase(pNode);
    }
}
TNode* Find(int iFindValue, bool bReverse, bool (*Fun)(TNode*))
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
                if (pNode->iValue == iFindValue)
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
                if (pNode->iValue == iFindValue)
                {
                    return pNode;
                }
            }
            pNode = pNode->pPrev;
        }
    }
    return nullptr;
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