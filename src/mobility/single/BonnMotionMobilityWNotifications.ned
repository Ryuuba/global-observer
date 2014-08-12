package inet.mobility.single;

import inet.mobility.common.MovingMobilityBase;

simple BonnMotionMobilityWNotifications extends BonnMotionMobility
{
   parameters:
      @class(BonnMotionMobilityWNotifications);
      string targetModuleName;
      string targetGateName;
}
