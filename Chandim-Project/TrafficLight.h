/**
*  @file TrafficLight.h
*   \brief description of functionality of traffic light
*/
#pragma once

#include "CommonDefs.h"


#include "CommonDefs.h"
#include "VehicleClass.h"
#include "Simulator.h"

extern Simulator* sim ;
class IntersectionwithSignal;

class TrafficLight
{
private:
	double GLT; /**< Green Left */
	double YLT; /**< Yellow Left */
	double RLT; /**< Right Left */
	double GTR; /**< Green Through */
	double YTR; /**< Yellow Through */
	double RTR; /**< Right Through */

	state curstate;   /**< Current state of the traffic light */
	state leftstate;  /**< Left state of the traffic light */


	IntersectionwithSignal* parent; /**< // Parent Intersection (to which it belongs to) */
public:
	int type; /**< 0 if 3 states and 1 if 6 states and 2 if there are two independent signals */
	int myid; /**< Id of the traffic signal */

	/**
	*  Returns the type of traffic light
	*
	*/
	int getType()
	{
		return type;
	}

	/**
	*  Returns the present state of the traffic light
	*
	*/
	state getState()
	{
		return curstate;
	}

	/**
	*  Returns the present left state of the traffic light
	*
	*/
	state getLeftState()
	{
		return leftstate;
	}

	/**
	*  Default constructor
	*
	*/
	TrafficLight();



	/**
	*  Constructor with initial states and everything
	*   (type, initialState GLT, YLT, RLT, GTR, YTR, RTR)
	*    put zeros if any was inapplicable
	*/
	TrafficLight(int id, int typ, state initialState, state initialstate2, double Ph1, double Ph2, double Ph3, double Ph4,
	             double Ph5, double Ph6, IntersectionwithSignal* p, Time_t timetoStart, Time_t timetoStart2);

	/**
	*  Default destructor
	*
	*/
	~TrafficLight();

	/**
	*  cyclestate
	*
	*/
	void cyclestate(int leftorthru);


};
