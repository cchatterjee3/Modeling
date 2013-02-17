/**
*	Takes Exit Queue As Argument and print Various following things
* 	1. Histogram of simulation time
*
*/

#include "VehicleQueue.h"


/*
* 	Takes exit queue and prints histogram of time takes to cover between source and destination
* 	Also prints stats like, average time , standard deviation etc.
*/
void PostProcStats(VehicleQueue* EQ, double TimeInterval, int buckets,int source, int dest);
