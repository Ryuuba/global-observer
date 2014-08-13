#ifndef _CLUSTERING_H
#define _CLUSTERING_H
#include <cstdint>
#include <string>
#include "Table.h"
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
      
   protected:
      //It initializes the protected attributes with the
      //omnetpp.ini-file data 
      virtual void initialize();
      //It calls methods to compute the state of the network
      //nodes and it adds and updates the Table with the
      //messages sent by network nodes.
      virtual void handleMessage(cMessage* msg);
      
      //Updates the global node table content
      virtual void updateTable();
      
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
      
      //Computes clusters in a centralized manner
      virtual void clustering();
      
      //Computes the leader according the value of
      //criterion string. Returns a NULL pointer when there
      //aren't UNCLUSTERED nodes
      virtual const uint32_t* getLeader();
      
      //Computes leaders according the degree criterion.
      //Returns a NULL pointer when there aren't 
      //UNCLUSTERED nodes
      virtual const uint32_t* getLeaderByDegree();
      
      //Creates k-hop clusters around leaders
      virtual void makeCluster(uint32_t leaderID);

      //Initialized the role list getting the UID of each
      //node in table, then it inserts to each node the
      //UNCLUSTERED role. Besides, it changes the value
      //of isRoleListInitialized to true
      virtual void initializeRoleList();
      
      //Colors leaders in red and clustered nodes in gold
      virtual void changeIconColor();
            
      
   public:
      Clustering();
      ~Clustering();
};

#endif
