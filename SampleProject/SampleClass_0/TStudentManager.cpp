#include "TStudentManager.h"
void* TStudentManager::g_pValueData = nullptr;
void  TStudentManager::PrintData(TLinkedlist& list) {
    system("cls");
    list.ShowAll(false, ShowStudent);
}
void  TStudentManager::NewData(TLinkedlist& list)
{
    char name[4] = { 0, };
    int iID, iKor, iEng, iMat;
    printf("\n이름,번호,국어,영어,수학 : ");
    scanf_s("%s %d %d %d %d", name, _countof(name), &iID, &iKor, &iEng, &iMat);
    TNode* pNewNode = CreateStudent(iID, name, iKor, iEng, iMat);
    if (pNewNode != nullptr)
    {
        pNewNode->iKey = ++TNode::iKeyIndex;
        list.push_back(pNewNode);
    }
}
void  TStudentManager::FileSave(TLinkedlist& list)
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "w");
    fprintf(fp, "%d %d\n", list.GetCounter(), TNode::iKeyIndex);
    list.ShowAll(false, ShowStudent, fp);
    fclose(fp);
}
void  TStudentManager::FileLoad(TLinkedlist& list)
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "r");
    if (fp != nullptr)
    {
        list.DeleteAll();
    }

    char buffer[256] = { 0 , };
    int iNodeCounter = 3;
    fgets(buffer, 256, fp);
    sscanf_s(buffer, "%d %d", &iNodeCounter, &TNode::iKeyIndex);

    //fscanf_s(fp, "%d %d\n",&iNodeCounter, &TNode::iKeyIndex);
    for (int iNode = 0; iNode < iNodeCounter; iNode++)
    {
        char name[4] = { 0, };
        int iKor, iEng, iMat, iTotal;
        float fAvg;

        int id, iKey;

        fgets(buffer, 256, fp);
        sscanf_s(buffer, "%d %d %s %d %d %d\n", &iKey, &id, name, _countof(name), &iKor, &iEng, &iMat, &iTotal, &fAvg);
        TNode* pNewNode1 = CreateStudent(id, name, iKor, iEng, iMat);
        pNewNode1->iKey = iKey;
        if (pNewNode1 != nullptr)
        {
            list.push_back(pNewNode1);
        }
    }
    list.ShowAll(false, ShowStudent, fp);
    fclose(fp);
};
void  TStudentManager::UpdateData(TLinkedlist& list) {
    int iIndex;
    printf("index= ");
    scanf_s("%d", &iIndex);
    TNode* pNode = list.Find(iIndex);
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
void  TStudentManager::FindData(TLinkedlist& list)
{
    char name[4] = { 0, };
    scanf_s("%s", name, _countof(name));
    g_pValueData = name;
    TNode* pNode = list.Find(FindStudentString);
    if (pNode != nullptr)
    {
        ShowStudentLine(pNode);
    }
}
void  TStudentManager::DeleteData(TLinkedlist& list)
{
    int iIndex;
    printf("\nindex= ");
    scanf_s("%d", &iIndex);
    TNode* pNode = list.Find(iIndex);
    ShowStudent(pNode);

    int iDelete = 0;
    printf("\n%d 노드를 삭제하시겠습니까.y(1)or n(0)", iIndex);
    scanf_s("%d", &iDelete);
    if (iDelete == 1)
    {
        list.Erase(pNode);
        printf("\n%d 삭제되었습니다.", iIndex);
    }
}
void  TStudentManager::SortData(TLinkedlist& list)
{
    /*TNode* a = g_pHead->pNext;
    TNode* b = g_pHead->pNext->pNext->pNext;
    Swap(a, b);*/

    /*  TNode* a = g_pHead->pNext;
      TNode* b = g_pHead->pNext->pNext;
      Swap(a, b);*/

    list.Sort(AscendingStudent);
    //list.Sort();
}
void  TStudentManager::SampleData(TLinkedlist& list)
{
    for (int iNode = 0; iNode < 10; iNode++)
    {
        TNode* pNewNode = CreateStudent(iNode);
        if (pNewNode != nullptr)
        {
            pNewNode->iKey = ++TNode::iKeyIndex;
            list.push_back(pNewNode);
        }
    }
}