/**
*	@file CommonDefs.h
*	Contains commmon definations of various parameters used in different functions
*/
#pragma once

#include <queue>
#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__

//variables
#define PassTime  5.0 		/**< service time to go straight in seconds */
#define startToPass  2.0 	/**< when a queue is empty and a vehicle arrives, it takes this much to depart */
#define LPassTime  3.0 		/**< service time to turn left in seconds (debug) */
#define roadSegTime  36.0 	/**< time to travel one road segment */
#define checkQinterval 2.0 	/**< if the next Q is full, check again in this amout of time */
#define BurstTime 2.0 		/**< time for the next vehicle to depart when cars are going in groups */


typedef double Time_t;						/**< Type for storing simulation times */

enum state {GLT, YLT, RLT, GTR, YTR, RTR};	/**< Enumerating traffic Light stats */

enum dir {N, S, E, W};						/**< Enumerating Directions */
	
class VehicleClass;
//typedef std::queue<VehicleClass* > VehicleQueue;

//these 2 definitions in intersection.cpp
/**
*	@see intersection.cpp
*
*/
int reg(int i);

/**
*	Returns routing address for Vehicle
*	@see intersection.cpp
*
*/
int turn(dir globalDir, int QDirection);


#endif
