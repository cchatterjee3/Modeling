
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Simulator.h"
#include "Topology.h"

#include "CommonDefs.h"

/*
#ifdef _WIN32
	#include <windows.h>
	#include <time.h>
#else
	#include <sys/time.h> 
#endif
*/

#include "RandomNum.h"


extern Simulator* sim ;

RandomNumGen Ran(0);


void scheduleVehicles(	_Topology* Topology, double maxTime)
{

double lambda[12]={0.143369176, 0.051930458, 0.054483541, 0.012919897, 
				   0.008486563, 0.118992606, 0.280186791, 0.028714107, 
				   0.015353122, 0.0000001  , 0.009876543, 0.035778175};

printf("///////////////////////////////\n");
printf("/// generating all arrivals ///\n");
printf("///////////////////////////////\n");

VehicleQueue*	joinqueue  [12];
Intersection*	joininter  [12];
int				joinQdir  [12];

double desProb[144]={
0.000,	0.225,	0.248,	0.287,	0.287,	0.349,	0.868,	0.884,	0.891,	0.907,	0.907,	1.000,
0.489,	0.489,	0.532,	0.532,	0.532,	0.574,	0.936,	0.957,	0.957,	0.957,	1.000,	1.000,
0.265,	0.429,	0.429,	0.429,	0.429,	0.449,	0.469,	0.469,	0.469,	0.469,	0.551,	1.000,
0.200,	0.300,	0.400,	0.400,	0.400,	0.400,	0.600,	0.600,	0.600,	0.600,	0.700,	1.000,
0.000,	0.429,	0.429,	0.571,	0.571,	0.571,	0.857,	0.857,	0.857,	1.000,	1.000,	1.000,
0.269,	0.356,	0.385,	0.413,	0.413,	0.413,	0.856,	0.865,	0.923,	0.942,	0.962,	1.000,
0.289,	0.332,	0.344,	0.356,	0.356,	0.526,	0.526,	0.810,	0.905,	0.929,	0.933,	1.000,
0.042,	0.042,	0.042,	0.042,	0.042,	0.042,	1.000,	1.000,	1.000,	1.000,	1.000,	1.000,
0.077,	0.077,	0.077,	0.154,	0.154,	0.308,	1.000,	1.000,	1.000,	1.000,	1.000,	1.000,
0.500,	0.500,	0.500,	0.500,	0.500,	0.500,	1.000,	1.000,	1.000,	1.000,	1.000,	1.000,
0.000,	0.111,	0.889,	0.889,	0.889,	0.889,	1.000,	1.000,	1.000,	1.000,	1.000,	1.000,
0.242,	0.273,	0.303,	0.333,	0.333,	0.424,	0.970,	0.970,	0.970,	0.970,	1.000,	1.000
};

int interID;
int Qdir;

for (int i=0 ; i<12 ; ++i)
{

	switch (i)
	{
		case 0:
			interID=1;		Qdir=0;
			break;
		case 1:
			interID=1;		Qdir=1;
			break;
		case 2:
			interID=2;		Qdir=1;
			break;
		case 3:
			interID=3;		Qdir=1;
			break;
		case 4:
			interID=4;		Qdir=1;
			break;
		case 5:
			interID=5;		Qdir=1;
			break;
		case 6:
			interID=5;		Qdir=2;
			break;
		case 7:
			interID=5;		Qdir=3;
			break;
		case 8:
			interID=4;		Qdir=3;
			break;
		case 9:
			interID=3;		Qdir=3;
			break;
		case 10:
			interID=2;		Qdir=3;
			break;
		case 11:
			interID=1;		Qdir=3;
			break;
	}

	joininter[i] = Topology->In[interID-1];
	joinQdir[i] = Qdir;
	//turn(joininter[i]->routingtable[1];
}


int VIDcounter=0;
//srand(time(0));  

int fdest; //final destination
int Qlane;

for (int i=0 ; i<12 ; i++)
{
	double T=0.0;
	do{
		//getting the random number
//		double t = -log(max(rand()/(RAND_MAX*1.0+1.0),.001))/lambda[i];

        double t;
        if(lambda[i]>.00001) // check if lambda=0
            t = -log(Ran.Next())/lambda[i];
        else
            t = maxTime - T;

		//getting the random destination:
		double RandDest = Ran.Next(); //generates a random number in (0,1)
		bool foundDest=false;
		for (int j=0 ; j<12 ; j++)
		{
			if (RandDest<=desProb[i*12+j])
			{
				fdest=j;
                if(fdest != i)
                {
                    foundDest=true;
                    break;
                }
                else
        			printf("error: no destination found!\n");
                    
			}
		}
		if(foundDest==false)
		{
			printf("error: no destination found!\n");
		}

		T += t;
        int Turn0 = turn((dir) joininter[i]->routingtable[fdest], joinQdir[i]);
        if(Turn0 == 1 )
            Qlane=0;
        else if(Turn0 == -1)
            Qlane=1;
        else if (Turn0 == 0)
        {
            Qlane=0; //floor(Ran.Next()*2); //choosing random lane between 0 and 1
            if((Qlane != 1) && (Qlane !=0) )
                printf("error error in Vehicle scheduler 1 Qlane=%d \n", Qlane);
        }
        else
            printf("error error in Vehicle scheduler 2 \n");

		if(T<maxTime)
		{
            //generating a new vehicle
			VehicleClass* vehicle=new VehicleClass(++VIDcounter, i, fdest, T);		
			//scheduling all the vehicles
			sim->Schedule(T, &Intersection::addVehicletoQueue, joininter[i], 
                    joininter[i]->Qu[joinQdir[i]][Qlane], vehicle);
		}
	}while(T<maxTime); //less than 2 hours
}

printf("Total Vehicles scheduled: %d\n",VIDcounter);

}
