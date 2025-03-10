//#include "LinkedList.h"
//
//
//
//template<class T>
//int          TLinkedlist<T>::m_iCurrentCounter = 0;
//
//template<class T>
//TLinkedlist<T>::TLinkedlist()
//{
//    Initialize();
//}
//template<class T>
//TLinkedlist<T>::~TLinkedlist()
//{
//    DeInitialize();
//}
//template<class T>
//bool    TLinkedlist<T>::Ascending(T* a, T* b)
//{
//    if (a > b)
//    {
//        return true;
//    }
//    return false;
//}
//template<class T>
//bool    TLinkedlist<T>::Descending(T* a, T* b)
//{
//    if (a < b)
//    {
//        return true;
//    }
//    return false;
//}
//template<class T>
//void    TLinkedlist<T>::Show(T* pNode)
//{
//    if (pNode != nullptr)
//    {
//        printf("%d ", pNode->iKey);
//    }
//}
//template<class T>
//void    TLinkedlist<T>::push_back(T* pNewNode)
//{
//    // pPreNode -> pNewNode - > g_pTail
//    T* pPreNode = g_pTail->pPrev;
//    pPreNode->pNext = pNewNode;
//    pNewNode->pNext = g_pTail;
//    // pPreNode <- pNewNode <- g_pTail
//    g_pTail->pPrev = pNewNode;
//    pNewNode->pPrev = pPreNode;
//
//    TLinkedlist::m_iCurrentCounter++;
//}
//template<class T>
//void    TLinkedlist<T>::push_front(T* pNewNode)
//{
//    // g_pHead -> pNewNode - > pPostNode
//    T* pPostNode = g_pHead->pNext;
//    g_pHead->pNext = pNewNode;
//    pNewNode->pNext = pPostNode;
//    // g_pHead <- pNewNode <- pPostNode
//    pPostNode->pPrev = pNewNode;
//    pNewNode->pPrev = g_pHead;
//
//    TLinkedlist::m_iCurrentCounter++;
//}
//template<class T>
//void    TLinkedlist<T>::push_back(T* pDestNode, T* pNewNode)
//{
//#ifdef _DEBUG
//    if (pDestNode == nullptr || pNewNode == nullptr)
//    {
//        return;
//    }
//#endif
//    assert(pDestNode);
//    assert(pNewNode);
//    // pDestNode -> pNewNode - > pPostNode
//    T* pPostNode = pDestNode->pNext;
//    pDestNode->pNext = pNewNode;
//    pNewNode->pNext = pPostNode;
//    // pDestNode <- pNewNode <- pPostNode
//    pPostNode->pPrev = pNewNode;
//    pNewNode->pPrev = pDestNode;
//
//    TLinkedlist::m_iCurrentCounter++;
//}
//template<class T>
//void    TLinkedlist<T>::push_front(T* pDestNode, T* pNewNode)
//{
//    /*if (pDestNode == nullptr || pNewNode == nullptr)
//    {
//        return false;
//    }*/
//    assert(pDestNode);
//    assert(pNewNode);
//    // pPreNode -> pNewNode - > pDestNode
//    T* pPreNode = pDestNode->pPrev;
//    pPreNode->pNext = pNewNode;
//    pNewNode->pNext = pDestNode;
//    // pPreNode <- pNewNode <- pDestNode
//    pDestNode->pPrev = pNewNode;
//    pNewNode->pPrev = pPreNode;
//
//    TLinkedlist::m_iCurrentCounter++;
//}
//template<class T>
//void    TLinkedlist<T>::Initialize()
//{
//    // 가상의 머리노드를 생성해 둔다.
//    g_pHead = (T*)malloc(sizeof(T));
//    g_pHead->iKey = -1;
//    g_pTail = (T*)malloc(sizeof(T));
//    g_pTail->iKey = -2;
//
//    g_pHead->pNext = g_pTail;
//    g_pHead->pPrev = nullptr;
//    g_pTail->pNext = nullptr;
//    g_pTail->pPrev = g_pHead;
//
//}
//template<class T>
//void    TLinkedlist<T>::DeInitialize()
//{
//    free(g_pHead);
//    free(g_pTail);
//    g_pHead = nullptr;
//    g_pTail = nullptr;
//}
//template<class T>
//T* TLinkedlist<T>::CreateNode()
//{
//    T* pNewNode = (T*)malloc(sizeof(T));
//    pNewNode->iKey = 0;
//    pNewNode->pNext = nullptr;
//    pNewNode->pPrev = nullptr;
//    return pNewNode;
//}
//template<class T>
//void    TLinkedlist<T>::ShowAll(bool bReverse, void(*Fun)(T*,FILE*), FILE* fp)
//{
//    if (bReverse == false)
//    {
//        // 단 방향 연결리스트 순회.
//        for (T* pNode = g_pHead->pNext;
//            pNode != g_pTail;
//            pNode = pNode->pNext)
//        {
//            if (Fun != nullptr)
//            {
//                Fun(pNode,fp);
//            }
//            else
//            {
//                Show(pNode);
//            }
//        }
//    }
//    else
//    {
//        for (T* pNode = g_pTail->pPrev;
//            pNode != g_pHead;
//            pNode = pNode->pPrev)
//        {
//            Show(pNode);
//        }
//    }
//}
//template<class T>
//T* TLinkedlist<T>::Erase(int iKey)
//{
//    T* pNode = Find(iKey);
//    return Erase(pNode);
//}
//template<class T>
//T* TLinkedlist<T>::Erase(T* pDeleteNode)
//{
//    T* pPreNode = pDeleteNode->pPrev;
//    T* pPostNode = pDeleteNode->pNext;
//    pPreNode->pNext = pPostNode;
//    pPostNode->pPrev = pPreNode;
//    free(pDeleteNode);
//
//    TLinkedlist::m_iCurrentCounter--;
//    return pPreNode;
//}
//template<class T>
//void    TLinkedlist<T>::DeleteAll()
//{
//    // 해제(신규 추가된 노드를 모두 삭제한다.
//    T* pNode = g_pTail->pPrev;
//    while (pNode != g_pHead)
//    {
//        pNode = Erase(pNode);
//    }
//}
//template<class T>
//T* TLinkedlist<T>::Find(int iFindKey, bool bReverse, bool (*Fun)(T*))
//{
//    if (bReverse == false)
//    {
//        T* pNode = g_pHead->pNext;
//        while (pNode != g_pTail)
//        {
//            if (Fun != nullptr)
//            {
//                bool bResult = Fun(pNode);
//                if (bResult == true) return pNode;
//            }
//            else
//            {
//                if (pNode->iKey == iFindKey)
//                {
//                    return pNode;
//                }
//            }
//            pNode = pNode->pNext;
//        }
//    }
//    else
//    {
//        T* pNode = g_pTail->pPrev;
//        while (pNode != g_pHead)
//        {
//            if(Fun != nullptr)
//            {
//                bool bResult = Fun(pNode);
//                if (bResult == true) return pNode;               
//            }
//            else
//            {
//                if (pNode->iKey == iFindKey)
//                {
//                    return pNode;
//                }
//            }
//            pNode = pNode->pPrev;
//        }
//    }
//    return nullptr;
//}
//template<class T>
//T* TLinkedlist<T>::Find(bool (*Fun)(T*))
//{
//    if (Fun == nullptr) return nullptr;
//    T* pNode = g_pHead->pNext;
//    while (pNode != g_pTail)
//    {
//        bool bResult = Fun(pNode);
//        if (bResult == true) return pNode;
//        pNode = pNode->pNext;
//    }    
//    return nullptr;
//}
//template<class T>
//bool TLinkedlist<T>::Swap(T* aNode, T* bNode)
//{
//    //  H, a, 1 , 2, b -> H<->b,<->1, 2, a
//    //  a, 1 , b -> b, 1, a
//    //  a, b -> b, a
//    T* aTemp = aNode;
//    T* aPrev = aNode->pPrev;
//    T* aNext = aNode->pNext;
//    T* bPrev = bNode->pPrev;
//    T* bNext = bNode->pNext;
//
//    //aPrev -> bNode -> aNext -> aNode -> bNext;
//    //aPrev -> bNode -> aNode -> bNext;
//    aPrev->pNext = bNode;
//    if( aNext == bNode)
//    { 
//        bNode->pNext = aNode;
//    }else
//    {
//        bNode->pNext = aNext;
//    }
//   
//    aNext->pNext = aNode;
//    aNode->pNext = bNext;
//
//    //aPrev <- bNode <- aNext <- aNode <- bNext;
//    //aPrev <- bNode <- aNode <- bNext;
//    bNext->pPrev = aNode;
//    if (aNext == bNode)
//    {
//        aNode->pPrev = bNode;
//    }
//    else
//    {
//        aNode->pPrev = aNext;
//    }
//    aNext->pPrev = bNode;
//    bNode->pPrev = aPrev;
//    return true;
//}
//template<class T>
//void   TLinkedlist<T>::Sort(bool (*Fun)(T* a, T* b))
//{
//    if (Fun == nullptr) return;
//    // 10, 6, 9, 1, 7, 2, 3
//    // 6, 10, 9, 1, 7, 2, 3
//    // 6, 3, 9, 1, 7, 2, 10
//   
//    // 2, 6, 9, 1, 7, 2, 3
//    // 2, 6, 9, 1, 7, 2, 3
//    T* pEnd = g_pTail;
//    int iCounter = 0;
//    for (int iCnt=0; iCnt < TLinkedlist::m_iCurrentCounter; iCnt++)
//    {
//        for (T* bNode = g_pHead->pNext;
//            bNode != pEnd;
//            )
//        {
//            T* pNode0 = bNode;
//            T* pNode1 = bNode->pNext;
//            if (pNode1 == g_pTail) break;
//            if (Fun(pNode0, pNode1))
//            {
//                Swap(pNode0, pNode1);
//                bNode = pNode0;
//            }
//            else
//            {
//                bNode = bNode->pNext;
//            }
//            iCounter++;
//        }
//        pEnd = pEnd->pPrev;
//    }
//    printf("\n%d번 비교로 정렬했습니다.", iCounter);
//}
//
//// 0 -> 1 -> 2 -> nullptr
//// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
//// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
//// 주)노드를 추가할 때 마다 꼬리를 저장하고 있으면 
////  직접 꼬리노드에 연결할 수 있다.
//// new 5 insert : // 4(Tail) -> 5 -> nullptr
//
///// 가상의 머리노드(g_pHead)를 사전에 생성해 두고 추가하자.
////  실제 데이터 노드는 g_pHead->pNext부터 연결한다.
//// g_pHead -> 0 -> 1 -> 2 -> nullptr
//// new 3 insert : // 0 -> 1 -> 2 -> 3 -> nullptr
//// new 4 insert : // 0 -> 1 -> 2 -> 3 -> 4 -> nullptr
//// 주)노드를 추가할 때 마다 꼬리를 저장하고 있으면 
////  직접 꼬리노드에 연결할 수 있다.
//// new 5 insert : // 4(Tail) -> 5 -> nullptr