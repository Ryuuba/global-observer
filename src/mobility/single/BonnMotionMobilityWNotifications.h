#ifndef BONN_MOTION_MOBILITY_W_NOTIFICATIONS_H
#define BONN_MOTION_MOBILITY_W_NOTIFICATIONS_H

#include "BonnMotionMobility.h"
#include <string>
#include "notification_m.h"


//Class overriding BonnMotionMobility to send notification
//messages to GlobalObserverModules. Messages carry the
//position, speed, pause-time, motion-time, and ID of 
//the mobile node executing this simple module
class INET_API BonnMotionMobilityWNotifications :
public BonnMotionMobility
{
   protected:
      //Node state
      int nodeId;
      simtime_t edgeTime, pauseTime, motionTime;
      double flightLength;
      bool isInMotion;
      Coord edgeDetector, position;
      Notification* notification;
      std::string targetModuleName, targetGateName;
      cModule* targetModule;
   protected:
      /** @brief Initializes mobility model parameters. */
      virtual void initialize(int stage);
      /** @brief Overridden from BonnMotionMobility. */
      virtual void move();
      /** @brief fills a notificarion message and returns a 
          pointer to the target module */
      virtual void notificationGenerator();
      /** @brief update the edge time if it had a mobility
          change */
      virtual void updateEdgeTime(Coord edgeDetector);
      /** @brief Updates the flight length */
      virtual void updateMotionTime();
      /** @brief Updates either pause time or motion time */
      virtual void updateFlightLength();
      /** @brief Sends notification messages to Global
          Observer Module */
      virtual void sendNotification();
      /** @brief print the node state in the event trace*/
      virtual void printState();
      
   public:
      BonnMotionMobilityWNotifications();
      virtual ~BonnMotionMobilityWNotifications();
};

#endif
