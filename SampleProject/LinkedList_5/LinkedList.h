//#define  _CRT_SECURE_NO_WARNINGS
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
    int     iKey;    
    // 고유한 키 생성
    static  unsigned int iKeyIndex;
    // 연결된 노드의 현재 개수
    static  int iCurrentCounter;

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
TNode* CreateNode();
void   ShowAll( bool bReverse = false, 
                void (*Fun)(TNode*, FILE*) = nullptr,
                FILE* fp = nullptr);
TNode* Erase(int iKey);
TNode* Erase(TNode* pDeleteNode);
void    DeleteAll();
TNode* Find(int iFindKey, bool bReverse = false, bool (*Fun)(TNode*)=nullptr);
TNode* Find(bool (*Fun)(TNode*) = nullptr);
bool   Swap(TNode* aNode, TNode* bNode);

bool    Ascending(TNode* a, TNode* b);
bool    Descending(TNode* a, TNode* b);
void   Sort(bool (*Fun)(TNode* a, TNode* b) = Ascending);
