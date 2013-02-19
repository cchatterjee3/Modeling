/**
*	@file main.cpp
*
*/
#include <iostream>
#include "Simulator.h"
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"
#include "Topology.h"
#include "scheduleVehicles.h"
#include "PostProcessing.h"

#include "testing/test1.h"

#include<queue>

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
    

    unittest(100000, 100000, Topology);


    sim->StopAt(100000);
    sim->Run();
    cout << "post processing" << endl;
    cout << "ExitQ has " << Topology->ExitQ->Q1.size() << " members";
    cin.get() ;

    PostProcStats(Topology->ExitQ, 1000,  30, 0, 7);
    cin.get();

    VehicleQueue * Q;
    Intersection * I;
    
    cout << endl;

    cout <<"missing cars:" << endl;
    cout << endl;
    cin.get();
    for (int inter = 0 ; inter<5 ; ++inter)
    {
        for (int direction = 0 ; direction<4 ; ++direction)
        {
            for (int lane = 0 ; lane<2 ; ++lane)
            {
                
                I=Topology->In[inter];
                Q=I->Qu[direction][lane];
                if(Q->Q1.size())
                {
                    cout << Q->Q1.size()<<" Intersection:"<<inter+1<<" Lane:"<<lane<<" Direction:"<<direction<<endl;
                    cout << "   ID: " << Q->Q1.front()->getID() 
                         << " dest: " << Q->Q1.front()->getDestination() 
                         << "start: " << Q->Q1.front()->startTime
                         << endl;
    
                }
            }
            
        }
    }
    cin.get();
    
    
    return 0;
}
