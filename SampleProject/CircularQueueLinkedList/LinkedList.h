//#define  _CRT_SECURE_NO_WARNINGS
/// ����� ���Ḯ��Ʈ,  
// g_pHead(realData)
// g_pHead(virtualData)->realData
// g_pHead(V) ->realData-> g_pTail(V)
// realData -> g_pTail( ��κ� �ڿ� ����)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>

struct TStudent
{
    char m_szName[4];
    int  m_iIndex;
    int m_iKor;
    int m_iEng;
    int m_iMat;
    int m_iTotal;
    float m_fAverage;/*
    TStudent* pNext;
    TStudent* pPrev;*/
};

struct TNode
{
    TStudent data;
    int     iKey;    
    TNode*  pNext;
    TNode*  pPrev;
    // ������ Ű ����
    static  unsigned int iKeyIndex;
};

class TLinkedlist
{
private:
    TNode* g_pHead;
    TNode* g_pTail;
    // ����� ����� ���� ����
    static  int m_iCurrentCounter;   
public:
    const TNode* const GetHead() { return g_pHead; }
    const TNode* const GetTail() { return g_pTail; }
    int   GetCounter() { return m_iCurrentCounter; }
    // �ڷῡ ó���� �ֿ���
    // �ʱ�ȭ, ����, ġȯ, �ڷ����, �ڷ�����, ���, ����, �˻�, ����, ����, �ε�, ����
    void    Show(const TNode* const pNode) const;
    void    push_back(TNode* pNewNode);
    void    push_front(TNode* pNewNode);
    void    push_back(TNode* pDestNode, TNode* pNewNode);
    void    push_front(TNode* pDestNode, TNode* pNewNode);
    void    Initialize();
    void    DeInitialize();
    
    void   ShowAll( bool bReverse = false, 
                    void (*Fun)(TNode*, FILE*) = nullptr,
                    FILE* fp = nullptr);
    TNode* Erase(int iKey);
    TNode* Erase(TNode* pDeleteNode);
    void    DeleteAll();
    TNode* Find(int iFindKey, bool bReverse = false, 
                bool (*Fun)(TNode*)=nullptr);
    TNode* Find(bool (*Fun)(TNode*) = nullptr);
    bool   Swap(TNode* aNode, TNode* bNode);
    void   Sort(bool (*Fun)(TNode* a, TNode* b) = Ascending);
public:
    static TNode* CreateNode();
    static bool    Ascending(TNode* a, TNode* b);
    static bool    Descending(TNode* a, TNode* b);
public:
    TLinkedlist();
    ~TLinkedlist();
};
