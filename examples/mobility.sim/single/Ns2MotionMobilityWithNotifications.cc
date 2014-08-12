#include "Ns2MotionMobilityWithNotifications.h"

Define_Module(Ns2MotionMobilityWithNotifications);


Ns2MotionMobilityWithNotifications::
Ns2MotionMobilityWithNotifications()
{
   //state from Ns2MotionMobility
   vecpos = 0;
   ns2File = NULL;
   nodeId = 0;
   scrollX = 0;
   scrollY = 0;
   //node state
   notification = NULL;
   isInMotion = false;
   edgeTime = 0.0;
   pauseTime = 0.0;
   motionTime = 0.0;
   targetModule = NULL;
}

Ns2MotionMobilityWithNotifications::
~Ns2MotionMobilityWithNotifications(){}

void Ns2MotionMobilityWithNotifications::
initialize(int stage)
{
   Ns2MotionMobility::initialize(stage);
   targetModuleName = par("targetModuleName").stringValue();
   targetModule = simulation.
                  getSystemModule()->
                  getSubmodule(targetModuleName.c_str());
   targetGateName = par("targetGateName").stringValue();
}

void Ns2MotionMobilityWithNotifications::
move()
{  
   Coord edgeDetector = lastSpeed;
   updateMotionTime();
   notificationGenerator();
   sendNotification();
   printState();
   Ns2MotionMobility::move();
   raiseErrorIfOutside();
   updateEdgeTime(edgeDetector);
}

void Ns2MotionMobilityWithNotifications::
updateMotionTime()
{
   if(isInMotion)
     motionTime = simTime() - edgeTime;
   else
     pauseTime = simTime() - edgeTime;
}

void Ns2MotionMobilityWithNotifications::
notificationGenerator()
{

   notification = new Notification;
   notification->setPosition(lastPosition);
   notification->setPauseTime(pauseTime);
   notification->setMotionTime(motionTime);
   notification->setSpeed(lastSpeed.length());
   notification->setSource(nodeId);
}

void Ns2MotionMobilityWithNotifications::
sendNotification()
{
   sendDirect(notification,
              targetModule,
              targetGateName.c_str());
}

void Ns2MotionMobilityWithNotifications::
updateEdgeTime(Coord edgeDetector)
{
    if ( (edgeDetector != lastSpeed) &&
         (edgeDetector.length() * lastSpeed.length() == 0.0) )
    {
        edgeTime = simTime();
        if ( lastSpeed == Coord::ZERO )
        {
            motionTime = 0.0;
            isInMotion = false;
        }
        else
        {
            pauseTime = 0.0;
            isInMotion = true;
        }
    }
}

void Ns2MotionMobilityWithNotifications::
printState()
{
   ev << "Node ID: " << nodeId << "\n";
   ev << "Position: " << lastPosition.x << ", " 
      << lastPosition.y << "\n";
   ev << "Speed: " << lastSpeed.length() << "\n";
   ev << "Pause time: " << pauseTime << "\n";
   ev << "Motion time: " << motionTime << endl;
}
