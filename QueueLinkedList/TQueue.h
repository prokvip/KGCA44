#pragma once
#include "LinkedList.h"
class TQueue : private TLinkedlist
{
	int		m_iMaxSize;
public:
	bool	Push(TNode* pNewNode);
	bool	Pop();
	const TNode* const 	Top();
	bool	IsFull();
	bool	IsEmpty();
	void    Show(const TNode* const pNode);
	void    ShowAll();
public:
	TQueue();
	TQueue(int iMaxSize);
	~TQueue();

};

