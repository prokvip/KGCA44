#include "TStudentManager.h"
#include "TBinarySearch.h"

int main()
{  
    TBinarySearch bst;
    int iDataAray[] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80,55 };
   // int iDataAray[] = { 10,9,8,7,6,5,4,3,2,1 };
   //// int iDataAray[] = { 1,2,3,4,5,6,7,8,9,10 };
    for (int i = 0; i < _countof(iDataAray); i++)
    {
        //bst.Add(rand() % 100);
        bst.Add(iDataAray[i]);
    }
    for (int i = 0; i < _countof(iDataAray); i++)
    {
        //bst.Add(rand() % 100);
        bst.del(iDataAray[i]);
    }
    //bst.del(87);
    //bst.del(15);
    //bst.del(52);
    //bst.del(100);
    //bst.del(50);
    //bst.del(4);
    //bst.del(64);
    //bst.del(21);
   

    ////TDataNode* pFindNode = bst.find(80);
    ////delete bst.m_pRoot;

    ////TLinkedlist<TStudent*>          m_LinkedlistStudentPoint;
    ////m_LinkedlistStudentPoint.push_back(new TStudent);
    ////m_LinkedlistStudentPoint.push_back(new TStudent);
    ////m_LinkedlistStudentPoint.push_back(new TStudent);

    /////*TNode<TStudent*>* pNode = m_LinkedlistStudentPoint[1];
    ////if (pNode != nullptr)
    ////{
    ////    delete pNode->data;
    ////}
    ////m_LinkedlistStudentPoint.Erase(pNode);    */

    ////std::cout << &m_LinkedlistStudentPoint << std::endl;
    ////std::cout << m_LinkedlistStudentPoint << std::endl;

    ////int iNumNode = m_LinkedlistStudentPoint.Size();
    ////for (TNode<TStudent*>* pNode = m_LinkedlistStudentPoint.begin();
    ////     pNode != m_LinkedlistStudentPoint.end();
    ////     )
    ////{
    ////    //TNode<TStudent*>* pNode = m_LinkedlistStudentPoint[i+1];
    ////    if (pNode != nullptr)
    ////    {
    ////        delete pNode->data;
    ////        pNode->data = 0;
    ////    }
    ////    pNode = m_LinkedlistStudentPoint.Erase(pNode);
    ////}
    ////m_LinkedlistStudentPoint.DeleteAll();

    /////// <summary>
    /////// 
    /////// </summary>
    /////// <returns></returns>
    ////TLinkedlist<TStudent>          m_LinkedlistStudentValue;
    ////m_LinkedlistStudentValue.push_back(TStudent());
    ////m_LinkedlistStudentValue.push_back(TStudent());
    ////m_LinkedlistStudentValue.push_back(TStudent());
    ////m_LinkedlistStudentValue.DeleteAll();

    /////// <summary>
    /////// 
    /////// </summary>
    /////// <returns></returns>
    ////TStudentManager mgr;   
    ////int iWork = 0;
    ////bool workRun = true;
    ////mgr.SetExecute(&TStudentManager::PrintData, PRINT);
    ////mgr.SetExecute(&TStudentManager::NewData, NEW_DATA);
    ////mgr.SetExecute(&TStudentManager::FileSave, FILE_SAVE);
    ////mgr.SetExecute(&TStudentManager::FileLoad, FILE_LOAD);
    ////mgr.SetExecute(&TStudentManager::UpdateData, UPDATE);
    ////mgr.SetExecute(&TStudentManager::FindData, FIND);
    ////mgr.SetExecute(&TStudentManager::DeleteData, DELETE);
    ////mgr.SetExecute(&TStudentManager::SortData, SORT);
    ////mgr.SetExecute(&TStudentManager::SampleData, SAMPLE_DATA);
    ////while (workRun)
    ////{
    ////    mgr.Title();
    ////    printf("\nPRINT(0)NEW_DATA(1)SAVE(2)LOAD(3)UPDATE(4)FIND(5)DEL(6)SORT(7)SAMPLE(8)EXIT(99)");
    ////    scanf_s("%d", &iWork);
    ////    mgr.Execute(iWork);
    ////}   
}

