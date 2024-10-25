#include "TStudentManager.h"
#define CLASS_FUNCTION
#ifndef CLASS_FUNCTION
void (TStudentManager::*RUN)();
int main()
{
    TStudentManager mgr;      

    int iWork = 0;
    bool workRun = true;
    while (workRun)
    {        
        mgr.Title();
        printf("\nPRINT(0)NEW_DATA(1)SAVE(2)LOAD(3)UPDATE(4)FIND(5)DEL(6)SORT(7)SAMPLE(8)EXIT(99)");
        scanf_s("%d", &iWork);
        
        switch (iWork)
        {
            case SAMPLE_DATA:
            {
                //TStudentManager::SampleData': 비표준 구문입니다. '&'를 사용하여 멤버 포인터를 만드세요.
                RUN = &TStudentManager::SampleData;
            }break;
            case PRINT:
            {
                RUN = &TStudentManager::PrintData;
            }break;
            case NEW_DATA:
            {
                RUN = &TStudentManager::NewData;
            }break;
            case FILE_SAVE:
            {
                RUN = &TStudentManager::FileSave;
            }break;
            case FILE_LOAD:
            {
                RUN = &TStudentManager::FileLoad;
            }break;
            case UPDATE:
            {
                RUN = &TStudentManager::UpdateData;
            }break;
            case FIND:
            {
                RUN = &TStudentManager::FindData;
            }break;
            case DELETE:
            {
                RUN = &TStudentManager::DeleteData;
            }break;
            case SORT:
            {
                RUN = &TStudentManager::SortData;
            }break;
            case EXIT:
            {
                RUN = nullptr;
                workRun = false;
            }break;
        }
        
        if (RUN != nullptr)
        {            
            //RUN(mgr.GetList()); // error
            (mgr.*RUN)(mgr.GetList());
        }
    }
}
#else
int main()
{
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
    /*while (workRun)
    {
        mgr.Title();
        printf("\nPRINT(0)NEW_DATA(1)SAVE(2)LOAD(3)UPDATE(4)FIND(5)DEL(6)SORT(7)SAMPLE(8)EXIT(99)");
        scanf_s("%d", &iWork);
        mgr.Execute(mgr.GetList(), iWork);
    }*/

    /// <summary>
    /// 방법 2
    /// </summary>
    /// <returns></returns>
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
#endif
