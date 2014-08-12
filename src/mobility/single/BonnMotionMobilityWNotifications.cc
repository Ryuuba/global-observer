#include "BonnMotionMobilityWNotifications.h"
#include "BonnMotionFileCache.h"
#include "FWMath.h"

Define_Module(BonnMotionMobilityWNotifications);

BonnMotionMobilityWNotifications::
BonnMotionMobilityWNotifications()
{
   //state from BonnMotionMobility
   is3D = false;
   lines = NULL;
   currentLine = -1;
   //Node state
   nodeId = 0;
   edgeTime = 0.0;
   pauseTime = 0.0;
   motionTime = 0.0;
   flightLength = 0.0;
   isInMotion = false;
   notification = NULL;
   targetModule = NULL;
}

BonnMotionMobilityWNotifications::
~BonnMotionMobilityWNotifications()
{
}

void
BonnMotionMobilityWNotifications::initialize(int stage)
{
    LineSegmentsMobilityBase::initialize(stage);

    EV_TRACE << "initializing BonnMotionMobility stage "
             << stage << endl;
    if (stage == 0)
    {
        is3D  = par("is3D").boolValue();
        nodeId = par("nodeId");
        if (nodeId == -1)
            nodeId = getContainingNode(this)->getIndex();
        const char *fname = par("traceFile");
        const BonnMotionFile *bmFile = 
        BonnMotionFileCache::getInstance()->getFile(fname);
        lines = bmFile->getLine(nodeId);
        if (!lines)
            throw cRuntimeError("Invalid nodeId %d -- no\
                                 such line in file '%s'",
                                nodeId, fname);
        currentLine = 0;
    }
   targetModuleName = par("targetModuleName").stringValue();
   targetGateName = par("targetGateName").stringValue();
   targetModule = simulation.
                  getSystemModule()->
                  getSubmodule(targetModuleName.c_str());
   //To initialize global observer
   if (stage == 2)
   {
      notificationGenerator();
      sendNotification();
      printState();
   }  
}

void
BonnMotionMobilityWNotifications::move()
{
   edgeDetector = lastSpeed;
   position = lastPosition;
   updateMotionTime();
   //printState();
   LineSegmentsMobilityBase::move();
   raiseErrorIfOutside();
   updateFlightLength();
   notificationGenerator();
   sendNotification();
   updateEdgeTime(edgeDetector);
}

void
BonnMotionMobilityWNotifications::updateMotionTime()
{
   if(isInMotion)
      motionTime = simTime() - edgeTime;
   else
      pauseTime = simTime() - edgeTime;
}

void
BonnMotionMobilityWNotifications::updateFlightLength()
{
   //accumulates the distance between the last position and
   //the current position
   if(isInMotion)
      flightLength += position.distance(lastPosition);
   else
      flightLength = 0.0;
}

void
BonnMotionMobilityWNotifications::notificationGenerator()
{
   notification = new Notification;
   notification->setPosition(lastPosition);
   notification->setPauseTime(pauseTime);
   notification->setMotionTime(motionTime);
   notification->setSpeed(edgeDetector.length());
   notification->setSource(nodeId);
   notification->setFlightLength(flightLength);
}

void
BonnMotionMobilityWNotifications::sendNotification()
{
   sendDirect(notification,
              targetModule,
              targetGateName.c_str());
}

void
BonnMotionMobilityWNotifications::
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

void
BonnMotionMobilityWNotifications::printState()
{
   ev << "Node ID: " << nodeId << "\n"
      << "Position: " << lastPosition.x << ", " 
      << lastPosition.y << "\n"
      << "Speed: " << lastSpeed.length() << "\n"
      << "Pause time: " << pauseTime << "\n"
      << "Motion time: " << motionTime << "\n"
      << "Flight length: " << flightLength << endl;
}
