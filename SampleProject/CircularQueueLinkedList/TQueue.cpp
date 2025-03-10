#include "TQueue.h"
void	TQueue::ShowAll()
{
	// 단 방향 연결리스트 순회.
	for (TNode* pNode = GetTail()->pPrev;
		pNode != GetHead();
		pNode = pNode->pPrev)
	{
		Show(pNode);
	}
}
bool	TQueue::IsFull()
{
	if (m_iMaxSize == GetCounter())
	{
		return true;
	}
	return false;
}
bool	TQueue::IsEmpty()
{
	if (0 == GetCounter())
	{
		return true;
	}
	return false;
}
bool	TQueue::Push(TNode* pNewNode)
{
	if (IsFull())
	{
		return false;
	}
	push_front(pNewNode);
	return true;
}
bool	TQueue::Pop()
{
	if (IsEmpty())
	{
		return false;
	}
	if (Erase(GetTail()->pPrev) == nullptr)
	{
		return false;
	}
	return true;
};
const TNode* const TQueue::Top()
{
	const TNode* const pTail = GetTail();
	return pTail->pPrev;
}
void    TQueue::Show(const TNode* const  pNode)
{
	TLinkedlist::Show(pNode);
}
TQueue::TQueue()
{
	m_iMaxSize = -1;
}
TQueue::TQueue(int iMaxSize) : m_iMaxSize(iMaxSize)
{
}
TQueue::~TQueue()
{

}