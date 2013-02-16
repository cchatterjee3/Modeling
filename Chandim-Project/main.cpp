
#include <iostream>
#include "Simulator.h"
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"
#include "Topology.h"
#include "scheduleVehicles.h"

#include "testing/test1.h"

using namespace std;

class Simulator;
Simulator* sim = new Simulator();

int main()
{
	//Temporary Initialization Place
	_Topology *Topology = new _Topology();

	

	/*
	int VIDcounter=0;
	VehicleQueue* joinqueue = Topology->I1->NBI2;
	for ( int t=0 ; t<100 ; t+=1000 )
	{
		VehicleClass* vehicle=new VehicleClass(++VIDcounter, 0, 4, t);
		sim->Schedule(t, &Intersection::addVehicletoQueue, Topology->I1, joinqueue, vehicle);
	}
	//scheduleVehicles(Topology, 7200.0);

	int VIDcounter=0;
	double t;
	VehicleClass* vehicle;
	VehicleQueue* joinqueue;
	Intersection* Inter;

	t=0;
	vehicle=new VehicleClass(++VIDcounter, 8,  4, t);
	Inter=Topology->I4;
	joinqueue = Inter->Qu[3][0];
	sim->Schedule(t, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);

	t=2;
	vehicle=new VehicleClass(++VIDcounter, 8,  5, t);
	Inter=Topology->I4;
	joinqueue = Inter->Qu[3][0];
	sim->Schedule(t, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);

	t=2;
	vehicle=new VehicleClass(++VIDcounter, 8,  3, t);
	Inter=Topology->I4;
	joinqueue = Inter->Qu[3][1];
	sim->Schedule(t, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);

	t=16;
	vehicle=new VehicleClass(++VIDcounter, 8, 10, t);
	Inter=Topology->I4;
	joinqueue = Inter->Qu[3][1];
	sim->Schedule(t, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);

	t=30;
	vehicle=new VehicleClass(++VIDcounter, 8,  6, t);
	Inter=Topology->I4;
	joinqueue = Inter->Qu[3][0];
	sim->Schedule(t, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);
*/
    

unittest(10, 50, Topology);


    sim->StopAt(500);
    sim->Run();
    cout << "post processing" << endl;
    cin.get() ;
    
    PrintEventList(Topology->ExitQ->back());
    cin.get() ;
    
    
    
    
    return 0;
}
