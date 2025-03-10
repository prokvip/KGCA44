#pragma once
#include "LinkedList.h"
class TStack : private TLinkedlist
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
	TStack();
	TStack(int iMaxSize);
	~TStack();

};

