#include "TStack.h"
void	TStack::ShowAll()
{
	// 단 방향 연결리스트 순회.
	for (TNode* pNode = GetHead()->pNext;
		pNode != GetTail();
		pNode = pNode->pNext)
	{
		Show(pNode);
	}
}
bool	TStack::IsFull()
{
	if (m_iMaxSize == GetCounter())
	{
		return true;
	}
	return false;
}
bool	TStack::IsEmpty()
{
	if (0 == GetCounter())
	{
		return true;
	}
	return false;
}
bool	TStack::Push(TNode* pNewNode)
{
	if (IsFull())
	{
		return false;
	}
	push_front(pNewNode);
	return true;
}
bool	TStack::Pop()
{
	if (IsEmpty())
	{
		return false;
	}
	if (Erase(GetHead()->pNext) == nullptr)
	{
		return false;
	}
	return true;
};
const TNode* const TStack::Top()
{
	const TNode* const pHead = GetHead();
	return pHead->pNext;
}
void    TStack::Show(const TNode* const  pNode)
{
	TLinkedlist::Show(pNode);
}
TStack::TStack()
{
	m_iMaxSize = -1;
}
TStack::TStack(int iMaxSize) : m_iMaxSize(iMaxSize)
{
}
TStack::~TStack()
{

}