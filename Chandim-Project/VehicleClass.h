#pragma once
#define DEF_VLENGTH
#include "CommonDefs.h"


#include "testing/test1.h"



#ifdef test
    #include <list>
    #include "Simulator.h"
    extern Simulator* sim ;
#endif

class VehicleClass;
class VehicleQueue;
//typedef std::queue<VehicleClass> VehicleQueue;

class VehicleClass
{
  private:
         int fDestination; //final location
         int sDestination; //starting location
         int length; //vehicle length
         int ID; //car ID for simulation purpose
         dir currentDirection; //current direction
         VehicleQueue* LastQ;
  public:
         Time_t startTime;
         Time_t endTime;

#ifdef test
      std::list<eventDsc> EventList;
#endif      
  		void setEndTime(Time_t t);
  		int getID();
         //VehicleClass(int ID, int sDestination...)     !!Constructor
         //!!Constructor
         void updateDirection (dir Direction);

		 dir getDirection ();

		 void setLastQ (VehicleQueue* Q);

		 VehicleQueue* getLastQ ();
         
         Time_t StartTime(){return startTime;};
         Time_t EndTime(){return endTime;};
         
         int getDestination ();
		 int getSource ();
         
         VehicleClass(int id, int start, int Dest, Time_t starttime);
         VehicleClass();
         ~VehicleClass();
};
