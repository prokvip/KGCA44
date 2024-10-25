#include "TStudentManager.h"
#define CLASS_FUNCTION
#ifndef CLASS_FUNCTION
void (TStudentManager::*RUN)(TLinkedlist& list);
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
    ////mgr.Run();
    //
    //bool workRun = true;
    //while (workRun)
    //{
    //    workRun = mgr.Run();
    //}
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
            mgr.EXECUTE = &TStudentManager::SampleData;
        }break;
        case PRINT:
        {
            mgr.EXECUTE = &TStudentManager::PrintData;
        }break;
        case NEW_DATA:
        {
            mgr.EXECUTE = &TStudentManager::NewData;
        }break;
        case FILE_SAVE:
        {
            mgr.EXECUTE = &TStudentManager::FileSave;
        }break;
        case FILE_LOAD:
        {
            mgr.EXECUTE = &TStudentManager::FileLoad;
        }break;
        case UPDATE:
        {
            mgr.EXECUTE = &TStudentManager::UpdateData;
        }break;
        case FIND:
        {
            mgr.EXECUTE = &TStudentManager::FindData;
        }break;
        case DELETE:
        {
            mgr.EXECUTE = &TStudentManager::DeleteData;
        }break;
        case SORT:
        {
            mgr.EXECUTE = &TStudentManager::SortData;
        }break;
        case EXIT:
        {
            mgr.EXECUTE = nullptr;
            workRun = false;
        }break;
        }

        if (mgr.EXECUTE != nullptr)
        {
            //RUN(mgr.GetList()); // error            
            mgr.Execute(mgr.GetList());
        }
    }
}
#endif
