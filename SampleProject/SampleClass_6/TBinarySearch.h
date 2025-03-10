#pragma once
#include <iostream>

#ifndef max
#define max(a,b) (((a)>(b)) ? (a) : (b))
#endif
struct TDataNode
{
	int iData;
	int iHeight;
	TDataNode* pParent = nullptr;
	TDataNode* pLeft=nullptr;
	TDataNode* pRight = nullptr;
	TDataNode(int iData)
	{
		this->iData = iData;
		iHeight = 1;
	}
	TDataNode() {
	};
	~TDataNode() {
		if( pLeft != nullptr)		delete pLeft;
		if (pRight != nullptr)		delete pRight;
	};
};

class TBinarySearch
{
public:
	TDataNode* m_pRoot;
	bool		Add(int iData);
	bool		push(TDataNode* , TDataNode* );
	TDataNode*  find(int iData);
	TDataNode*  get(TDataNode* pParent, int iData);
	bool		del(int iData);
	bool		deleteNode(TDataNode* pParent);
	void		case2(TDataNode* pDelNode, TDataNode* pSuccessorNode);

public:
	TDataNode*  UpdateHeight(TDataNode* pNode);
	int			GetHeight(TDataNode* pNode);
	int			GetBalance(TDataNode* pNode);
	TDataNode*	GetSuccessorRight(TDataNode* pNode);
	TDataNode*	GetSuccessorLeft(TDataNode* pNode);
public:
	void	   RRRotation(
		TDataNode* pPNode,
		TDataNode* pANode,
		TDataNode* pBNode,
		TDataNode* pCNode);
	void	   LLRotation(
		TDataNode* pPNode,
		TDataNode* pANode,
		TDataNode* pBNode,
		TDataNode* pCNode);
	TBinarySearch() : m_pRoot(nullptr)
	{

	}
};

