/**
*	@file postprocessing.h
*	Takes Exit Queue As Argument and print Various following things
* 	1. Histogram of simulation time
*
*/

#include "VehicleQueue.h"


/** 
* 	Takes exit queue and prints histogram of time takes to cover between source and destination
* 	Also prints stats like, average time , standard deviation etc.
*	@param EQ is exit Q
*	@param buckets is number of buckets for histogram
*	@param timeval is the  period of time which is divided into buckets 
*	@param source is starting point of the journey
*	@param dest is input for describing 
*/
void PostProcStats(VehicleQueue* EQ, double timeval, int buckets,int source, int dest);


