
#include <iostream>
#include "Simulator.h"

#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"

#include "Topology.h"

#include "scheduleVehicles.h"

using namespace std;

class Simulator;
Simulator* sim = new Simulator();

int main()
{
	//Temporary Initialization Place
	_Topology *Topology = new _Topology();

	
	int VIDcounter=1;
	VehicleQueue* joinqueue = Topology->I1->NBI2;

	for ( int t=0 ; t<100 ; t+=1000 )
	{
		VehicleClass* vehicle=new VehicleClass(VIDcounter++, 0, 4, sim->Now());
		sim->Schedule(t, &Intersection::addVehicletoQueue, Topology->I1, joinqueue, vehicle);
	}

	//scheduleVehicles(Topology, 7200.0);



    sim->StopAt(500);
    sim->Run();
    cin.get() ;
    return 0;
}

