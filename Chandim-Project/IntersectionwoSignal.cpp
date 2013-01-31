#include "TrafficLight.h"
#include "IntersectionwoSignal.h"
#include <memory.h>
#include "Simulator.h"
extern Simulator* sim ;

IntersectionwithoutSignal::IntersectionwithoutSignal(int nID) : Intersection(nID)
{
}
IntersectionwithoutSignal::IntersectionwithoutSignal( )
{

}
IntersectionwithoutSignal::~IntersectionwithoutSignal(void)
{
	
}
void IntersectionwithoutSignal::VehiclePass(VehicleClass* vehicle) //Vehicle passes through intersection
{
	cout << "In WithoutSignal::VehiclePass with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

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

