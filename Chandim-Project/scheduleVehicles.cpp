
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Simulator.h"
#include "Topology.h"
#include "RandomNum.h"

extern Simulator* sim ;
RandomNumGen Ran;



void scheduleVehicles(	_Topology* Topology)
{

double lambda[12]={0.1597,0.0369,0.0099,0.0163,0.0154,0.0287,0.2913,
				   0.1213,0.0205,0.0158,0.0545,0.0655};


printf("///////////////////////////////\n");
printf("/// generating all arrivals ///\n");
printf("///////////////////////////////\n");

VehicleQueue* joinqueue[12];
Intersection* joininter[12];

for (int i=0 ; i<12 ; ++i)
{
	switch (i)
	{
		case 0:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->NBI;
			break;
		case 1:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->EBI;
			break;
		case 2:
			joininter[i] = Topology->I2;
			joinqueue[i] = Topology->I2->EBI;
			break;
		case 3:
			joininter[i] = Topology->I3;
			joinqueue[i] = Topology->I3->EBI;
			break;
		case 4:
			joininter[i] = Topology->I4;
			joinqueue[i] = Topology->I4->EBI;
			break;
		case 5:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->EBI;
			break;
		case 6:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->SBI;
			break;
		case 7:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->WBI;
			break;
		case 8:
			joininter[i] = Topology->I4;
			joinqueue[i] = Topology->I4->WBI;
			break;
		case 9:
			joininter[i] = Topology->I3;
			joinqueue[i] = Topology->I3->WBI;
			break;
		case 10:
			joininter[i] = Topology->I2;
			joinqueue[i] = Topology->I2->WBI;
			break;
		case 11:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->WBI;
			break;
	}
}

int VIDcounter=0;
srand(time(0));  
    
for (int i=0 ; i<12 ; ++i)
{
	double T=0.0;
	do{
		//getting the random number
		double t = -log(max(rand()/(RAND_MAX*1.0+1.0),.001))/lambda[i];
		printf("i= %d , t= %f , 1/lambda=%f , T=%f\n",i,t,1/lambda[i],T);
		
		T += t;
		//generating a new vehicle
		VehicleClass* vehicle=new VehicleClass(++VIDcounter, i, 6);		
		//scheduling all the vehicles
		sim->Schedule(T, &Intersection::addVehicletoQueue, joininter[i], joinqueue[i], vehicle);
	}while(T<7200.0); //less than 2 hours
}
printf("Total Vehicles scheduled: %d\n",VIDcounter);

}

