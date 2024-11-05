#include "TStudentManager.h"

int main()
{
   /* TStudent* cList[3];
    cList[0] = new TStudent();
    cList[1] = new TStudent();
    cList[2] = new TStudent();*/
        TLinkedlist<TStudent*>          m_LinkedlistStudentPoint;
        m_LinkedlistStudentPoint.push_back(new TStudent);
        m_LinkedlistStudentPoint.push_back(new TStudent);
        m_LinkedlistStudentPoint.push_back(new TStudent);

        TLinkedlist<TStudent>          m_LinkedlistStudentValue;
        m_LinkedlistStudentValue.push_back(TStudent());
        m_LinkedlistStudentValue.push_back(TStudent());
        m_LinkedlistStudentValue.push_back(TStudent());

        //std::cout << m_LinkedlistStudent << std::endl;
   
        for (int i = 0; i < m_LinkedlistStudentPoint.Size(); i++)
        {
            TNode<TStudent*>* pNode = m_LinkedlistStudentPoint[i];
            delete pNode->data;
            m_LinkedlistStudentPoint.Erase(pNode);
        }

    /*delete cList[0];
    delete cList[1];
    delete cList[2];*/
    m_LinkedlistStudentPoint.DeleteAll();
    m_LinkedlistStudentValue.DeleteAll();


    TLinkedlist<float>               m_intArray;
    TLinkedlist<TCharacter>        m_LinkedlistCharacter;
   
   
    
    std::cout << &m_LinkedlistCharacter << std::endl;

    for (int i = 0; i < m_LinkedlistCharacter.Size(); i++)
    {
        TNode<TCharacter>* pNode = m_LinkedlistCharacter.Find(1);
        std::cout << pNode << std::endl;
    }


    

    //m_intArray.ShowAll();
    


    TStudentManager mgr;
   
    int iWork = 0;
    bool workRun = true;

    /// <summary>
    /// 방법 1
    /// </summary>
    /// <returns></returns>
    mgr.SetExecute(&TStudentManager::PrintData, PRINT);
    mgr.SetExecute(&TStudentManager::NewData, NEW_DATA);
    mgr.SetExecute(&TStudentManager::FileSave, FILE_SAVE);
    mgr.SetExecute(&TStudentManager::FileLoad, FILE_LOAD);
    mgr.SetExecute(&TStudentManager::UpdateData, UPDATE);
    mgr.SetExecute(&TStudentManager::FindData, FIND);
    mgr.SetExecute(&TStudentManager::DeleteData, DELETE);
    mgr.SetExecute(&TStudentManager::SortData, SORT);
    mgr.SetExecute(&TStudentManager::SampleData, SAMPLE_DATA);
    while (workRun)
    {
        mgr.Title();
        printf("\nPRINT(0)NEW_DATA(1)SAVE(2)LOAD(3)UPDATE(4)FIND(5)DEL(6)SORT(7)SAMPLE(8)EXIT(99)");
        scanf_s("%d", &iWork);

        switch (iWork)
        {
        case SAMPLE_DATA:
        {
            mgr.EXECUTEDirect = &TStudentManager::SampleData;
        }break;
        case PRINT:
        {
            std::cout << mgr << std::endl;           
            mgr.EXECUTEDirect = &TStudentManager::PrintData;
        }break;
        case NEW_DATA:
        {
            mgr.EXECUTEDirect = &TStudentManager::NewData;
        }break;
        case FILE_SAVE:
        {
            mgr.EXECUTEDirect = &TStudentManager::FileSave;
        }break;
        case FILE_LOAD:
        {
            mgr.EXECUTEDirect = &TStudentManager::FileLoad;
        }break;
        case UPDATE:
        {
            mgr.EXECUTEDirect = &TStudentManager::UpdateData;
        }break;
        case FIND:
        {
            mgr.EXECUTEDirect = &TStudentManager::FindData;
        }break;
        case DELETE:
        {
            mgr.EXECUTEDirect = &TStudentManager::DeleteData;
        }break;
        case SORT:
        {
            mgr.EXECUTEDirect = &TStudentManager::SortData;
        }break;
        case EXIT:
        {
            mgr.EXECUTEDirect = nullptr;
            workRun = false;
        }break;
        }

        if (mgr.EXECUTEDirect != nullptr)
        {
            mgr.ExecuteDirect();
        }
    }
}

