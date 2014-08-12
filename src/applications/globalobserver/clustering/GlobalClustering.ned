// Module that executes a generic clustering algorithm on
// the global node state, which is received from nodes
// reporting their position, speed, pause-time, and
// motion-time through a notification message. Besides,
// this module record stats about the performance of 
// different leader-election criteria

package inet.applications.globalobserver.clustering;

import inet.applications.globalobserver.contract.IGlobalObserver;

module GlobalClustering like IGlobalObserver
{
   parameters:
      @display("i=misc/sun_l");
      int range @unit(m); // coberture range of mobile hosts
   gates:
      //gate receiving notifications of network nodes
      input fromOut @directIn;
   submodules:
      clustering: Clustering{
         range = range;
      }
   connections:
      fromOut --> clustering.fromGlobalClustering;
}
