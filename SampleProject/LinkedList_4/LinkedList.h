
/// 양방향 연결리스트,  
// g_pHead(realData)
// g_pHead(virtualData)->realData
// g_pHead(V) ->realData-> g_pTail(V)
// realData -> g_pTail( 대부분 뒤에 삽입)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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
    int     iValue;    
    TNode*  pNext;
    TNode*  pPrev;
};
extern TNode* g_pHead;
extern TNode* g_pTail;

// 자료에 처리의 주요기능
// 초기화, 정리, 치환, 자료생성, 자료해제, 출력, 삽입, 검색, 삭제, 저장, 로드, 정렬
void    Show(TNode* pNode);
//void    Swap(TNode* a, TNode* b);
void    push_back(TNode* pNewNode);
void    push_front(TNode* pNewNode);
void    push_back(TNode* pDestNode, TNode* pNewNode);
void    push_front(TNode* pDestNode, TNode* pNewNode);
void    Initialize();
void    Release();
TNode* CreateNode(int iValue);
void   ShowAll(bool bReverse = false, void (*Fun)(TNode*) = nullptr);
TNode* Erase(int iValue);
TNode* Erase(TNode* pDeleteNode);
void    DeleteAll();
TNode* Find(int iFindValue, bool bReverse = false, bool (*Fun)(TNode*)=nullptr);
