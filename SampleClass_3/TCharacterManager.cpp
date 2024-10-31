#include "TCharacterManager.h"
void* TCharacterManager::g_pValueData = nullptr;
void  TCharacterManager::PrintData() {
    system("cls");
    m_Linkedlist.ShowAll(false, ShowStudent);
}
void  TCharacterManager::NewData()
{
    char name[4] = { 0, };
    int iID, iKor, iEng, iMat;
    printf("\n이름,번호,국어,영어,수학 : ");
    scanf_s("%s %d %d %d %d", name, _countof(name), &iID, &iKor, &iEng, &iMat);
    TNodeCharacter* pNewNode = CreateStudent(iID, name, iKor, iEng, iMat);
    if (pNewNode != nullptr)
    {
        pNewNode->iKey = ++TNodeCharacter::iKeyIndex;
        m_Linkedlist.push_back(pNewNode);
    }
}
void  TCharacterManager::FileSave()
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "w");
    fprintf(fp, "%d %d\n", m_Linkedlist.GetCounter(), TNodeCharacter::iKeyIndex);
    m_Linkedlist.ShowAll(false, ShowStudent, fp);
    fclose(fp);
}
void  TCharacterManager::FileLoad()
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "r");
    if (fp != nullptr)
    {
        m_Linkedlist.DeleteAll();
    }

    char buffer[256] = { 0 , };
    int iNodeCounter = 3;
    fgets(buffer, 256, fp);
    sscanf_s(buffer, "%d %d", &iNodeCounter, &TNodeCharacter::iKeyIndex);

    //fscanf_s(fp, "%d %d\n",&iNodeCounter, &TNodeCharacter::iKeyIndex);
    for (int iNode = 0; iNode < iNodeCounter; iNode++)
    {
        char name[4] = { 0, };
        int iKor, iEng, iMat, iTotal;
        float fAvg;

        int id, iKey;

        fgets(buffer, 256, fp);
        sscanf_s(buffer, "%d %d %s %d %d %d\n", &iKey, &id, name, _countof(name), &iKor, &iEng, &iMat, &iTotal, &fAvg);
        TNodeCharacter* pNewNode1 = CreateStudent(id, name, iKor, iEng, iMat);
        pNewNode1->iKey = iKey;
        if (pNewNode1 != nullptr)
        {
            m_Linkedlist.push_back(pNewNode1);
        }
    }
    m_Linkedlist.ShowAll(false, ShowStudent, fp);
    fclose(fp);
};
void  TCharacterManager::UpdateData() {
    int iIndex;
    printf("index= ");
    scanf_s("%d", &iIndex);
    TNodeCharacter* pNode = m_Linkedlist.Find(iIndex);
    ShowStudent(pNode);

    printf("\n이름,번호,국어,영어,수학 : ");
    scanf_s("%s %d %d %d %d", pNode->data.m_szName, _countof(pNode->data.m_szName),
        &pNode->data.m_iIndex, &pNode->data.m_iKor, &pNode->data.m_iEng, &pNode->data.m_iMat);

    pNode->data.m_iTotal =
        pNode->data.m_iKor +
        pNode->data.m_iEng +
        pNode->data.m_iMat;
    pNode->data.m_fAverage = pNode->data.m_iTotal / 3.0f;
}
void  TCharacterManager::FindData()
{
    char name[4] = { 0, };
    scanf_s("%s", name, _countof(name));
    g_pValueData = name;
    TNodeCharacter* pNode = m_Linkedlist.Find(FindStudentString);
    if (pNode != nullptr)
    {
        ShowStudentLine(pNode);
    }
}
void  TCharacterManager::DeleteData()
{
    int iIndex;
    printf("\nindex= ");
    scanf_s("%d", &iIndex);
    TNodeCharacter* pNode = m_Linkedlist.Find(iIndex);
    ShowStudent(pNode);

    int iDelete = 0;
    printf("\n%d 노드를 삭제하시겠습니까.y(1)or n(0)", iIndex);
    scanf_s("%d", &iDelete);
    if (iDelete == 1)
    {
        m_Linkedlist.Erase(pNode);
        printf("\n%d 삭제되었습니다.", iIndex);
    }
}
void  TCharacterManager::SortData()
{
    /*TNodeCharacter* a = g_pHead->pNext;
    TNodeCharacter* b = g_pHead->pNext->pNext->pNext;
    Swap(a, b);*/

    /*  TNodeCharacter* a = g_pHead->pNext;
      TNodeCharacter* b = g_pHead->pNext->pNext;
      Swap(a, b);*/

    m_Linkedlist.Sort(AscendingStudent);
    //m_Linkedlist.Sort();
}
void  TCharacterManager::SampleData()
{
    for (int iNode = 0; iNode < 10; iNode++)
    {
        TNodeCharacter* pNewNode = CreateStudent(iNode);
        if (pNewNode != nullptr)
        {
            pNewNode->iKey = ++TNodeCharacter::iKeyIndex;
            m_Linkedlist.push_back(pNewNode);
        }
    }
}
