#pragma once

#include <queue>
#include "CommonDefs.h"
#include "Intersection.h"


class IntersectionwithoutSignal : public Intersection
{
  private:

  public:
		//void VehicleArrival(VehicleClass* vehicle);//Add to queue
		virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
		virtual int QCanGo (int direction, int lane);

		//constructor:
        IntersectionwithoutSignal();
        IntersectionwithoutSignal(int);
         //destructor:
        ~IntersectionwithoutSignal();

};
