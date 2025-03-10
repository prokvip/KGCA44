/// 양방향 연결리스트
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

void    Show(TNode* pNode);
void    push_back(TNode* pNewNode);
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
        for (int iNode = 0; iNode < 3; iNode++)
        {
            TNode* pNewNode = CreateNode(iNode);
            push_back(pNewNode);           
        }
        ShowAll();
        ShowAll(true);

        // 0 -> 1 -> 2 -> nullptr
        // 1) 1 del   g_pHead -> 0 -> 2
        // 2) 2 del   g_pHead -> 0 -> 1        
        // 3) 0 del   g_pHead -> 1 -> 2
        TNode* pNode1 = Find(1);
        //TNode* pNode2 = Find(2,true);
        Erase(pNode1);        
        //Erase(pNode2);
        //Erase(0);

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
    // 0(PreNode) -> 1 -> pNewNode(tail) -> nullptr        
    g_pTail->pNext = pNewNode;    
    // 0(PreNode) <- 1 <- pNewNode(tail) -> nullptr    
    pNewNode->pPrev = g_pTail;

    g_pTail = pNewNode;
}
void    Initialize()
{
    // 가상의 머리노드를 생성해 둔다.
    g_pHead = (TNode*)malloc(sizeof(TNode));
    g_pHead->iValue = -1;
    g_pHead->pNext = nullptr;
    g_pHead->pPrev = nullptr;
    g_pTail = g_pHead;    
}
void    Release()
{
    free(g_pHead);
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
            pNode != nullptr;
            pNode = pNode->pNext)
        {
            Show(pNode);
        }
    }
    else
    {
        for (TNode* pNode = g_pTail;
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
    if (pPostNode != nullptr)
    {
        pPostNode->pPrev = pPreNode;
    }
    else
    {
        g_pTail = pPreNode; // 꼬리노드를 삭제의 경우
    }
    free(pDeleteNode);
    return pPreNode;
}
void    DeleteAll()
{
    // 해제(신규 추가된 노드를 모두 삭제한다.
    TNode* pNode = g_pTail;
    while (pNode!=nullptr && pNode != g_pHead)
    {
        pNode = Erase(pNode);
    }
    g_pHead->pNext = nullptr;
    g_pTail = g_pHead;
}
TNode* Find(int iFindValue, bool bReverse)
{
    if (bReverse == false)
    {
        TNode* pNode = g_pHead->pNext;
        while (pNode)
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
        TNode* pNode = g_pTail;
        while (pNode && g_pHead != pNode)
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