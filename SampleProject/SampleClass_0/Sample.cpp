
#include "TStudentManager.h"

void (*RUN)(TLinkedlist& list);
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
                RUN = TStudentManager::SampleData;
            }break;
            case PRINT:
            {
                RUN = TStudentManager::PrintData;
            }break;
            case NEW_DATA:
            {
                RUN = TStudentManager::NewData;
            }break;
            case FILE_SAVE:
            {
                RUN = TStudentManager::FileSave;
            }break;
            case FILE_LOAD:
            {
                RUN = TStudentManager::FileLoad;
            }break;
            case UPDATE:
            {
                RUN = TStudentManager::UpdateData;
            }break;
            case FIND:
            {
                RUN = TStudentManager::FindData;
            }break;
            case DELETE:
            {
                RUN = TStudentManager::DeleteData;
            }break;
            case SORT:
            {
                RUN = TStudentManager::SortData;
            }break;
            case EXIT:
            {
                RUN = nullptr;
                workRun = false;
            }break;
        }
        
        if (RUN != nullptr)
        {
            RUN(mgr.GetList());
        }
    }
}
