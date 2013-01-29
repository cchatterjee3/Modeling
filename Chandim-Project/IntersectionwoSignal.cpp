#include "TrafficLight.h"
#include "IntersectionwoSignal.h"

#include <memory.h>

IntersectionwithoutSignal::IntersectionwithoutSignal()
{
	
}

IntersectionwithoutSignal::IntersectionwithoutSignal( bool stat,dir *table,
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

IntersectionwithoutSignal::~IntersectionwithoutSignal(void)
{
	
}

void IntersectionwithoutSignal::VehiclePass(VehicleClass* vehicle) //Vehicle passes through intersection
{
	
}
void IntersectionwithoutSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{
	
}
void IntersectionwithoutSignal::addVehicletoQueue(VehicleQueue* joinqueue) //Adds to outgoing queue or removes vehicles 
{
	
}

