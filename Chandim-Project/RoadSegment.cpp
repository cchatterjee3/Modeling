#include "RoadSegment.h"

//enum dir {N, S, E, W};

void RoadSegment::AddVehicle(VehicleClass* vehicle)
{
  dir direction = parent->routingtable[vehicle->getDestination()];
  switch (Direction)
  {
    case N:
         switch (direction)
         {
           case W:
             qleft->push(vehicle);
             break;
           default:
             qright->push(vehicle);
             break;        
         }
    case S:
         switch (direction)
         {
           case E:
             qleft->push(vehicle);
             break;
           default:
             qright->push(vehicle);
             break;        
         }  
    case E:
         switch (direction)
         {
           case N:
             qleft->push(vehicle);
             break;
           default:
             qright->push(vehicle);
             break;        
         } 
    case W:
         switch (direction)
         {
           case S:
             qleft->push(vehicle);
             break;
           default:
             qright->push(vehicle);
             break;        
         }        
  }
  population++;    
   
}


void RoadSegment::EvictVehicle(int id)
{
              
}
