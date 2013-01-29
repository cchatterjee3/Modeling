#include <iostream>
#include "TrafficLight.h"
#include "IntersectionwithSignal.h"

#include <memory.h>
#include "Simulator.h"
extern Simulator* sim ;

//void schedule(void);

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
	
	switch (vehicle->getDirection())
	{
		case N:
			//Simulator::Schedule(1, IntersectionwithSignal::VehiclePass(vehicle), IntersectionwithSignal ,VehicleClass* vehicle);
			//sim->
			sim->Schedule(1, (&this)::VehiclePass,this, vehicle);			
			break;
	}
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
int IntersectionwithSignal::QCanGo(VehicleQueue* Q) //checks its own signals 
{
	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the first member of Queue
	//+1: Yes, the queue is not empty and the trafficc light is green
	
	bool canGo;

	if(Q->empty())
	{
		return -1;
	}
	VehicleClass* NextVeh; // define a Vehicle pointer
	dir dest=this->routingtable[NextVeh->getDestination()];
	//--------------------------------------------
	if(Q==EBI)
	{
		switch(dest)
		{
			case S:
				canGo=(EB->getState()==GTR);
				break;
			case E:
				canGo=(EB->getState()==GTR);
				break;
			case N:
				canGo=(EB->getState()==GLT); // or, the other direction is not busy(debug)
				break;
		}
	}
	//--------------------------------------------
	else if(Q==WBI)
	{
		switch(dest)
		{
			case N:
				canGo=(WB->getState()==GTR);
				break;
			case W:
				canGo=(WB->getState()==GTR);
				break;
			case S:
				canGo=(WB->getState()==GLT);
				break;
		}
	}
	//--------------------------------------------
	else if(Q==NBI)
	{
		switch(dest)
		{
			case E:
				canGo=(NB->getState()==GTR);
				break;
			case N:
				canGo=(NB->getState()==GTR);
				break;
			case W:
				canGo=(NB->getState()==GLT);
				break;
		}
	}
	//--------------------------------------------
	else if(Q==SBI)
	{
		switch(dest)
		{
			case W:
				canGo=(SB->getState()==GTR);
				break;
			case S:
				canGo=(SB->getState()==GTR);
				break;
			case E:
				canGo=(SB->getState()==GLT);
				break;
		}
	}
	if(canGo==true)
		return 1;
	else
		return 0;

}

