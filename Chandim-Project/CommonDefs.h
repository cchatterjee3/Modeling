#pragma once

#include <queue>
#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__

//variables
#define PassTime  4.0 //service time to go straight in seconds
#define startToPass  2.0 //when a queue is empty and a vehicle arrives, it takes this much to depart
#define LPassTime  3.0 //service time to turn left in seconds (debug)
#define roadSegTime  15.0 //time to travel one road segment



typedef double Time_t;
enum state {GLT, YLT, RLT, GTR, YTR, RTR};
enum dir {N, S, E, W};
//#include "VehicleClass.h"
class VehicleClass;
typedef std::queue<VehicleClass* > VehicleQueue;


#endif
