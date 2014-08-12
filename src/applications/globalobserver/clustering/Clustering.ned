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
      //string leaderElectionCriterion; //criterion to elect leader
      int hops; //cluster radious measured in hops
      int range @unit(m); // coberture range of mobile hosts
      double updateDelay = default(0.1s) @unit(s);
      string tableName = default("globalNodeTable");
      string criterion = default("degree");
      //statistics
      //@signal[leaderChange](type = "long");
      //@statistic[leaderNumber](title = "number of leader";source ="arrival";record = stats, vector);
      //@signal[leaderOff](type = "simtime_t");
      //@statistic[leadershipTime](title = "leadership time";source = "leadership";record = stats, vector);
   gates:
      input fromGlobalClustering;
}
