#include "TStack.h"
void	TStack::Push(TNode* pNewNode)
{
	push_front(pNewNode);
}
void	TStack::Pop()
{
	Erase(GetHead()->pNext);	
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
	int k = 0;
}
TStack::~TStack()
{
	int k = 0;
}