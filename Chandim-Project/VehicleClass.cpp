#include "VehicleClass.h"

void VehicleClass::setEndTime(Time_t t){
	endTime= t;
}
int VehicleClass::getID(){
	return this->ID;
}
//VehicleClass(int ID, int sDestination...)     !!Constructor
//!!Constructor
void VehicleClass::updateDirection (dir Direction)
{
    currentDirection = Direction;     
}

dir VehicleClass::getDirection ()
{
   return currentDirection;    
}

void VehicleClass::setLastQ (VehicleQueue* Q)
{
    LastQ = Q;
}

VehicleQueue* VehicleClass::getLastQ ()
{
   return LastQ;    
}

int VehicleClass::getDestination ()
{
   return fDestination;
}


VehicleClass::VehicleClass(int id, int start, int Dest, Time_t starttime){ID=id; sDestination = start; fDestination=Dest; startTime = starttime;};
VehicleClass::VehicleClass(){};
VehicleClass::~VehicleClass(){};
