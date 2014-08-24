#ifndef _CLUSTERING_H
#define _CLUSTERING_H
#include <cstdint>
#include <string>
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
      
      //Creates k-hop clusters around leaders
      virtual void makeCluster(uint32_t leaderID);

      //Initialized the role list getting the UID of each
      //node in table, then it inserts to each node the
      //UNCLUSTERED role. Besides, it changes the value
      //of isRoleListInitialized to true
      virtual void initializeRoleList();
      
      //Organizes clusters as follows: First, it checks if
      //there are leaders in the neighborhood of each
      //leader. If it happens, the neighborhoods of each
      //leader are unclustered. Otherwise, clusters are
      //formed around each leader
      virtual void organizeClusters();

      //Forms clusters around leaders when they do not have
      //leader neighbors
      virtual void organizeLeaders();

      //Unclusters the neighborhood of a leader
      virtual void getRidOf(uint32_t leaderID);

      //Changes clustered nodes to UNCLUSTERED when they do
      //not have leaders in their neighborhoods
      virtual void organizeClusteredNodes();


      //Colorizes a cluster. Cluster heads have a blue-icon
      //whereas clustered nodes have a gold-icon
      virtual void changeIconColor();
            
      //emits the statistics of the leadershipTime and the
      //number of leaders
      virtual void emitStatistics();

   public:
      Clustering();
      ~Clustering();
};

#endif
