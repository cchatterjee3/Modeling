#include "TrafficLight.h"
#include "IntersectionwoSignal.h"

#include <memory.h>
#include "Simulator.h"
extern Simulator* sim ;

IntersectionwithoutSignal::IntersectionwithoutSignal()
{
	busy=false;
}

IntersectionwithoutSignal::IntersectionwithoutSignal( bool stat,dir *table,
VehicleQueue* ebi, VehicleQueue* ebo, VehicleQueue* wbi, VehicleQueue* wbo, 
VehicleQueue* nbi, VehicleQueue* nbo, VehicleQueue* sbi, VehicleQueue* sbo)
{
	//initialize state
	busy=stat;

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
	VehicleQueue* LastQ=vehicle->getLastQ();
	VehicleClass* nextVeh;

	busy=true;
	//schedule vehicle deprature in service time
	sim->Schedule(PassTime, &IntersectionwithoutSignal::VehicleDeparture, this, vehicle);//(debug)
	//checking if there is another car in Queue and intersection is empty
	if(LastQ==NBI || LastQ==NBI) //without stop signs
	{
		//schedule vehicle pass in startToPass time
		if(!LastQ->empty())
		{
			nextVeh=&(LastQ->front());
			LastQ->pop();
			nextVeh->setLastQ(LastQ);
			sim->Schedule(startToPass, &IntersectionwithoutSignal::VehiclePass, this, vehicle);//(debug)
		}
	}
}

void IntersectionwithoutSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{
	//freeing intersection
	this->busy=false;

	//scheduling next queue join
	dir dest=this->routingtable[vehicle->getDestination()]; // finds routing direction
	if(dest==N)
	{
		//schedule north intersection addVehicletoQueue
	}
	else if (dest==S)
	{
		//schedule south intersection addVehicletoQueue
	}
	else
	{
		// schedule exit
	}
	//if(NBI->epmty() && )
	// schedule EB and westbound departures based on the intersection being busy
	//not possible until define busy directions
}

void IntersectionwithoutSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{
	joinqueue->push(*vehicle);
	//check busy directions, schedule departure	
}

