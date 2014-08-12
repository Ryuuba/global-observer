package inet.mobility.single;

import inet.mobility.common.MovingMobilityBase;

simple Ns2MotionMobilityWithNotifications extends Ns2MotionMobility
{
   parameters:
      @class(Ns2MotionMobilityWithNotifications);
      string targetModuleName;
      string targetGateName;
}
