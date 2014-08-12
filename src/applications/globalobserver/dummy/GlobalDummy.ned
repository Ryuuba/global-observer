package inet.applications.globalobserver.dummy;

import inet.applications.globalobserver.contract.IGlobalObserver;

//Module that only shows the ID of a node sending 
//a notification
simple GlobalDummy like IGlobalObserver
{
   parameters:
      @display("i=misc/sun_l");
      int range = default(50m) @unit(m); // coberture range of mobile hosts
   gates:
      //gate receving notifications of network nodes
      input fromOut @directIn;
}
