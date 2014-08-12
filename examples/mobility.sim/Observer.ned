package inet.examples.mobility.sim;

import inet.applications.globalobserver.contract.IGlobalObserver;

network Observer
{
    parameters:
        int numHosts;
        string observerType = default("GlobalDummy");
        @display("bgb=500,500");
    submodules:
        host[numHosts]: MobileHost;
        observer: <observerType> like IGlobalObserver;
}
