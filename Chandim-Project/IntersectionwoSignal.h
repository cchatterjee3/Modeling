/**
*   @file IntersectionwoSignal.h
*   Description of Intersection with out traffic signals class
*   @see Intersection.h
*/
#pragma once

#include <queue>
#include "CommonDefs.h"
#include "Intersection.h"


class IntersectionwithoutSignal : public Intersection
{
  private:

  public:
		//void VehicleArrival(VehicleClass* vehicle);//Add to queue
    /**
    *  Adds to outgoing queue or removes vehicles 
    *
    */
		virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); 

    /**
    *  Figures if the Q(direction,lane) can starts moving
    *
    */
		virtual int QCanGo (int direction, int lane);

    /**
    *  Default constructor
    *
    */		
    IntersectionwithoutSignal();
    /**
    *  Constructor with setting ID
    *
    */
    IntersectionwithoutSignal(int);
     /**
     *  Default Destructor
     *
     */
    ~IntersectionwithoutSignal();

};
