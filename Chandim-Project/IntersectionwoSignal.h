#pragma once

#include <queue>
#include "CommonDefs.h"
#include "Intersection.h"


class IntersectionwithoutSignal : public Intersection
{
  private:
         //int curphase; //current phase //needs review
  public:
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
         //constructor:
	
        IntersectionwithoutSignal();
        IntersectionwithoutSignal(int);
         //destructor:
        ~IntersectionwithoutSignal();

};

