#include "TNetUDP.h"
int main()
{
    TNetUDP tNet;
    tNet.Init();
    tNet.CreateServer(10000);
    tNet.Run();    
    tNet.Release();    
}
