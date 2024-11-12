#include "TBinarySearch.h"
void TBinarySearch::case2(TDataNode* pDeleteNode, TDataNode* pSuccessorNode)
{
	TDataNode* pDeleteParent = pDeleteNode->pParent;
	TDataNode* pSuccessorParent = pSuccessorNode->pParent;

	TDataNode* pDeleteLeft = pDeleteNode->pLeft;
	TDataNode* pDeleteRight = pDeleteNode->pRight;
	TDataNode* pSuccessorLeft = pSuccessorNode->pLeft;
	TDataNode* pSuccessorRight = pSuccessorNode->pRight;

	if (pDeleteParent)
	{
		if (pDeleteParent->pLeft == pDeleteNode) // 왼쪽 자식
		{
			pDeleteParent->pLeft = pSuccessorNode;		
			pSuccessorNode->pLeft = pDeleteLeft;
			if (pDeleteNode != pSuccessorParent)
			{
				pSuccessorNode->pRight = pDeleteRight;
			}
		}
		else
		{
			pDeleteParent->pRight = pSuccessorNode;
			pSuccessorNode->pRight = pDeleteRight;	
			if (pDeleteNode != pSuccessorParent)
			{
				pSuccessorNode->pLeft = pDeleteLeft;
			}
		}
		pSuccessorNode->pParent = pDeleteParent;
	}
	else
	{
		m_pRoot = pSuccessorNode;
		m_pRoot->pLeft = pDeleteLeft;
		m_pRoot->pRight = pDeleteRight;
		m_pRoot->pParent = nullptr;
		pDeleteRight->pParent = pSuccessorNode;
		pDeleteLeft->pParent  = pSuccessorNode;
	}

	if (pDeleteNode == pSuccessorParent)
	{
		pDeleteNode->pParent = pSuccessorNode;
		pDeleteNode->pLeft = pSuccessorLeft;
		pDeleteNode->pRight = pSuccessorRight;
	}
	else
	{
		if (pSuccessorParent->pLeft == pSuccessorNode) 
		{
			pSuccessorParent->pLeft = pSuccessorRight;
		}
		if (pSuccessorParent->pRight == pSuccessorNode) 
		{
			pSuccessorParent->pRight = pSuccessorLeft;
		}		
	}
}
bool TBinarySearch::del(int iData)
{	
	TDataNode* pFindNode = find(iData);
	if (pFindNode == nullptr) return false;
	if (deleteNode(pFindNode)) return true;
		
	TDataNode* pRightSucceed = nullptr;
	TDataNode* pRightParent = pFindNode->pRight;
	while (pRightParent != nullptr)
	{
		pRightSucceed = pRightParent;
		pRightParent = pRightParent->pLeft;		
	}
	case2(pFindNode, pRightSucceed);
	pFindNode->pLeft = nullptr;
	pFindNode->pRight = nullptr;
	delete pFindNode;
	return true;	
}

// case0 , case1
bool TBinarySearch::deleteNode(TDataNode* pDelNode)
{
	// case 0
	TDataNode* pParent = pDelNode->pParent;
	if (pParent == nullptr) return false;
	if (pParent->pLeft == pDelNode)
	{
		// 왼쪽 자식
		if (pDelNode->pLeft == nullptr &&
			pDelNode->pRight == nullptr)
		{
			pParent->pLeft = nullptr;
			delete pDelNode;
			return true;
		}
	}
	else
	{
		// 오른쪽 자식
		// 왼쪽 자식
		if (pDelNode->pLeft == nullptr &&
			pDelNode->pRight == nullptr)
		{
			pParent->pRight = nullptr;
			delete pDelNode;
			return true;
		}
	}
	
	// case 1
	if (pDelNode->pLeft == nullptr )
	{
		// 삭제노드의 오른쪽 노드 존재 부모(Left)-> 삭제노드의 오른쪽 노드
		if (pParent->pLeft == pDelNode)
		{
			pParent->pLeft = pDelNode->pRight;
		}
		// 삭제노드의 왼쪽 노드 존재 부모(Left)-> 삭제노드의 오른쪽 노드
		else
		{
			pParent->pRight = pDelNode->pRight;			
		}		
		pDelNode->pRight->pParent = pParent;
		pDelNode->pLeft = nullptr;
		pDelNode->pRight = nullptr;
		delete pDelNode;
		return true;
	}
	if (pDelNode->pRight == nullptr)
	{
		// 삭제노드의 오른쪽 노드 존재 부모(Left)-> 삭제노드의 오른쪽 노드
		if (pParent->pLeft == pDelNode)
		{
			pParent->pLeft = pDelNode->pLeft;
		}
		// 삭제노드의 왼쪽 노드 존재 부모(Left)-> 삭제노드의 오른쪽 노드
		else
		{
			pParent->pRight = pDelNode->pLeft;
		}
		pDelNode->pLeft->pParent = pParent;
		pDelNode->pLeft = nullptr;
		pDelNode->pRight = nullptr;
		delete pDelNode;
		return true;
	}	
	return false;
}
bool	   TBinarySearch::Add(int iData)
{
	TDataNode* pNode = new TDataNode(iData);
	if (m_pRoot == nullptr)
	{
		m_pRoot = pNode;
		return true;
	}	
	push(m_pRoot, pNode);
}
void	   TBinarySearch::push(TDataNode* pParent, TDataNode* pNewNode)
{
	if (pParent->iData > pNewNode->iData)
	{
		// left
		if (pParent->pLeft == nullptr)
		{
			pParent->pLeft = pNewNode;
			pNewNode->pParent = pParent;
			return;
		}
		push(pParent->pLeft, pNewNode);
	}
	else
	{
		// right
		if (pParent->pRight == nullptr)
		{
			pParent->pRight = pNewNode;
			pNewNode->pParent = pParent;
			return;
		}
		push(pParent->pRight, pNewNode);
	}
}
TDataNode* TBinarySearch::find(int iData)
{
	return get(m_pRoot, iData);
}
TDataNode* TBinarySearch::get(TDataNode* pParent, int iData)
{
	if (pParent == nullptr) return nullptr;
	if (pParent->iData == iData)
	{
		return pParent;
	}
	if (pParent->iData > iData)
	{		
		get(pParent->pLeft, iData);
	}
	else
	{
		get(pParent->pRight, iData);
	}
}
