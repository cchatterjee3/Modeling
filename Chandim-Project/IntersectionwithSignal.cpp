#include "TrafficLight.h"
#include "IntersectionwithSignal.h"

#include <memory.h>

IntersectionwithSignal::IntersectionwithSignal()
{
	
}

IntersectionwithSignal::IntersectionwithSignal(int id, bool stat,dir *table,
VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo)
{
	//initialize state
	ID=id;
	busy=stat;

	//initialize routing table
	memcpy(routingtable, table, 12*sizeof(dir));
	//for (int i=0;i<12;i++)
	//	routingtable[i]=table[i];


	EBI=ebi;	EBO=ebo;	WBI=wbi;	WBO=wbo;	
	NBI=nbi;	NBO=nbo;	SBI=sbi;	SBO=sbo;	

	//setting each traffic light's type
	int EBtype, WBtype, NBtype, SBtype;

	if( ID ==1 || ID ==5 )
	{
		EBtype=1; WBtype=1; NBtype=1; SBtype=1;
		if( ID==5)
		{
			WBtype=0;
		}
	}
	else
	{
		EBtype=0; WBtype=0; NBtype=0; SBtype=0;
	}


	if( 1==1 ) //for all intersections for now // needs info from input data
	{
		EB=new TrafficLight(EBtype, (state)0, 1, 1, 1, 1, 1, 1);
		WB=new TrafficLight(WBtype, (state)0, 1, 1, 1, 1, 1, 1);
		NB=new TrafficLight(NBtype, (state)0, 1, 1, 1, 1, 1, 1);
		SB=new TrafficLight(SBtype, (state)0, 1, 1, 1, 1, 1, 1);
	}
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


