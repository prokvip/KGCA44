#include "TNetworkUDP.h"
#include "TNetworkTCP.h"
int main()
{
    //TNetworkUDP tNet(std::make_shared<TNoneSelect>());
    //TNetworkUDP tNet(nullptr);
    TNetworkTCP tNet(std::make_shared<TEventSelect>());
    tNet.Init();
    tNet.CreateServer(10000);
    tNet.Run();    
    tNet.Release();    
}
