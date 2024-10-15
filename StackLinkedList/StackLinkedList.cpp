#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
struct TNode
{
    int     iValue;
    struct TNode*  pNext;
} ;
// C언어에서는 동일한 이름의 함수를 선언할 수없다.
// C++에서는 가능하다.(함수 오버로딩)
void  funA(int k)
{
    printf("%d", k);
}
void  funA( TNode* pNode)
{    
    if (pNode != nullptr)
    {
        printf("%d ", pNode->iValue);
    }
}

TNode* pHead = nullptr;

void AddLink(TNode* pNewNode)
{
    if (pHead == nullptr)
    {
        pHead = pNewNode;
    }
    else
    {
        TNode* pNode = pHead;
        while(pNode)
        {
            if (pNode->pNext == nullptr)
            {
                pNode->pNext = pNewNode;
                break;
            }
            else
            {
                pNode = pNode->pNext;
            }
        }
    }
}
int main()
{
    TNode* pTemp = 0;
    funA(NULL);
    funA(nullptr);

    for (int iNode = 0; iNode < 10; iNode++)
    {
        TNode* pNewNode = (TNode*)malloc(sizeof(TNode));
        pNewNode->iValue = 100*iNode;
        pNewNode->pNext = nullptr;
        AddLink(pNewNode);
    }
    // 단 방향 연결리스트 순회.
    for (TNode* pNode = pHead;
         pNode != nullptr;
         pNode = pNode->pNext)
    {
        funA(pNode);
    }
    // 해제
    TNode* pNode = pHead;
    while (pNode)
    {
        TNode* pTemp = pNode->pNext;
        free(pNode);
        pNode = pTemp;
    }

    printf("Hello World!\n");
}
