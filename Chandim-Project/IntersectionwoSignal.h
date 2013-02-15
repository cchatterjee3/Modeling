#pragma once

#include <queue>
#include "CommonDefs.h"
#include "Intersection.h"


class IntersectionwithoutSignal : public Intersection
{
  private:

  public:
		//void VehicleArrival(VehicleClass* vehicle);//Add to queue
		void VehiclePass(VehicleClass* vehicle, int Turn); //Vehicle passes through intersection
		void VehicleDeparture (VehicleClass* vehicle); //Depart
		virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
		void EvictQ (VehicleQueue* joinqueue);
		int QCanGo (int direction, int lane);

		//constructor:
        IntersectionwithoutSignal();
        IntersectionwithoutSignal(int);
         //destructor:
        ~IntersectionwithoutSignal();

};
