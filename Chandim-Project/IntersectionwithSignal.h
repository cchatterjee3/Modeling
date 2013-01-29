
#include <queue>
#include "CommonDefs.h"


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
         bool busyNB; bool busySB; bool busyEB; bool busyWB;
  public:
  		IntersectionwithSignal* NInter;//(debug)
  		IntersectionwithSignal* SInter;//(debug)
		
         //void VehicleArrival(VehicleClass* vehicle);//Add to queue
         void VehiclePass(VehicleClass* vehicle); //Vehicle passes through intersection
         void VehicleDeparture (VehicleClass* vehicle); //Depart
         void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle); //Adds to outgoing queue or removes vehicles 
         void changeSignalTrigger(); //checks its own signals 
         int QCanGo(VehicleQueue* Q );
         
//         int getID()
//         {
//         	return ID;
//         }
         
         //constructor:
        IntersectionwithSignal(int id, bool stat,dir *table,
		VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
		VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo);
		
        IntersectionwithSignal();
         //destructor:
        ~IntersectionwithSignal();
};
