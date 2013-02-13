#include "TrafficLight.h"
#include "IntersectionwoSignal.h"
#include <memory.h>
#include "Simulator.h"
extern Simulator* sim ;

class VehicleQueue;

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

	cout << "In NoSignal::VehiclePass with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	dir dest;
	busy=true;

	//schedule vehicle deprature in service time
	sim->Schedule(PassTime, &IntersectionwithoutSignal::VehicleDeparture, this, vehicle);//(debug)

	cout << "--> VehicleDeparture scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+PassTime <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

}

void IntersectionwithoutSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{

	cout << "In NoSignal::VehicleDeparture with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	//freeing intersection
	this->busy=false;


	//scheduling next queue join
	dir dest=this->routingtable[vehicle->getDestination()]; // finds routing direction
	if(dest==N)
	{
		if(ID==5)
		{
			// exit the system
			vehicle->setEndTime(sim->getNow());
			ExitQ->push(vehicle);
		}
		//schedule north intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event
			
			cout << "joining northern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

/*(NBI->NBI1)			sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
				NInter , NInter->NBI , vehicle); //(debug) */
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
		}
	}
	else if (dest==S)
	{
		if(ID==1)
		{
			// exit the system
			vehicle->setEndTime(sim->getNow());
			ExitQ->push(vehicle);
		}
		//schedule south intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event

			cout << "joining southern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

/*(NBI->NBI1)			sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
				SInter , SInter->NBI , vehicle); //(debug) */
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
		}
	}
	else
	{
		// exit the system
		vehicle->setEndTime(sim->getNow());
		ExitQ->push(vehicle);
		cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
	}


	//checking if there is another car in Queue and the light is green
	if(busy=false)
	{
			//schedule another vehicle pass in service time
			sim->Schedule(PassTime, &IntersectionwithoutSignal::VehiclePass, this, vehicle);//(debug)
	}

}

void IntersectionwithoutSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	cout << "In WithoutSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	joinqueue->push(vehicle);
	vehicle->setLastQ(joinqueue);

	if(  !busy )
	{
		VehicleClass* vehicle=joinqueue->front();
		joinqueue->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(joinqueue);
		sim->Schedule(startToPass, &IntersectionwithoutSignal::VehiclePass, this, vehicle);//(debug)

		cout << "--> VehiclePass scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+startToPass <<endl;
		cout << "press any key to continue..."<<endl;	cin.get() ;

	}
}
