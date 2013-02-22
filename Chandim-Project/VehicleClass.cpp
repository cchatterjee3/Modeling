#include "VehicleClass.h"
#include<stdlib.h>



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

int VehicleClass::getSource ()
{
   return sDestination;
}


VehicleClass::VehicleClass(int id, int start, int Dest, Time_t starttime)
{
    out_of_line=false;
    ID=id;
	sDestination = start;
	fDestination=Dest;
	startTime = starttime;
	LastQ=NULL;

#ifdef test
    eventDsc E1;
    E1.type = CNS;
    E1.InterID =ID;
    E1.QDir = 0;
    E1.QLane = 0;
    E1.timetag = this->startTime;
    this->EventList.push_back(E1);
#endif
        


};
VehicleClass::VehicleClass(){};
VehicleClass::~VehicleClass(){};
