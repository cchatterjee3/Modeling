#pragma once
#define DEF_VLENGTH
#include "CommonDefs.h"

class VehicleClass;
//typedef std::queue<VehicleClass> VehicleQueue;

class VehicleClass
{
  private:
         Time_t startTime;
         Time_t endTime;
         int fDestination; //final location
         int sDestination; //starting location
         int length; //vehicle length
         int ID; //car ID for simulation purpose
         dir currentDirection; //current direction
         VehicleQueue* LastQ;
  public:
  		void setEndTime(Time_t t);
  		int getID();
         //VehicleClass(int ID, int sDestination...)     !!Constructor
         //!!Constructor
         void updateDirection (dir Direction);
         
         
         
         dir getDirection ();
         

         void setLastQ (VehicleQueue* Q);
         
         
         VehicleQueue* getLastQ ();
         
         
         int getDestination ();
         
         VehicleClass(int id, int start, int Dest, Time_t starttime);
         VehicleClass();
         ~VehicleClass();
};
