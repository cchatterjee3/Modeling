#include "TrafficLight.h"
#include "IntersectionwithSignal.h"

#include <memory.h>

IntersectionwithSignal::IntersectionwithSignal()
{
	
}

IntersectionwithSignal::IntersectionwithSignal( bool stat,dir *table,
VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo)
{
	//initialize state
	state=stat;

	//initialize routing table
	memcpy(routingtable, table, 12*sizeof(dir));
	//for (int i=0;i<12;i++)
	//	routingtable[i]=table[i];


	EBI=ebi;	EBO=ebo;	WBI=wbi;	WBO=wbo;	
	NBI=nbi;	NBO=nbo;	SBI=sbi;	SBO=sbo;	
}

IntersectionwithSignal::~IntersectionwithSignal(void)
{
	
}

void IntersectionwithSignal::VehiclePass(VehicleClass* vehicle) //Vehicle passes through intersection
{
	
}
void IntersectionwithSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{
	
}
void IntersectionwithSignal::addVehicletoQueue(VehicleQueue* joinqueue) //Adds to outgoing queue or removes vehicles 
{
	
}
void IntersectionwithSignal::changeSignalTrigger() //checks its own signals 
{
	
}


