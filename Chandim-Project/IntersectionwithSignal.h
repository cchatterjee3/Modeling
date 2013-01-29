
#include <queue>

#define TPassTime = 3.0 //time to go straight in seconds
#define LPassTime = 2.0 //time to turn left in seconds


//#include "TrafficLight.h"

class TrafficLight;

class IntersectionwithSignal
{
  private:
         int ID;
         TrafficLight* EB;
         TrafficLight* WB;
         TrafficLight* NB;
         TrafficLight* SB;
         int curphase; //current phase //needs review, because each traffic light has its own phase.
         dir routingtable[12]; //for routing cars
         VehicleQueue* EBI;
         VehicleQueue* EBO;
         VehicleQueue* WBI;
         VehicleQueue* WBO;
         VehicleQueue* NBI;
         VehicleQueue* NBO;
         VehicleQueue* SBI;
         VehicleQueue* SBO;
         bool busy; // busy or not
         
  public:
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         void addVehicletoQueue(VehicleQueue* joinqueue); //Adds to outgoing queue or removes vehicles 
         void changeSignalTrigger(); //checks its own signals 
         
         int getID()
         {
         	return ID;
         }
         
         //constructor:
        IntersectionwithSignal(int id, bool stat,dir *table,
		VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
		VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo);
		
        IntersectionwithSignal();
         //destructor:
        ~IntersectionwithSignal();
};
