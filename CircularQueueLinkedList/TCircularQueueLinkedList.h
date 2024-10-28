#pragma once
#include "Linkedlist.h"
class TCircularQueueLinkedList //: private TLinkedlist
{
	int		m_iMaxSize;
	TNode**  m_pArray = nullptr; 
	int		m_iBack;
	int		m_iFront;
public:
	bool	Push(TNode* pNode);
	TNode*	Pop();
	bool	IsFull();
	bool	IsEmpty();
public:
	//void    ShowAll();
	TCircularQueueLinkedList();
	TCircularQueueLinkedList(int iMaxSize);
	~TCircularQueueLinkedList();
};

