#pragma once 
#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"
#include "Intersection.h"

//class TrafficLight;

class IntersectionwithSignal : public Intersection
{
  private:
         int curphase; //current phase //needs review, because each traffic light has its own phase.
         //bool busyNB; bool busySB; bool busyEB; bool busyWB;
  public:

         TrafficLight* EB;
         TrafficLight* WB;
         TrafficLight* NB;
         TrafficLight* SB;
		 TrafficLight* TLight[4] ;
                 
         void changeSignalTrigger( int LightID, int leftorthru); //checks its own signals //leftortur=1: left
         virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
		 virtual int QCanGo (int direction, int lane);

         //constructor:
        IntersectionwithSignal();
        IntersectionwithSignal(int);
		 //destructor:
		~IntersectionwithSignal();
};

