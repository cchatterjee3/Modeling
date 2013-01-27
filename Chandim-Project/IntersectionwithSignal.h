#include <queue>

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
         bool state[2]; // busy or not
         
  public:    
         void Arrival();//    
};
