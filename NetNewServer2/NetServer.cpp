#include "TNetworkUDP.h"
#include "TNetworkTCP.h"
int main()
{
    //TNetworkUDP tNet(std::make_shared<TNoneSelect>());
    //TNetworkUDP tNet(nullptr);
    //TNetworkTCP tNet(std::make_shared<TEventSelect>());
    TNetworkTCP tNet(std::make_shared<TStdSelect>());
    tNet.Init();
    tNet.CreateServer(10000);
    tNet.Run();    
    tNet.Release();    
}
