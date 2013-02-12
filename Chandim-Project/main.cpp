
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

	/*
	int VIDcounter=1;
	VehicleQueue* joinqueue = Topology->I1->NBI;

	for ( int t=1 ; t<100 ; t+=100 )
	{
		VehicleClass* vehicle=new VehicleClass(VIDcounter++, 0, 6);
		sim->Schedule(t, &Intersection::addVehicletoQueue, Topology->I1, joinqueue, vehicle);
	}
*/
	scheduleVehicles(Topology);

	cout << Topology->I1->getID() << endl;
	cin.get() ;



    sim->StopAt(100);
    sim->Run();
    cin.get() ;
    return 0;
}

