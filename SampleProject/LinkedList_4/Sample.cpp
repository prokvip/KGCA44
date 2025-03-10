#include "LinkedList.h"
#include <string.h>
TNode*  CreateStudent(int iIndex)
{
    TNode* pNewNode = CreateNode(iIndex);
    pNewNode->data.m_iIndex = iIndex;
    pNewNode->data.m_szName[0] = 65 + rand() % 26;
    pNewNode->data.m_szName[1] = 65 + rand() % 26;
    pNewNode->data.m_szName[2] = 65 + rand() % 26;
    pNewNode->data.m_szName[3] = 0;
    pNewNode->data.m_iKor = rand() % 100; // 0 ~ 65535
    pNewNode->data.m_iEng = rand() % 100;
    pNewNode->data.m_iMat = rand() % 100;
    pNewNode->data.m_iTotal = 
        pNewNode->data.m_iKor +
        pNewNode->data.m_iEng +
        pNewNode->data.m_iMat;
    pNewNode->data.m_fAverage = pNewNode->data.m_iTotal / 3.0f;
    return pNewNode;
}
void    ShowStudent(TNode* pNode)
{
    if (pNode != nullptr)
    {
        printf("\n%d %s %d %d %d %d %10.4f", 
                pNode->data.m_iIndex,
            pNode->data.m_szName,
            pNode->data.m_iKor,
            pNode->data.m_iEng,
            pNode->data.m_iMat,
            pNode->data.m_iTotal,
            pNode->data.m_fAverage);
    }
}
void    ShowStudentLine(TNode* pNode)
{
    if (pNode != nullptr)
    {
        printf("\n번호:%d", pNode->data.m_iIndex);
        printf("\n이름:%s", pNode->data.m_szName);
        printf("\n국어:%d", pNode->data.m_iKor );
        printf("\n영어:%d", pNode->data.m_iEng);
        printf("\n수학:%d", pNode->data.m_iMat);
        printf("\n총점:%d", pNode->data.m_iTotal);
        printf("\n평균%10.4f", pNode->data.m_fAverage);
    }
}

void*  g_pValueData=nullptr;
bool    FindStudent(TNode* pNode)
{
    int iKor = *((int*)g_pValueData);
    if (pNode->data.m_iKor == iKor)
    {
        return true;
    }
    return false;
}
bool    FindStudentFloat(TNode* pNode)
{
    float iKor = *((float*)g_pValueData);
    if (pNode->data.m_fAverage == iKor)
    {
        return true;
    }
    return false;
}
bool    FindStudentString(TNode* pNode)
{
    char* iKor = (char*)g_pValueData;
    // error C4996: 'stricmp': The POSIX name for this item is deprecated. Instead, 
    //use the ISO C and C++ conformant name: _stricmp. See online help for details.
    if (_stricmp(pNode->data.m_szName, iKor) ==0 )
    {
        return true;
    }
    return false;
}
void    Title()
{
    printf("\n=========성적관리프로그램=========");
    printf("\n번호 이름 국어 영어 수학 총점 평균");
}
int main()
{
    Initialize();  

    {        
        for (int iNode = 0; iNode < 10; iNode++)
        {
            TNode* pNewNode = CreateStudent(iNode);            
            push_back(pNewNode);                
        }
        ShowAll(false, ShowStudent);

        // 0 -> 1 -> 2 -> nullptr
        // 1) 1 del   g_pHead -> 0 -> 2
        // 2) 2 del   g_pHead -> 0 -> 1        
        // 3) 0 del   g_pHead -> 1 -> 2
        char name[] = "PHQ";
        g_pValueData = name;
        TNode* pNode1 = Find(1, false, FindStudentString);
        TNode* pNode2 = Find(2,true);

        TNode* pNewNode1 = CreateNode(999);
        if (pNewNode1 != nullptr)
        {
            push_back(pNode1, pNewNode1);
        }

        TNode* pNewNode2 = CreateNode(999);
        push_front(pNode1, pNewNode2);

        /*Erase(pNode1);        
        Erase(pNode2);
        Erase(0);*/

        DeleteAll();

        ShowAll(true);
        ShowAll(false);
        for (int iNode = 0; iNode < 5; iNode++)
        {
            push_back(CreateNode(iNode));
        }
        ShowAll();
        DeleteAll();
    }
    Release();
}
