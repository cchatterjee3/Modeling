#include <queue>
#include "TrafficLight.h"

class IntersectionwithSignal
{
  private:
         int ID;
         TrafficLight EB;
         TrafficLight WB;
         TrafficLight NB;
         TrafficLight SB;
         int curphase; //current phase 
         dir routingtable[12]; //for routing cars
         VehicleQueue* EBI;
         VehicleQueue* EBO;
         VehicleQueue* WBI;
         VehicleQueue* WBO;
         VehicleQueue* NBI;
         VehicleQueue* NBO;
         VehicleQueue* SBO;
         VehicleQueue* SBI;
         bool state; // busy or not
         
         
  public:    
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         void addVehicletoQueue(VehicleQueue* joinqueue); //Adds to outgoing queue or removes vehicles 
         void changeSignalTrigger(); //checks its own signals 
};
