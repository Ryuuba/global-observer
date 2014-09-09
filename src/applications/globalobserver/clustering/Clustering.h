#ifndef _CLUSTERING_H
#define _CLUSTERING_H
#include <cstdint>
#include <string>
#include <random>
#include "Table.h"
#include "LeaderTable.h"
#include "notification_m.h"
#include "IGlobalObserver.h"

class Clustering:
public IGlobalObserver{
   protected:
      //Criterion to elect leaders
      std::string criterion;
      //cluster radious measured in hops
      uint8_t hops;
      //coberture range of mobile hosts
      uint8_t range;
      //Timer to update the node state
      cMessage* update;
      //Delay to compute the state of the network nodes
      simtime_t updateDelay;
      //received-messages counter 
      uint8_t receivedMessages;
      //Data structure storing the state of the nodes
      Table globalNodeTable;
      //Flag indicating if role list is initialized
      bool isRoleListInitialized;
      //Signals to record statistics
      simsignal_t numberOfLeaders;
      simsignal_t leadershipTime;
      simsignal_t leaderChurn;
      //Bool value that indicates statistics only will be
      //gathered from clusters whose size is greater than 
      //cut value
      bool filter;
      //Numerical value establishing a limit to discard 
      //statistics from clusters whose size is less than
      //cut value
      simtime_t cutTime;
      //Datastructure to store the leadership-time
      LeaderTable leaderTable;
   protected:
      //It initializes the protected attributes with the
      //omnetpp.ini-file data 
      virtual void initialize();
      //It calls methods to compute the state of the
      //network nodes and it adds and updates the Table
      //with the messages sent by network nodes.
      virtual void handleMessage(cMessage* msg);
      
      //Updates the global node table content
      virtual void updateTable();

      //Updates an global-node-table entry using a message
      //sent by a node
      virtual void updateTable(cMessage* msg);
      
      //invokes both computeNeighborhood(uint32_t nodeID)
      //and computeNeighborhood(uint32_t nodeID, uint8_t k)
      virtual void computeNeighborhood();      

      //Computes the one-hop neighborhood of a node using
      //the coberture range as parameter.
      virtual Neighborhood
      computeNeighborhood(uint32_t nodeID);

      //Computes the neighborhood of a node using
      //the number of k-hops as parameter.
      virtual Neighborhood
      computeNeighborhood(uint32_t nodeID, uint8_t k);
      
      //Computes clusters in a centralized manner. It takes
      //all nodes whose role is UNCLUSTERED and form with
      //them clusters
      virtual void makeClusters();
      
      //Computes the leader according the value of
      //criterion string. Returns a NULL pointer when there
      //aren't UNCLUSTERED nodes
      virtual std::pair<bool,uint32_t> getLeader();
      
      //Computes leaders according the degree criterion.
      //Returns a NULL pointer when there aren't 
      //UNCLUSTERED nodes
      virtual std::pair<bool,uint32_t> getLeaderByDegree();

      //Computes leaders according the size of their k-hop
      //neighborhood
      virtual std::pair<bool,uint32_t>
      getLeaderByKHopNeighborhood();

      //Computes leaders according the average distance
      //among a node and its neighbors
      virtual std::pair<bool,uint32_t>
      getLeaderByDistance();
         
      virtual std::pair<bool,uint32_t>
      getLeaderBySpeed();

      virtual std::pair<bool,uint32_t>
      getLeaderByPauseTime();

      virtual std::pair<bool,uint32_t>
      getLeaderByFlightLength();
      
      //Creates k-hop clusters around leaders
      virtual void makeCluster(uint32_t leaderID);

      //Initialized the role list getting the UID of each
      //node in table, then it inserts to each node the
      //UNCLUSTERED role. Besides, it changes the value
      //of isRoleListInitialized to true
      virtual void initializeRoleList();
      
      //Assigns the role ISOLATED to those nodes whose 
      //neighborhood is NULL
      virtual void organizeIsolated();

      //Organizes clusters as follows: First, it checks if
      //there are leaders in the neighborhood of each
      //leader. If it happens, the neighborhoods of each
      //leader are unclustered. Otherwise, clusters are
      //formed around each leader
      virtual void organizeClusters();

      //Forms clusters around leaders when they do not have
      //leader neighbors
      virtual void organizeLeaders();

      //Verifies the validity of a leader neighborhood
      virtual bool checkNeighborhood(uint32_t leaderID);

      //Verifies if a node is isolated
      virtual bool isIsolated(uint32_t id);

      //Returns the leader ID of the give node
      virtual Neighborhood::Neighbor
      getLeaderOf(uint32_t id);

      //Unclusters the neighborhood of a leader
      virtual void getRidOf(uint32_t leaderID);

      //Changes clustered nodes to UNCLUSTERED when they do
      //not have leaders in their neighborhoods
      virtual void organizeClusteredNodes();


      //Colorizes a cluster. Cluster heads have a blue-icon
      //whereas clustered nodes have a gold-icon
      virtual void changeIconColor();

      //Prints the static cluster color table
      virtual void
      printColorTable
      (std::unordered_map<uint32_t,std::string>& table);

      //Updates cluster color table
      virtual void
      updateClusterColorTable
      (std::unordered_map<uint32_t,std::string>& table);

      //Returns a string containing an HTML color
      virtual std::string pickRandomColor();

      //emits the following statistics: number of leaders,
      //leader churn, and leadership time. If filter bool
      //value equals true, then it only emits statistics 
      //from clusters whose size is greater than cutValue
      virtual void emitStatistics();

      //removes from leader table such leaders whose
      //cluster size is less than cutValue
      virtual void filterStatistics();

      //Prints cluster information
      virtual void printClusters();

      //Prints global node table
      virtual void printTable();

   public:
      Clustering();
      ~Clustering();
};

#endif
