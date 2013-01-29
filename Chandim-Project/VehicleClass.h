#pragma once
#define DEF_VLENGTH
#include "CommonDefs.h"

class VehicleClass;
typedef std::queue<VehicleClass> VehicleQueue;

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
         //VehicleClass(int ID, int sDestination...)     !!Constructor
         //!!Constructor
         void updateDirection (dir Direction)
         {
              currentDirection = Direction;     
         }
         
         dir getDirection ()
         {
             return currentDirection;    
         }

         void setLastQ (VehicleQueue* Q)
         {
              LastQ = Q;
         }
         
         VehicleQueue* getLastQ ()
         {
             return LastQ;    
         }
         
         int getDestination ()
         {
             return fDestination;
         }
};
