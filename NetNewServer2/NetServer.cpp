#include "TNetUDP.h"
int main()
{
    TNetworkTCP tNet;
    tNet.Init();
    tNet.CreateServer(10000);
    tNet.Run();    
    tNet.Release();    
}
