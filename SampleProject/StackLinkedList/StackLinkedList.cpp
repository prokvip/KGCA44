#include "TStack.h"

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
    TStack stack;
	//TStack stack(3);	
    TNode* pNewNode = CreateStudent(0);
	bool bRet = stack.Push(pNewNode);
    bRet = stack.Push(CreateStudent(1));
    bRet = stack.Push(CreateStudent(2));
    bRet = stack.Push(CreateStudent(3));
    stack.ShowAll();
    //const TNode* const pNode = stack.Top(); 
    stack.Show(stack.Top());
    bRet = stack.Pop();
    bRet = stack.Pop();
    bRet = stack.Pop();
    bRet = stack.Pop();
    stack.ShowAll();
};