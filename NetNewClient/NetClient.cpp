#include "TNetwork.h"

//쓰레드의 시작함수 : 반환되면 쓰레드는 정상종료된다.
DWORD WorkSend(LPVOID lpThreadParameter)
{
    TNetwork* net = (TNetwork*)lpThreadParameter;    
    std::string SendBuf;
    SendBuf.reserve(256);
    while (net->m_bRun)
    {     
        std::getline(std::cin, SendBuf);
        net->SendWork(SendBuf);
    }
    return 1;
}
int main()
{
    TNetwork net;   
    net.Init();
    if (net.Connect("192.168.0.88", 10000))
    {       
        HANDLE hThread1 = CreateThread(NULL, 0, WorkSend, &net, 0, NULL);
        CloseHandle(hThread1);
        net.Run();
    }
    net.Release();
}
