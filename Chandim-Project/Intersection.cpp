#include <iostream>

#include "Intersection.h"
#include "CommonDefs.h"

using namespace std;

Intersection::Intersection(int nID)
{
		ID=nID;
		//Queues------------------------------------------
		busy=false;
		switch (ID){
			case 4:
				haveSignal=false;
				break;
			default: // other intersections
				haveSignal=true;
				break;
		}
		//Queues------------------------------------------
		EBI=new VehicleQueue;
		WBI=new VehicleQueue;
		NBI=new VehicleQueue;
		SBI=new VehicleQueue;
		//initialize routing table
		//memcpy(routingtable, table, 12*sizeof(dir));
		switch (ID){
			/*
			case 1: //(debug)
				routingtable={N,N,N,N,N,N,N,N,N,N,N,N};
				break;
			*/
			default: // other intersections
				dir routingtable[12]={N,N,N,N,N,N,N,N,N,N,N,N};
				break;
		}
		
		if(haveSignal)
			cout << "Intersection ID=" << ID << " created with    signal"<<endl;
		else
			cout << "Intersection ID=" << ID << " created without signal"<<endl;
		
};

Intersection::Intersection(){};
Intersection::~Intersection(){};

