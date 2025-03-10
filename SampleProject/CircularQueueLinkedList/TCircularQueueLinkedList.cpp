#include "TCircularQueueLinkedList.h"
//void	TCircularQueueLinkedList::ShowAll()
//{
//	// 단 방향 연결리스트 순회.
//	for (const TNode* pNode = GetHead();
//		pNode != GetTail();
//		pNode = pNode->pPrev)
//	{
//		Show(pNode);		
//	}
//}
bool	TCircularQueueLinkedList::Push(TNode* pNode)
{
	if (IsFull())
	{
		delete pNode;
		return false;
	}
	m_iBack = (m_iBack + 1) % m_iMaxSize;
	m_pArray[m_iBack] = pNode;	
	m_iSize++;
	return true;
}
void TCircularQueueLinkedList::Pop()
{
	if (IsEmpty()) return;
	TNode* pNode = m_pArray[m_iFront];
	delete pNode;
	m_pArray[m_iFront] = nullptr;
	m_iFront = (m_iFront + 1) % m_iMaxSize;
	m_iSize--;
	
}
TNode*	TCircularQueueLinkedList::Top()
{
	if (IsEmpty()) return nullptr;	
	TNode* pNode = m_pArray[m_iFront];	
	return pNode;
}

bool	TCircularQueueLinkedList::IsFull()
{
	//return m_iFront == (m_iBack + 1) % m_iMaxSize;
	return m_iSize == m_iMaxSize;
}
bool	TCircularQueueLinkedList::IsEmpty()
{
	//return m_iFront == m_iBack;
	return m_iSize == 0;
	
}
TCircularQueueLinkedList::TCircularQueueLinkedList()
{
	m_iMaxSize = 10;
	m_iSize = m_iFront = 0;
	m_iBack = m_iMaxSize-1;	
	m_pArray = new TNode*[m_iMaxSize];
};
TCircularQueueLinkedList::TCircularQueueLinkedList(int iMaxSize)
{
	m_iMaxSize = iMaxSize;
	m_iSize = m_iFront = 0;
	m_iBack = m_iMaxSize - 1;
	m_pArray = new TNode*[iMaxSize];
};
TCircularQueueLinkedList::~TCircularQueueLinkedList()
{
	delete[] m_pArray;
};