/// 양방향 연결리스트,  
// g_pHead(realData)
// g_pHead(virtualData)->realData
// g_pHead(V) ->realData-> g_pTail(V)
// realData -> g_pTail( 대부분 뒤에 삽입)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
struct TNode
{
    int     iValue;
    TNode*  pNext;
    TNode*  pPrev;
};

TNode* g_pHead = nullptr;
TNode* g_pTail = nullptr;

// 자료에 처리의 주요기능
// 초기화, 정리, 치환, 자료생성, 자료해제, 출력, 삽입, 검색, 삭제, 저장, 로드, 정렬
void    Show(TNode* pNode);
//void    Swap(TNode* a, TNode* b);
void    push_back(TNode* pNewNode );
void    push_front(TNode* pNewNode);
void    push_back(TNode* pDestNode, TNode* pNewNode);
void    push_front(TNode* pDestNode, TNode* pNewNode);
void    Initialize();
void    Release();
TNode*  CreateNode(int iValue);
void    ShowAll(bool bReverse=false);
TNode*  Erase(int iValue);
TNode*  Erase(TNode* pDeleteNode);
void    DeleteAll();
TNode*  Find(int iFindValue, bool bReverse = false);

int main()
{
    Initialize();  
    {        
        for (int iNode = 0; iNode < 10; iNode++)
        {
            TNode* pNewNode = CreateNode(iNode);
            //push_back(pNewNode);    
            push_front(pNewNode);
        }
        ShowAll();
        ShowAll(true);

        // 0 -> 1 -> 2 -> nullptr
        // 1) 1 del   g_pHead -> 0 -> 2
        // 2) 2 del   g_pHead -> 0 -> 1        
        // 3) 0 del   g_pHead -> 1 -> 2
        TNode* pNode1 = Find(1);
        TNode* pNode2 = Find(2,true);

        TNode* pNewNode1 = CreateNode(999);
        if (pNewNode1 != nullptr)
        {
            push_back(pNode1, pNewNode1);
        }

        TNode* pNewNode2 = CreateNode(999);
        push_front(pNode1, pNewNode2);

        /*Erase(pNode1);        
        Erase(pNode2);
        Erase(0);*/

        DeleteAll();

        ShowAll(true);
        ShowAll(false);
        for (int iNode = 0; iNode < 5; iNode++)
        {
            push_back(CreateNode(iNode));
        }
        ShowAll();
        DeleteAll();
    }
    Release();
}

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
void    ShowAll(bool bReverse)
{
    if (bReverse == false)
    {
        // 단 방향 연결리스트 순회.
        for (TNode* pNode = g_pHead->pNext;
            pNode != g_pTail;
            pNode = pNode->pNext)
        {
            Show(pNode);
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
    while (pNode!=g_pHead)
    {
        pNode = Erase(pNode);
    }
}
TNode* Find(int iFindValue, bool bReverse)
{
    if (bReverse == false)
    {
        TNode* pNode = g_pHead->pNext;
        while (pNode!=g_pTail)
        {
            if (pNode->iValue == iFindValue)
            {
                return pNode;
            }
            pNode = pNode->pNext;
        }
    }
    else
    {
        TNode* pNode = g_pTail->pPrev;
        while (pNode != g_pHead)
        {
            if (pNode->iValue == iFindValue)
            {
                return pNode;
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