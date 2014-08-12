cplusplus
{{
#include <Coord.h>
#include <cstdint>
}};

class noncobject Coord;

message Notification
{
   Coord position;
   simtime_t pauseTime;
   simtime_t motionTime;
   double speed;
   uint32_t source;
   double flightLength;
};
