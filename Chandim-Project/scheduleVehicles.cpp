
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Simulator.h"
#include "Topology.h"
#include "RandomNum.h"

#ifdef __WIN32__
        #include <time.h>
        #include <windows.h>
#endif


extern Simulator* sim ;

RandomNumGen Ran(0);


void scheduleVehicles(	_Topology* Topology, double maxTime)
{

double lambda[12]={0.1597,0.0369,0.0099,0.0163,0.0154,0.0287,0.2913,
				   0.1213,0.0205,0.0158,0.0545,0.0655};


printf("///////////////////////////////\n");
printf("/// generating all arrivals ///\n");
printf("///////////////////////////////\n");

VehicleQueue* joinqueue[12];
Intersection* joininter[12];

double desProb[144]={
0.000,0.098,0.098,0.098,0.106,0.122,0.667,0.732,0.732,0.772,0.797,1.000,
0.235,0.235,0.265,0.265,0.265,0.265,0.794,0.882,0.912,0.941,0.971,1.000,
0.000,0.000,0.000,0.000,0.000,0.000,0.111,0.111,0.111,0.111,0.889,1.000,
0.000,0.000,0.000,0.000,0.000,0.000,0.111,0.111,0.111,0.111,0.889,1.000,
0.077,0.077,0.077,0.077,0.077,0.077,0.769,0.923,0.923,1.000,1.000,1.000,
0.042,0.042,0.042,0.042,0.042,0.042,1.000,1.000,1.000,1.000,1.000,1.000,
0.296,0.364,0.368,0.368,0.466,0.757,0.757,0.931,0.931,0.943,0.955,1.000,
0.000,0.000,0.000,0.000,0.087,0.101,0.768,0.768,0.783,0.826,0.870,1.000,
0.267,0.333,0.333,0.333,0.333,0.333,0.467,0.733,0.733,0.867,0.867,1.000,
0.182,0.455,0.545,0.545,0.545,0.545,0.727,0.727,0.818,0.818,0.909,1.000,
0.265,0.714,0.796,0.796,0.796,0.796,0.816,0.837,0.837,0.837,0.837,1.000,
0.489,0.489,0.532,0.532,0.532,0.553,0.915,0.957,0.957,0.957,1.000,1.000
};


for (int i=0 ; i<12 ; ++i)
{
	switch (i)
	{
		case 0:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->NBI1; //(NBI->NBI1)
			break;
		case 1:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->EBI1; //(NBI->NBI1)
			break;
		case 2:
			joininter[i] = Topology->I2;
			joinqueue[i] = Topology->I2->EBI1; //(NBI->NBI1)
			break;
		case 3:
			joininter[i] = Topology->I3;
			joinqueue[i] = Topology->I3->EBI1; //(NBI->NBI1)
			break;
		case 4:
			joininter[i] = Topology->I4;
			joinqueue[i] = Topology->I4->EBI1; //(NBI->NBI1)
			break;
		case 5:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->EBI1; //(NBI->NBI1)
			break;
		case 6:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->SBI1; //(NBI->NBI1)
			break;
		case 7:
			joininter[i] = Topology->I5;
			joinqueue[i] = Topology->I5->WBI1; //(NBI->NBI1)
			break;
		case 8:
			joininter[i] = Topology->I4;
			joinqueue[i] = Topology->I4->WBI1; //(NBI->NBI1)
			break;
		case 9:
			joininter[i] = Topology->I3;
			joinqueue[i] = Topology->I3->WBI1; //(NBI->NBI1)
			break;
		case 10:
			joininter[i] = Topology->I2;
			joinqueue[i] = Topology->I2->WBI1; //(NBI->NBI1)
			break;
		case 11:
			joininter[i] = Topology->I1;
			joinqueue[i] = Topology->I1->WBI1; //(NBI->NBI1)
			break;
	}
}

int VIDcounter=0;
//srand(time(0));  

int fdest; //final destination

for (int i=0 ; i<12 ; i++)
{
	double T=0.0;
	do{
		//getting the random number
//		double t = -log(max(rand()/(RAND_MAX*1.0+1.0),.001))/lambda[i];
		double t = -log(Ran.Next())/lambda[i];
		//getting the random destination:
		double RandDest = Ran.Next(); //generates a random number in (0,1)
		bool foundDest=false;
		for (int j=0 ; j<12 ; j++)
		{
/*			if(i==6)
			{
				printf("i= %d , j= %d , destprob=%f, fdest=%d , RandDest=%f \n",i,j,desProb[i*12+j],fdest,RandDest);
			}
*/
			if (RandDest<=desProb[i*12+j])
			{
				fdest=j;
				foundDest=true;
				break;
			}
		}
		if(foundDest==false)
		{
			printf("error: no destination found!\n");
		}
		T += t;

/*		if(i==6)
		{

		printf("i= %d , t= %f , 1/lambda=%f , T=%f\n , fdest=%d , RandDest=%f \n",i,t,1/lambda[i],T,fdest,RandDest);
		system ("pause");
		} */


		
		//generating a new vehicle
		VehicleClass* vehicle=new VehicleClass(++VIDcounter, i, fdest);		
		//scheduling all the vehicles
		sim->Schedule(T, &Intersection::addVehicletoQueue, joininter[i], joinqueue[i], vehicle);
	}while(T<maxTime); //less than 2 hours
}

printf("Total Vehicles scheduled: %d\n",VIDcounter);

}
