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
		if (pDeleteParent->pLeft == pDeleteNode) 
		{
			pDeleteParent->pLeft = pSuccessorNode;					
		}
		else
		{
			pDeleteParent->pRight = pSuccessorNode;
		}
		if (pDeleteLeft != pSuccessorNode)
		{			
			pSuccessorNode->pLeft = pDeleteLeft;
			if (pDeleteLeft)pDeleteLeft->pParent = pSuccessorNode;
		}		
		if (pDeleteRight != pSuccessorNode)
		{
			pSuccessorNode->pRight = pDeleteRight;
			if (pDeleteRight)pDeleteRight->pParent = pSuccessorNode;
		}		
		pSuccessorNode->pParent = pDeleteParent;
	}
	else
	{
		m_pRoot = pSuccessorNode;
		if ( pDeleteLeft != pSuccessorNode)
		{
			m_pRoot->pLeft = pDeleteLeft;
			if (pDeleteLeft)pDeleteLeft->pParent = pSuccessorNode;
		}
		if (pDeleteRight != pSuccessorNode)
		{
			m_pRoot->pRight = pDeleteRight;
			if (pDeleteRight)pDeleteRight->pParent = pSuccessorNode;
		}
		m_pRoot->pParent = nullptr;		
	}
	if (pDeleteNode != pSuccessorParent)
	{		
		if (pSuccessorParent->pLeft == pSuccessorNode) 
		{
			pSuccessorParent->pLeft = pSuccessorRight;
			if(pSuccessorRight)pSuccessorRight->pParent = pSuccessorParent;
		}
		if (pSuccessorParent->pRight == pSuccessorNode) 
		{
			pSuccessorParent->pRight = pSuccessorLeft;
			if (pSuccessorLeft)pSuccessorLeft->pParent = pSuccessorParent;
		}		
		pDeleteNode->pParent = nullptr;
		pDeleteNode->pLeft = nullptr;
		pDeleteNode->pRight = nullptr;
		delete pDeleteNode;
		UpdateHeight(pSuccessorParent);
	}
	else
	{
		pDeleteNode->pParent = nullptr;
		pDeleteNode->pLeft = nullptr;
		pDeleteNode->pRight = nullptr;
		delete pDeleteNode;
		UpdateHeight(pSuccessorNode);
	}	
}
TDataNode* TBinarySearch::GetSuccessorRight(TDataNode* pNode)
{
	TDataNode* pSuccessor = nullptr;
	TDataNode* pNext = pNode->pRight;
	while (pNext != nullptr)
	{
		pSuccessor = pNext;
		pNext = pNext->pLeft;
	}
	return pSuccessor;
}
TDataNode* TBinarySearch::GetSuccessorLeft(TDataNode* pNode)
{
	TDataNode* pSuccessor = nullptr;
	TDataNode* pNext = pNode->pLeft;
	while (pNext != nullptr)
	{
		pSuccessor = pNext;
		pNext = pNext->pRight;
	}
	return pSuccessor;
}
bool TBinarySearch::del(int iData)
{	
	TDataNode* pFindNode = find(iData);
	if (pFindNode == nullptr) return false;
	if (deleteNode(pFindNode)) return true;
		
	TDataNode* pSuccessor = nullptr;
	int iBalanceFactor = GetBalance(pFindNode);
	if (iBalanceFactor >= 0)
		pSuccessor = GetSuccessorLeft(pFindNode);
	else
		pSuccessor = GetSuccessorRight(pFindNode);

	if (pSuccessor != nullptr)
	{
		case2(pFindNode, pSuccessor);
	}
	else
	{
		if (pFindNode->pLeft == nullptr && pFindNode->pRight == nullptr)
		{
			delete pFindNode;
			m_pRoot = nullptr;
			return true;
		}
		if (pFindNode->pLeft != nullptr)
		{
			m_pRoot = pFindNode->pLeft;
		}
		if (pFindNode->pRight != nullptr)
		{
			m_pRoot = pFindNode->pRight;
		}
		m_pRoot->pParent = nullptr;
		pFindNode->pLeft = nullptr;
		pFindNode->pRight = nullptr;
		delete pFindNode;
	}
	return true;	
}

// case0 , case1
bool TBinarySearch::deleteNode(TDataNode* pDelNode)
{
	// case 0
	TDataNode* pParent = pDelNode->pParent;
	if (pParent == nullptr)
	{		
		return false;
	}
	if (pParent->pLeft == pDelNode)
	{
		if (pDelNode->pLeft == nullptr &&	pDelNode->pRight == nullptr)
		{
			pParent->pLeft = nullptr;
			delete pDelNode;
			UpdateHeight(pParent);
			return true;
		}
	}
	else
	{
		if (pDelNode->pLeft == nullptr &&	pDelNode->pRight == nullptr)
		{
			pParent->pRight = nullptr;
			delete pDelNode;
			UpdateHeight(pParent);
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
		UpdateHeight(pParent);
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
		UpdateHeight(pParent);
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
		if (pPNode->pLeft == pANode)
			pPNode->pLeft = pBNode;//
		if (pPNode->pRight == pANode)
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
		if (pPNode->pLeft == pANode)
		{
			pPNode->pLeft = pBNode;
		}
		else
		{
			pPNode->pRight = pBNode;
		}
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

			int iBF = GetBalance(pBNode);
			//if (pCNode != nullptr)// D
			if (iBF >=0  )
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
				if (pbNode)pbNode->pParent = pBNode;
				
				// RR Rotation
				RRRotation(pPNode,
					pANode,
					pANode->pLeft,
					pANode->pLeft->pLeft);
				UpdateHeight(pBNode);
			}
		}
		if (iBalanceFactor < -1)
		{
			TDataNode* pPNode = pNode->pParent;
			TDataNode* pANode = pNode;
			TDataNode* pBNode = pNode->pRight;
			TDataNode* pCNode = pBNode->pRight;
			TDataNode* pcNode = pBNode->pLeft;

			int iBF = GetBalance(pBNode);
			if( iBF <= 0)
			//if (pCNode != nullptr)// D
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
				if(pbNode)pbNode->pParent = pBNode;

				// RR Rotation
				LLRotation(pPNode,
					pANode,
					pANode->pRight,
					pANode->pRight->pRight);
				UpdateHeight(pBNode);
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