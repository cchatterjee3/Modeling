#pragma once 
#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"
#include "Intersection.h"


//class TrafficLight;

class IntersectionwithSignal : public Intersection
{
  private:
         TrafficLight* EB;
         TrafficLight* WB;
         TrafficLight* NB;
         TrafficLight* SB;
         int curphase; //current phase //needs review, because each traffic light has its own phase.
         //bool busyNB; bool busySB; bool busyEB; bool busyWB;
  public:
		
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
         void changeSignalTrigger(); //checks its own signals 
         int QCanGo(VehicleQueue* Q );
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

