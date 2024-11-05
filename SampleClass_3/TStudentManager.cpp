#include "TStudentManager.h"
void* TStudentManager::g_pValueData = nullptr;

std::ostream& operator <<(std::ostream& os, 
                          TStudentManager& mgr)
{
    for (TNode<TStudent>* pNode = mgr.m_Linkedlist.begin();
        pNode != mgr.m_Linkedlist.end();
        pNode = pNode->pNext)
    {
        std::cout << pNode << std::endl;
    }
    return os;
}
void  TStudentManager::PrintData() {
    system("cls");
    m_Linkedlist.ShowAll(false, ShowStudent);
}
void  TStudentManager::NewData()
{
    char name[4] = { 0, };
    int iID, iKor, iEng, iMat;
    printf("\n이름,번호,국어,영어,수학 : ");
    scanf_s("%s %d %d %d %d", name, _countof(name), &iID, &iKor, &iEng, &iMat);
    TStudent* pNewData = CreateStudent(iID, name, iKor, iEng, iMat);
    if (pNewData != nullptr)
    {
        m_Linkedlist.push_back(*pNewData);
        delete pNewData;
    }
}
void  TStudentManager::FileSave()
{
    FILE* fp = 0;
    fopen_s(&fp, "data.txt", "w");
    fprintf(fp, "%d %d\n", m_Linkedlist.Size(), TNode<TStudent>::iKeyIndex);
    m_Linkedlist.ShowAll(false, ShowStudent, fp);
    fclose(fp);
}
void  TStudentManager::FileLoad()
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
    sscanf_s(buffer, "%d %d", &iNodeCounter, &TNode<TStudent>::iKeyIndex);

    //fscanf_s(fp, "%d %d\n",&iNodeCounter, &TNode::iKeyIndex);
    for (int iNode = 0; iNode < iNodeCounter; iNode++)
    {
        char name[4] = { 0, };
        int iKor, iEng, iMat, iTotal;
        float fAvg;

        int id, iKey;

        fgets(buffer, 256, fp);
        sscanf_s(buffer, "%d %d %s %d %d %d\n", &iKey, &id, name, _countof(name), &iKor, &iEng, &iMat, &iTotal, &fAvg);
        TStudent* pNewNode1 = CreateStudent(id, name, iKor, iEng, iMat);
        if (pNewNode1 != nullptr)
        {
            m_Linkedlist.push_back(*pNewNode1, iKey);
            delete pNewNode1;
        }
    }    
    fclose(fp);
    m_Linkedlist.ShowAll(false, ShowStudent, nullptr);
};
void  TStudentManager::UpdateData() {
    int iIndex;
    printf("index= ");
    scanf_s("%d", &iIndex);
    TNode<TStudent>* pNode = m_Linkedlist.Find(iIndex);
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
void  TStudentManager::FindData()
{
    char name[4] = { 0, };
    scanf_s("%s", name, _countof(name));
    g_pValueData = name;
    TNode<TStudent>* pNode = m_Linkedlist.Find(FindStudentString);
    if (pNode != nullptr)
    {
        ShowStudentLine(pNode);
    }
}
void  TStudentManager::DeleteData()
{
    int iIndex;
    printf("\nindex= ");
    scanf_s("%d", &iIndex);
    TNode<TStudent>* pNode = m_Linkedlist.Find(iIndex);
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
void  TStudentManager::SortData()
{
    /*TNode* a = g_pHead->pNext;
    TNode* b = g_pHead->pNext->pNext->pNext;
    Swap(a, b);*/

    /*  TNode* a = g_pHead->pNext;
      TNode* b = g_pHead->pNext->pNext;
      Swap(a, b);*/

    m_Linkedlist.Sort(AscendingStudent);
    //m_Linkedlist.Sort();
}
void  TStudentManager::SampleData()
{
    for (int iNode = 0; iNode < 3; iNode++)
    {
        TStudent* pNewData = CreateStudent(iNode);
        if (pNewData != nullptr)
        {
             m_Linkedlist.push_back(*pNewData);
             delete pNewData;
        }
    }
}
