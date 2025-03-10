#include "TBinarySearch.h"
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
