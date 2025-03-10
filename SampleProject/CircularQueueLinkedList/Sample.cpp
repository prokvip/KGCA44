#include "TCircularQueueLinkedList.h"

TNode* CreateStudent(int iIndex)
{
    TNode* pNewNode = TLinkedlist::CreateNode();
    pNewNode->iKey = ++TNode::iKeyIndex;
    pNewNode->data.m_iIndex = iIndex;
    pNewNode->data.m_szName[0] = 65 + rand() % 26;
    pNewNode->data.m_szName[1] = 65 + rand() % 26;
    pNewNode->data.m_szName[2] = 65 + rand() % 26;
    pNewNode->data.m_szName[3] = 0;
    pNewNode->data.m_iKor = rand() % 100; // 0 ~ 65535
    pNewNode->data.m_iEng = rand() % 100;
    pNewNode->data.m_iMat = rand() % 100;
    pNewNode->data.m_iTotal =
        pNewNode->data.m_iKor +
        pNewNode->data.m_iEng +
        pNewNode->data.m_iMat;
    pNewNode->data.m_fAverage = pNewNode->data.m_iTotal / 3.0f;
    return pNewNode;
}

void main()
{
    //TCircularQueueLinkedList quque;
    TCircularQueueLinkedList quque(4); // 4-1 = 3
    // -, -, 7, -
	bool bRet = quque.Push(CreateStudent(0));
    bRet = quque.Push(CreateStudent(1));
    bRet = quque.Push(CreateStudent(2));
    bRet = quque.Push(CreateStudent(3)); 
    bRet = quque.Push(CreateStudent(4)); // full
    
    quque.Pop();
    TNode* pNode = quque.Top();
    pNode = quque.Top();

    quque.Pop();
    quque.Pop();
    quque.Pop();
    quque.Pop();
    quque.Pop();


   /* bRet = quque.Push(CreateStudent(4));    
    bRet = quque.Pop();
    bRet = quque.Push(CreateStudent(5));
    bRet = quque.Pop();
    bRet = quque.Push(CreateStudent(6));
    bRet = quque.Top();
    bRet = quque.Top();
    bRet = quque.Top();
    bRet = quque.Top();*/
};