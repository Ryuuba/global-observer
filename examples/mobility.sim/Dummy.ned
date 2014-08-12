package inet.examples.mobility.sim;

import inet.applications.globalobserver.contract.IGlobalObserver;

network Dummy
{
    parameters:
        int numHosts;
        @display("bgb=500,500");
    submodules:
        host[numHosts]: MobileHost;
        observer: <GlobalDummy> like IGlobalObserver;
}
