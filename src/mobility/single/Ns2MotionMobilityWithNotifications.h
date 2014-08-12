#ifndef NS2_MOTION_MOBILITY_WITH_NOTIFICATIONS_H
#define NS2_MOTION_MOBILITY_WITH_NOTIFICATIONS_H
#include <omnetpp.h>
#include <string>
#include "INETDefs.h"
#include "Ns2MotionMobility.h"
#include "notification_m.h"

class INET_API Ns2MotionMobilityWithNotifications : public Ns2MotionMobility
{
   protected:
      //pause time and motion time of a node
      simtime_t pauseTime, motionTime, edgeTime;
      bool isInMotion;
      Notification* notification;
      std::string targetModuleName, targetGateName;
      cModule* targetModule;
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
      /** @brief Updates either pause time or motion time */
      virtual void updateMotionTime();
      /** @brief Sends notification messages to Global
          Observer Module */
      virtual void sendNotification();
      /** @brief print the node state in the event trace*/
      virtual void printState();
   public:
      Ns2MotionMobilityWithNotifications();
      virtual ~Ns2MotionMobilityWithNotifications();
};

#endif
