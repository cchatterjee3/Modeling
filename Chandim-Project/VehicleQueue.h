/***
*	@file VehicleQueue.h	
*	brief decs for vehicle queue class , which is a FIFO queue with 
*
*/
#ifndef VEHICLEQUEUE_H
#define VEHICLEQUEUE_H

#include "VehicleClass.h"


class VehicleQueue
{
private:
    
    int maxLength;					/**< To hold the maximum length of the Queue */

public:

    //std::queue<VehicleClass* > Q1;	/**< std::Queue for holding the vehicle queue */
    
	std::deque<VehicleClass* > Q1;	/**< std::Queue for holding the vehicle queue */

    int busy;						/**< to check if the queue is busy/not */
    double LastSentCar;				/**< Holds time for vehicle that was sent last */

    /**
    *	Default constuctor
    *
    */
    VehicleQueue();

    /**
    *	Returns pointer of the vehicle which is front of the queue
    *
    */
    
    VehicleClass* front();

    /**
    *	Returns "true" if the queue is empty
    *
    */
    bool empty();

    /**
    *	Adds vehicle to the back of the queue 
    *	@param	V1 is pointer of the vehicle to be pushed into the queue
    *
    */
    void push(VehicleClass* V1);
    /**
    *	Returns (and removes ) vehicle that was latest existing vehicle in the queue
    *
    */
    void pop();

    /**
    *	Returns pointer to the vehicle that is at the end of the queue
    *
    */
    VehicleClass* back();
    /**
    *	Returns Maximum possible lenght of the queue
    *
    */
    int  GetMaxLen();
    /**
    *	Returns lenght of the queue (i.e. how many vehicles are there in the queue)
    *
    */
    int  GetLen();

    /**
    *	Returns if the queue is busy or not
    *
    */
    bool isBusy();
};

#endif
