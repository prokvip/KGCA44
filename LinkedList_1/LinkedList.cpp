#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
struct TNode
{
    int     iValue;
    struct TNode*  pNext;
} ;
void  Show( TNode* pNode)
{    
    if (pNode != nullptr)
    {
        printf("%d ", pNode->iValue);
    }
}

TNode* g_pHead = nullptr;
TNode* g_pTail = nullptr;

void Insert(TNode* pNewNode)
{
    g_pTail->pNext = pNewNode;
    g_pTail = pNewNode;
}

void Initialize()
{
    // 가상의 머리노드를 생성해 둔다.
    g_pHead = (TNode*)malloc(sizeof(TNode));
    g_pTail = g_pHead;
}
void Release()
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
    return pNewNode;
}
void ShowAll()
{
    // 단 방향 연결리스트 순회.
    for (TNode* pNode = g_pHead->pNext;
        pNode != nullptr;
        pNode = pNode->pNext)
    {
        Show(pNode);
    }
}
TNode* Delete(TNode* pDeleteNode)
{
    TNode* pTemp = pDeleteNode->pNext;
    free(pDeleteNode);
    return pTemp;
}
TNode* Del(TNode* pDeleteNode)
{
    TNode* pPreNode = g_pHead;
    while (pPreNode)
    {
        if (pPreNode->pNext == pDeleteNode)
        {
            TNode* pNext = Delete(pDeleteNode);
            pPreNode->pNext = pNext;
            break;
        }
        pPreNode = pPreNode->pNext;
    }
    return pPreNode;
}
void DeleteAll()
{
    // 해제(신규 추가된 노드를 모두 삭제한다.
    TNode* pNode = g_pHead->pNext;
    while (pNode)
    {
        pNode = Delete(pNode);
    }
    g_pHead->pNext = nullptr;
    g_pTail = g_pHead;
}
TNode* Find(int iFindValue)
{
    TNode* pPreNode = g_pHead;
    while (pPreNode)
    {
        if (pPreNode->pNext != nullptr)
        {
            if (pPreNode->pNext->iValue == iFindValue)
            {
                return pPreNode;
            }
        }   
        pPreNode = pPreNode->pNext;
    }
    return nullptr;
}
int main()
{
    Initialize();  
    {        
        for (int iNode = 0; iNode < 3; iNode++)
        {
            TNode* pNewNode = CreateNode(iNode);
            Insert(pNewNode);           
        }
        ShowAll();

        // 0 -> 1 -> 2 -> nullptr
        // 1) 1 del   g_pHead -> 0 -> 2
        // 2) 2 del   g_pHead -> 0 -> 1        
        // 3) 0 del   g_pHead -> 1 -> 2
       /* TNode* pFindPreNode = Find(1);
        TNode* pNextNode  = Delete(pFindPreNode->pNext);
        TNode* pNextNode = Delete(g_pTail);

        pFindPreNode->pNext = pNextNode;*/
        //TNode* pNextNode = Find(2);
        //TNode* pNextNode = Find(0);

        DeleteAll();

        ShowAll();
        for (int iNode = 0; iNode < 5; iNode++)
        {
            Insert(CreateNode(iNode));
        }
        ShowAll();
        DeleteAll();
    }
    Release();
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