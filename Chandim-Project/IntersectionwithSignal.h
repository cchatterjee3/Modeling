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

         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
         void changeSignalTrigger( int LightID); //checks its own signals 
		 void EvictQ (VehicleQueue* joinqueue);
		 int QCanGo (VehicleQueue* Q );
		 int QCanGo (int direction, int lane);

         //constructor:
         	/*
        IntersectionwithSignal(int id, bool stat,dir *table,
		VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
		VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo);
		*/
		
        IntersectionwithSignal();
        IntersectionwithSignal(int);
        
		 //destructor:
        
		~IntersectionwithSignal();
};

