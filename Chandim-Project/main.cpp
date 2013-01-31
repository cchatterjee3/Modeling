
#include <iostream>
#include <conio.h>
#include "Simulator.h"

#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"

#include "Topology.h"

using namespace std;

class Simulator;
Simulator* sim = new Simulator();

int main()
{
	//Temporary Initialization Place
	_Topology *Topology = new _Topology();

	int VIDcounter=1;
	VehicleQueue* joinqueue = Topology->I1->NBI;

	for ( int t=1 ; t<100 ; t+=10 )
	{
		VehicleClass* vehicle=new VehicleClass(VIDcounter++, 1);
		sim->Schedule(t, &Intersection::addVehicletoQueue, Topology->I1, joinqueue, vehicle);
	}

	cout << Topology->I1->getID() << endl;
	cin.get() ;



    sim->StopAt(100);
    sim->Run();
    getch();
    return 0;
}

