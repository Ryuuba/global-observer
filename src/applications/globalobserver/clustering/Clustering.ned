// Module executing a global clustering algorithm. It
// receives from nodes notification messages which
// constructs a global table. Using the global table data,
// the clustering simple module applies a leader-election
// criteria to assign the status LEADER to those ones with
// the highest aptitude. Then the module assigns the status
// CLUSTERED to k-hop neighbor nodes of the LEADER. Each
// time it is received a notification message,
// clustering module updates the global table and records
// stats through the signal mechanism provides by OMNETPP

package inet.applications.globalobserver.clustering;

simple Clustering
{
   parameters:
      @display("i=block/cogwheel_l");
      //criterion to elect leader
      //string leaderElectionCriterion; 
      int hops; //cluster radious measured in hops
      int range @unit(m); //coberture range of mobile hosts
      //central organization delay
      double updateDelay = default(0.1s) @unit(s);
      //leader election criterion
      string criterion = default("degree");

      //statistics
      @signal[leaders](type = "long");
      @statistic[numberOfLeaders](title = "number of leaders";source ="leaders";record = stats, vector);
      @signal[leaderOff](type = "simtime_t");
      @statistic[leadershipTime](title = "leadership time";source = "leaderOff";record = stats, vector);
   gates:
      input fromGlobalClustering;
}
