#include <queue>
#include <VehicleClass.h>
#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__


typedef double Time_t;
enum state {GLT, YLT, RLT, GTR, YTR, RTR};
enum dir {N, S, E, W};
typedef queue<VehicleClass> VehicleQueue;

#endif
