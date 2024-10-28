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
	if (IsFull()) return false;
	m_pArray[m_iBack] = pNode;
	m_iBack = (m_iBack + 1) % m_iMaxSize;
	return true;
}
TNode*	TCircularQueueLinkedList::Pop()
{
	if (IsEmpty()) return nullptr;
	TNode* pNode = m_pArray[m_iFront];
	m_pArray[m_iFront] = nullptr; // delete
	m_iFront = (m_iFront + 1) % m_iMaxSize;
	return pNode;
}
bool	TCircularQueueLinkedList::IsFull()
{
	return m_iFront == (m_iBack + 1) % m_iMaxSize;
}
bool	TCircularQueueLinkedList::IsEmpty()
{
	return m_iFront == m_iBack;
	
}
TCircularQueueLinkedList::TCircularQueueLinkedList()
{
	m_iBack = 0;
	m_iFront = 0;
	m_iMaxSize = 10;
	m_pArray = new TNode*[m_iMaxSize];
};
TCircularQueueLinkedList::TCircularQueueLinkedList(int iMaxSize)
{
	m_iBack = 0;
	m_iFront = 0;
	m_iMaxSize = iMaxSize;
	m_pArray = new TNode*[iMaxSize];
};
TCircularQueueLinkedList::~TCircularQueueLinkedList()
{
	delete[] m_pArray;
};