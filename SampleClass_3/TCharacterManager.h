#pragma once
#include "LinkedList.h"
//1 > F:\KGCA44\SampleClass_3\LinkedList.h(48, 2) : error C2953 : 'TLinkedlist' : 클래스 템플릿이 이미 정의되었습니다.

class TCharacterManager
{
    TLinkedlist<TNodeCharacter>    m_Linkedlist;

    typedef void (TCharacterManager::* EXECUTE)();
    EXECUTE m_Execute[10];
public:
    static void* g_pValueData;
    void SetExecute(void (TCharacterManager::* setFun)(), int work)
    {
        m_Execute[work] = setFun;
    };
    void Execute(int iExeFun)
    {
        if (m_Execute[iExeFun] != nullptr)
        {
            (this->*m_Execute[iExeFun])();
        }
    }

    void (TCharacterManager::* EXECUTEDirect)();
    void ExecuteDirect()
    {
        if (EXECUTEDirect != nullptr)
        {
            (this->*EXECUTEDirect)();
        }
    }

    TLinkedlist<TNodeCharacter>& GetList() { return m_Linkedlist; }
    TNodeCharacter* CreateStudent(int iIndex)
    {
        TNodeCharacter* pNewNode = TLinkedlist<TNodeCharacter>::CreateNode();
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
    TNodeCharacter* CreateStudent(int iIndex, char name[], int iKor, int iEng, int iMat)
    {
        TNodeCharacter* pNewNode = TLinkedlist<TNodeCharacter>::CreateNode();
        pNewNode->data.m_iIndex = iIndex;
        //strcpy(pNewNode->data.m_szName, name);
        strcpy_s(pNewNode->data.m_szName, name);
        pNewNode->data.m_iKor = iKor;
        pNewNode->data.m_iEng = iEng;
        pNewNode->data.m_iMat = iMat;
        pNewNode->data.m_iTotal =
            pNewNode->data.m_iKor +
            pNewNode->data.m_iEng +
            pNewNode->data.m_iMat;
        pNewNode->data.m_fAverage = pNewNode->data.m_iTotal / 3.0f;
        return pNewNode;
    }
    static void    ShowStudent(TNodeCharacter* pNode, FILE* fp = nullptr)
    {
        if (pNode == nullptr) return;
        if (fp == nullptr)
        {
            printf("\nKey[%d] %d %s %d %d %d %d %10.4f", pNode->iKey,
                pNode->data.m_iIndex,
                pNode->data.m_szName,
                pNode->data.m_iKor,
                pNode->data.m_iEng,
                pNode->data.m_iMat,
                pNode->data.m_iTotal,
                pNode->data.m_fAverage);
        }
        else
        {
            fprintf(fp, "%d %d %s %d %d %d %d %10.4f\n", pNode->iKey,
                pNode->data.m_iIndex,
                pNode->data.m_szName,
                pNode->data.m_iKor,
                pNode->data.m_iEng,
                pNode->data.m_iMat,
                pNode->data.m_iTotal,
                pNode->data.m_fAverage);
        }
    }
    static void    ShowStudentLine(TNodeCharacter* pNode, FILE* fp = nullptr)
    {
        if (pNode == nullptr) return;
        if (fp == nullptr)
        {
            printf("\nKEY:%d", pNode->iKey);
            printf("\n번호:%d", pNode->data.m_iIndex);
            printf("\n이름:%s", pNode->data.m_szName);
            printf("\n국어:%d", pNode->data.m_iKor);
            printf("\n영어:%d", pNode->data.m_iEng);
            printf("\n수학:%d", pNode->data.m_iMat);
            printf("\n총점:%d", pNode->data.m_iTotal);
            printf("\n평균%10.4f", pNode->data.m_fAverage);
        }
    }

    static bool    FindStudent(TNodeCharacter* pNode)
    {
        int iIndex = *((int*)g_pValueData);
        if (pNode->data.m_iKor == iIndex)
        {
            return true;
        }
        return false;
    }
    static bool    FindStudentFloat(TNodeCharacter* pNode)
    {
        float iKor = *((float*)g_pValueData);
        if (pNode->data.m_fAverage == iKor)
        {
            return true;
        }
        return false;
    }
    static bool    FindStudentString(TNodeCharacter* pNode)
    {
        char* iKor = (char*)g_pValueData;
        if (_stricmp(pNode->data.m_szName, iKor) == 0)
        {
            return true;
        }
        return false;
    }
    static bool    AscendingStudent(TNodeCharacter* a, TNodeCharacter* b)
    {
        if (a->data.m_iTotal > b->data.m_iTotal)
        {
            return true;
        }
        return false;
    }
    static bool    DescendingStudet(TNodeCharacter* a, TNodeCharacter* b)
    {
        if (a->data.m_iTotal < b->data.m_iTotal)
        {
            return true;
        }
        return false;
    }
    void    Title()
    {
        printf("\n=========성적관리프로그램=========");
        //printf("\n번호 이름 국어 영어 수학 총점 평균");
    }

    void    PrintData();
    void    NewData();
    void    FileSave();
    void    FileLoad();
    void    UpdateData();
    void    FindData();
    void    DeleteData();
    void    SampleData();
    void    SortData();
};

