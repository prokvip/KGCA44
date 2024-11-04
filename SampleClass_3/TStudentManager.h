#pragma once
#include "LinkedList.h"

class TStudentManager
{
    TLinkedlist<TStudent>    m_Linkedlist;

    typedef void (TStudentManager::* EXECUTE)();
    EXECUTE m_Execute[10];
public:   
    static void* g_pValueData;
    void SetExecute(void (TStudentManager::*setFun)(),int work)
    { 
        m_Execute[work] = setFun;
    };   
    friend std::ostream& operator <<(std::ostream& os, TStudentManager& a);
    void Execute(int iExeFun)
    {
        if (m_Execute[iExeFun] != nullptr)
        {
            (this->*m_Execute[iExeFun])();
        }        
    }

    void (TStudentManager::* EXECUTEDirect)();
    void ExecuteDirect()
    {
        if (EXECUTEDirect != nullptr)
        {
            (this->*EXECUTEDirect)();
        }        
    }

    TLinkedlist<TStudent>&  GetList() { return m_Linkedlist; }
    TStudent* CreateStudent(int iIndex)
    {
        TStudent* pNewData = new TStudent;// TLinkedlist<TStudent>::CreateNode();
        pNewData->m_iIndex = iIndex;
        pNewData->m_szName[0] = 65 + rand() % 26;
        pNewData->m_szName[1] = 65 + rand() % 26;
        pNewData->m_szName[2] = 65 + rand() % 26;
        pNewData->m_szName[3] = 0;
        pNewData->m_iKor = rand() % 100; // 0 ~ 65535
        pNewData->m_iEng = rand() % 100;
        pNewData->m_iMat = rand() % 100;
        pNewData->m_iTotal =
        pNewData->m_iKor +
        pNewData->m_iEng +
        pNewData->m_iMat;
        pNewData->m_fAverage = 
        pNewData->m_iTotal / 3.0f;
        return pNewData;
    }
    TStudent* CreateStudent(int iIndex, char name[], int iKor, int iEng, int iMat)
    {
        TStudent* pNewData = new TStudent();
        pNewData->m_iIndex = iIndex;
        strcpy_s(pNewData->m_szName, name);
        pNewData->m_iKor = iKor;
        pNewData->m_iEng = iEng;
        pNewData->m_iMat = iMat;
        pNewData->m_iTotal =
            pNewData->m_iKor +
            pNewData->m_iEng +
            pNewData->m_iMat;
        pNewData->m_fAverage =
            pNewData->m_iTotal / 3.0f;
        return pNewData;
    }
    static void    ShowStudent(TNode<TStudent>* pNode, FILE* fp = nullptr)
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
    static void    ShowStudentLine(TNode<TStudent>* pNode, FILE* fp = nullptr)
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
   
    static bool    FindStudent(TNode<TStudent>* pNode)
    {
        int iIndex = *((int*)g_pValueData);
        if (pNode->data.m_iKor == iIndex)
        {
            return true;
        }
        return false;
    }
    static bool    FindStudentFloat(TNode<TStudent>* pNode)
    {
        float iKor = *((float*)g_pValueData);
        if (pNode->data.m_fAverage == iKor)
        {
            return true;
        }
        return false;
    }
    static bool    FindStudentString(TNode<TStudent>* pNode)
    {
        char* iKor = (char*)g_pValueData;
        if (_stricmp(pNode->data.m_szName, iKor) == 0)
        {
            return true;
        }
        return false;
    }
    static bool    AscendingStudent(TNode<TStudent>* a, TNode<TStudent>* b)
    {
        if (a->data.m_iTotal > b->data.m_iTotal)
        {
            return true;
        }
        return false;
    }
    static bool    DescendingStudet(TNode<TStudent>* a, TNode<TStudent>* b)
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
    
    void    PrintData   ();
    void    NewData     ();
    void    FileSave    ();
    void    FileLoad    ();
    void    UpdateData  ();
    void    FindData    ();
    void    DeleteData  ();
    void    SampleData  ();
    void    SortData    ();
};

