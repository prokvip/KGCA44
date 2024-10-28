#pragma once
#include "LinkedList.h"
class TStack : private TLinkedlist
{
public:
	void	Push(TNode* pNewNode);
	void	Pop();
	const TNode* const 	Top();
	void    Show(const TNode* const pNode);
public:
	TStack();
	~TStack();

};

