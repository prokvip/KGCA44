#include "TNetworkUDP.h"
#include "TNetworkTCP.h"
int main()
{
    TNetworkUDP tNet;
    tNet.Init();
    tNet.CreateServer(10000);
    tNet.Run();    
    tNet.Release();    
}
