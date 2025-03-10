#pragma once
#include <iostream>

struct TDataNode
{
	int iData;
	TDataNode* pLeft=nullptr;
	TDataNode* pRight = nullptr;
	TDataNode(int iData)
	{
		this->iData = iData;
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
	void		push(TDataNode* , TDataNode* );
	TDataNode* find(int iData);
	TDataNode* get(TDataNode* pParent, int iData);
	TBinarySearch() : m_pRoot(nullptr)
	{

	}
};

