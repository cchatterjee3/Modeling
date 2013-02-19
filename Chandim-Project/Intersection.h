/**
*	@file intersection.h
*	Contains base class intersection from which both intersectionwithsignal and intersectionwosignal inherit
*	@see IntersectionwithSignal.h
*	@see IntersectionwoSignal.h
*/
#pragma once

#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"
#include "VehicleClass.h"
#include "VehicleQueue.h"

//#include "TrafficLight.h"


class Intersection
{
  protected:
	int ID; 			/**< Intersection Id */
	bool haveSignal;	/**< Have traffic signal or not */

	bool busy; 			/**< Busy or not */
	

public:
	VehicleQueue* EBI1;	/**< Vehicle Queue East bound lane 1*/
	VehicleQueue* EBI2;	/**< Vehicle Queue East bound lane 2*/
	VehicleQueue* WBI1;	/**< Vehicle Queue West bound lane 1*/
	VehicleQueue* WBI2;	/**< Vehicle Queue West bound lane 2*/
	VehicleQueue* NBI1;	/**< Vehicle Queue North bound lane 1*/
	VehicleQueue* NBI2; /**< Vehicle Queue North bound lane 2*/
	VehicleQueue* SBI1; /**< Vehicle Queue South bound lane 1*/
	VehicleQueue* SBI2; /**< Vehicle Queue South bound lane 2*/

	VehicleQueue* Qu[4][2];
	
	dir routingtable[12]; /**< Acts as trnslator for routing cars */
	/*VehicleQueue* EBI;
	VehicleQueue* WBI;
	VehicleQueue* SBI;
	VehicleQueue* NBI;*/
	
	//int EBIlength;
	//int WBIlength;
	int NBIlength;
	int SBIlength;

	VehicleQueue* ExitQ;	/**< all vehicle exiting the system are queued into Exit queue for post processing */

	Intersection* NInter;	/**< Neighboring intersection in the North */
	Intersection* SInter;	/**< Neighboring intersection in the South */
	
	/**
	*	Default Constructor
	*
	*/
	Intersection();

	/**
	*	Constructor
	*	@param num
	*/
	Intersection(int num);

	/**
	*	Default destructor
	*
	*/
	~Intersection();

	/**
	*	Returns the ID of the intersection
	*
	*/
	int getID()	{return ID;}
	
	//void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle);
	/**
	*	Logic of vehicle passing through this intersection
	*	@param Vehicle
	*	@param turn
	*/
	void VehiclePass(VehicleClass* vehicle, int Turn); 

	/**
	*	Departs Vehicle from the intersection
	*	@param vehicle is the vehicle to be departed
	*/
	void VehicleDeparture (VehicleClass* vehicle); 

	/**
	*	Evicts the Vehicle Queue
	*
	*/
	void EvictQ (VehicleQueue* joinqueue);

	/**
	*	Virtual function
	*	Adds vehicle into queue
	*/
	virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle)=0;

	/**
	*	QCAnGo
	*
	*/
	virtual int  QCanGo (int direction, int lane)=0; 

	/**
	*	Gets the direction of the queue
	*
	*/
    int getQdirection(Intersection * inter, VehicleQueue* Q);
    /**
    *	Get the queue lane
    *
    */
    int getQlane(Intersection * inter, VehicleQueue* Q);

    /**
    *	Gets the next queue info
    *
    */
	void NextQInfo(VehicleQueue* currentQ, VehicleClass* vehicle, Intersection * &  NextInter, VehicleQueue * & FutureQ, bool & isfull, int & Turn);

};

