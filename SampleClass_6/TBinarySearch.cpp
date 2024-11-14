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
			pDeleteLeft->pParent = pSuccessorNode;
			if (pDeleteNode != pSuccessorParent)
			{
				pSuccessorNode->pRight = pDeleteRight;
			}
		}
		else
		{
			pDeleteParent->pRight = pSuccessorNode;
			pSuccessorNode->pLeft = pDeleteLeft;	
			pDeleteLeft->pParent = pSuccessorNode;
			if (pDeleteNode != pSuccessorParent)
			{
				pSuccessorNode->pRight = pDeleteRight;
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

	if (pDeleteNode != pSuccessorParent)
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
	pDeleteNode->pParent = nullptr;
	pDeleteNode->pLeft = nullptr;
	pDeleteNode->pRight = nullptr;
	delete pDeleteNode;
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
	return push(m_pRoot, pNode);	
}
bool	   TBinarySearch::push(TDataNode* pParent, TDataNode* pNewNode)
{
	if (pParent->iData > pNewNode->iData)
	{
		// left
		if (pParent->pLeft == nullptr)
		{
			pParent->pLeft = pNewNode;
			pNewNode->pParent = pParent;
			UpdateHeight(pNewNode->pParent);
			return true;
		}
		else
		{
			push(pParent->pLeft, pNewNode);
		}
	}
	else
	{
		// right
		if (pParent->pRight == nullptr)
		{
			pParent->pRight = pNewNode;
			pNewNode->pParent = pParent;
			UpdateHeight(pNewNode->pParent);			
			return true;
		}
		else
		{
			push(pParent->pRight, pNewNode);
		}
	}
	return false;
}
TDataNode* TBinarySearch::find(int iData)
{
	return get(m_pRoot, iData);
}
TDataNode* TBinarySearch::get(TDataNode* pParent, int iData)
{
	if (pParent == nullptr) return nullptr;
	TDataNode* pRet = nullptr;
	if (pParent->iData == iData)
	{
		return pParent;
	}
	if (pParent->iData > iData)
	{		
		pRet = get(pParent->pLeft, iData);
	}
	else
	{
		pRet = get(pParent->pRight, iData);
	}
	return pRet;
}
int			TBinarySearch::GetBalance(TDataNode* pNode)
{
	if (pNode == nullptr) return 0;
	return GetHeight(pNode->pLeft) - GetHeight(pNode->pRight);
}
void	   TBinarySearch::RRRotation(
	TDataNode* pPNode,
	TDataNode* pANode,
	TDataNode* pBNode,
	TDataNode* pCNode )
{
	// RR Rotation
	if (pPNode)
	{
		pPNode->pLeft = pBNode;//
		pBNode->pParent = pPNode;//
	}
	else
	{
		m_pRoot = pBNode;
		pBNode->pParent = nullptr;		
	}

	if (pBNode)
	{
		TDataNode* cNode = pBNode->pRight;
		pBNode->pRight = pANode;
		pANode->pParent = pBNode;
		pANode->pLeft = cNode;
		if (cNode!=nullptr)
		{
			cNode->pParent = pANode;
		}
	}
	UpdateHeight(pANode);
}
void	   TBinarySearch::LLRotation(
	TDataNode* pPNode,
	TDataNode* pANode,
	TDataNode* pBNode,
	TDataNode* pCNode)
{
	// RR Rotation
	if (pPNode)
	{
		pPNode->pRight = pBNode;//
		pBNode->pParent = pPNode;//
	}
	else
	{
		m_pRoot = pBNode;
		pBNode->pParent = nullptr;
	}

	if (pBNode)
	{
		TDataNode* cNode = pBNode->pLeft;
		pBNode->pLeft = pANode;
		pANode->pParent = pBNode;
		pANode->pRight = cNode;
		if (cNode != nullptr)
		{
			cNode->pParent = pANode;
		}
	}
	UpdateHeight(pANode);
}
TDataNode* TBinarySearch::UpdateHeight(TDataNode* pNode)
{
	int iLeftHeight = GetHeight(pNode->pLeft);
	int iRightHeight = GetHeight(pNode->pRight);
	pNode->iHeight = 1 + max(iLeftHeight, iRightHeight);
	int iBalanceFactor = GetBalance(pNode);
	if (iBalanceFactor > 1 || iBalanceFactor < -1)
	{
		if (iBalanceFactor > 1) {
			TDataNode* pPNode = pNode->pParent;
			TDataNode* pANode = pNode;
			TDataNode* pBNode = pNode->pLeft;			
			TDataNode* pCNode = pBNode->pLeft;

			
			if (pCNode != nullptr)// D
			{
				// RR Rotation
				RRRotation(pPNode, pANode, pBNode, pCNode);				
			}
			else
			{
				TDataNode* pcNode = pBNode->pRight;
				TDataNode* pbNode = pcNode->pLeft;

				pANode->pLeft = pcNode;
				pcNode->pParent = pANode;
				pcNode->pLeft = pBNode;
				pBNode->pParent = pcNode;
				pBNode->pRight = pbNode;
				// RR Rotation
				RRRotation(pPNode,
					pANode,
					pCNode,
					pBNode);
			}
		}
		if (iBalanceFactor < -1)
		{
			TDataNode* pPNode = pNode->pParent;
			TDataNode* pANode = pNode;
			TDataNode* pBNode = pNode->pRight;
			TDataNode* pCNode = pBNode->pRight;
			TDataNode* pcNode = pBNode->pLeft;
			if (pCNode != nullptr)// D
			{
				// RR Rotation
				LLRotation(pPNode, pANode, pBNode, pCNode);
			}
			else
			{
				TDataNode* pcNode = pBNode->pLeft;
				TDataNode* pbNode = pcNode->pRight;
				pANode->pRight = pcNode;
				pcNode->pParent = pANode;
				pcNode->pRight = pBNode;
				pBNode->pParent = pcNode;
				pBNode->pLeft = pbNode;
				// RR Rotation
				LLRotation(pPNode,
					pANode,
					pCNode,
					pBNode);
			}
		}
	}
	else
	{
		if (pNode->pParent != nullptr)
		{
			UpdateHeight(pNode->pParent);
		}
	}
	return pNode;
}
int TBinarySearch::GetHeight(TDataNode* pNode)
{
	if (pNode == nullptr) return 0;
	return pNode->iHeight;
}