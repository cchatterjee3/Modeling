
/**
*   @file IntersectionwithSignal.h
*   Description of Intersection with traffic signals class
*   @see Intersection.h
*/
#pragma once 
#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"
#include "Intersection.h"

//class TrafficLight;

class IntersectionwithSignal : public Intersection
{
  private:
         int curphase; /**< //current phase //needs review, because each traffic light has its own phase. */
         //bool busyNB; bool busySB; bool busyEB; bool busyWB;
  public:

         TrafficLight* EB;  /**< East bound Traffic lights */
         TrafficLight* WB;  /**< West bound Traffic lights */
         TrafficLight* NB;  /**< North bound Traffic lights */
         TrafficLight* SB;  /**< South bound Traffic lights */
		 TrafficLight* TLight[4] ;
                 
         /**
         *    checks its own signals
         *    leftortur=1: left
         */
         void changeSignalTrigger( int LightID, int leftorthru);
         /**
         *    Adds to outgoing queue or removes vehicles 
         *
         */
         virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); 
         /**
         *    If the queue can go in "direction,lane"
         *
         */
		 virtual int QCanGo (int direction, int lane);

         /**
         *    Default Constructor
         *
         */
        IntersectionwithSignal();
        /**
        *    COnstror sets the ID of the intersection
        *
        */
        IntersectionwithSignal(int);
		 /**
         *    Destructor
         *
         */
		~IntersectionwithSignal();
};

