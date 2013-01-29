#pragma once

#define DEF_VLENGTH

#include "CommonDefs.h"

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
};
