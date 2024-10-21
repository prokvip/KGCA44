//error C4996: 'scanf': This function or variable may be unsafe. Consider using scanf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
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
TNode* CreateStudent(int iIndex, char name[], int iKor, int iEng, int iMat)
{
    TNode* pNewNode = CreateNode(iIndex);
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
void    ShowStudent(TNode* pNode, FILE* fp=nullptr)
{
    if (pNode == nullptr) return;
    if (fp == nullptr)
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
    else
    {        
        fprintf(fp,"%d %s %d %d %d %d %10.4f\n",
            pNode->data.m_iIndex,
            pNode->data.m_szName,
            pNode->data.m_iKor,
            pNode->data.m_iEng,
            pNode->data.m_iMat,
            pNode->data.m_iTotal,
            pNode->data.m_fAverage);
    }
}
void    ShowStudentLine(TNode* pNode, FILE* fp=nullptr)
{
    if (pNode == nullptr) return;
    if (fp == nullptr)
    {
        printf("\n번호:%d", pNode->data.m_iIndex);
        printf("\n이름:%s", pNode->data.m_szName);
        printf("\n국어:%d", pNode->data.m_iKor);
        printf("\n영어:%d", pNode->data.m_iEng);
        printf("\n수학:%d", pNode->data.m_iMat);
        printf("\n총점:%d", pNode->data.m_iTotal);
        printf("\n평균%10.4f", pNode->data.m_fAverage);        
    }
    else
    {
        fprintf(fp,"\n번호:%d", pNode->data.m_iIndex);
        fprintf(fp, "\n이름:%s", pNode->data.m_szName);
        fprintf(fp, "\n국어:%d", pNode->data.m_iKor);
        fprintf(fp, "\n영어:%d", pNode->data.m_iEng);
        fprintf(fp, "\n수학:%d", pNode->data.m_iMat);
        fprintf(fp, "\n총점:%d", pNode->data.m_iTotal);
        fprintf(fp, "\n평균%10.4f", pNode->data.m_fAverage);
    }
}

void*  g_pValueData=nullptr;
bool    FindStudent(TNode* pNode)
{
    int iIndex = *((int*)g_pValueData);
    if (pNode->data.m_iKor == iIndex)
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
    //printf("\n번호 이름 국어 영어 수학 총점 평균");
}
enum WORK { PRINT, NEW_DATA, FILE_SAVE, FILE_LOAD,
            UPDATE, SAMPLE_DATA, EXIT=99};
void  Print();
void  NewData();
void  FileSave();
void  FileLoad();
void  Update();
void  SampleData();

void (*WORK)();
int main()
{
    Initialize();
    int iWork = 0;
    bool workRun = true;
    while (workRun)
    {        
        Title();
        printf("\nPRINT(0) NEW_DATA(1)FILE_SAVE(2) FILE_LOAD(3)UPDATE(4) SAMPLE_DATA(5) EXIT(99)");
        //scanf("%d", &iWork);
        scanf_s("%d", &iWork);
        
        switch (iWork)
        {
            case SAMPLE_DATA:
            {
                WORK = SampleData;
            }break;
            case PRINT:
            {
                WORK = Print;
            }break;
            case NEW_DATA:
            {
                WORK = NewData;
            }break;
            case FILE_SAVE:
            {
                WORK = FileSave;
            }break;
            case FILE_LOAD:
            {
                WORK = FileLoad;
            }break;
            case UPDATE:
            {
                 WORK = Update; 
            }break;
            case EXIT:
            {
                workRun = false;
            }break;
        }
        
        WORK();
    }
    Release();
}


void  Print(){
    system("cls");
    ShowAll(false, ShowStudent);
}
void  NewData()
{
    char name[4] = { 0, };
    int iKor, iEng, iMat;
    scanf_s("%s %d %d %d", name, _countof(name), &iKor, &iEng, &iMat);
    TNode* pNewNode1 = CreateStudent(999, name, iKor, iEng, iMat);
    if (pNewNode1 != nullptr)
    {
        push_back(pNewNode1);
    }
}
void  FileSave()
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "w");
    int iNodeCounter = 3;
    fprintf(fp, "%d\n", iNodeCounter);
    ShowAll(false, ShowStudent, fp);
    fclose(fp);
}
void  FileLoad()
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "r");
    int iNodeCounter = 3;
    fscanf_s(fp, "%d\n",&iNodeCounter);
    for (int iNode = 0; iNode < iNodeCounter; iNode++)
    {
        char name[4] = { 0, };
        int iKor, iEng, iMat, iTotal;
        float fAvg;

        int id;
        char buffer[256] = { 0 , };
        fgets(buffer, 256, fp);
        sscanf_s(buffer,"%d %s %d %d %d\n", &id, name, _countof(name), &iKor, &iEng, &iMat, &iTotal, &fAvg);
        TNode* pNewNode1 = CreateStudent(id, name, iKor, iEng, iMat);
        if (pNewNode1 != nullptr)
        {
            push_back(pNewNode1);
        }
    }
    ShowAll(false, ShowStudent, fp);
    fclose(fp);
};
void  Update(){
    int iIndex;
    printf("index= ");
    scanf_s("%d", &iIndex);
    TNode* pNode = Find(iIndex);
    ShowStudent(pNode);

    char name[4] = { 0, };
    int iKor, iEng, iMat;
    scanf_s("%s %d %d %d", pNode->data.m_szName, _countof(pNode->data.m_szName),
        &pNode->data.m_iKor, &pNode->data.m_iEng, &pNode->data.m_iMat);

}
void  SampleData()
{
    for (int iNode = 0; iNode < 3; iNode++)
    {
        TNode* pNewNode = CreateStudent(iNode);
        push_back(pNewNode);
    }
}