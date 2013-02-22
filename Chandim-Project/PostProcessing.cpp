
#include <math.h>
#include <stdio.h>
#include "PostProcessing.h"
#include "VehicleQueue.h"

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define LARGE_FLOAT 100000.0

void PostProcStats(VehicleQueue* ExQ, double TimeInterval, int buckets,int source, int dest, ofstream &fh)
{
	int* Hist;
	Hist = new int[buckets];

	//initialzing the array to zero
	for (int i = 0; i < buckets; ++i)
	{
		Hist[i]=0;
	}


	double BucketSize= TimeInterval/buckets;
	double TMin =LARGE_FLOAT;
	double TMax =0;
	double Sum=0;		//sum of average time
	double SSum=0;		//sum of square of avg time
	int NumVehicle=0;
	VehicleQueue* EQ = new VehicleQueue(ExQ);
	
    while(!EQ->empty())
	{
		VehicleClass* V1 = EQ->front();
		EQ->pop();
		if (V1->getSource()==source && V1->getDestination()==dest && V1->startTime>900)
		{
			NumVehicle++;
			double Temp;
			Temp = V1->EndTime()-V1->StartTime();
			fh << Temp  <<  ", ";
            if (Temp<0)
			{
				printf("Possibly some error/bug occured with Simulation\n");
			}
			TMin = MIN(TMin,Temp);
			TMax = MAX(TMax,Temp);
			Sum +=  Temp;
			SSum += Temp*Temp;
			if (Temp/BucketSize <buckets)
			{
				Hist[(int) (Temp/BucketSize)] +=1; 
			}
			
		}
	}

	double Avg = Sum/NumVehicle;
	double SAvg = SSum/NumVehicle;
	double StdDev = sqrt(SAvg-Avg*Avg);

	//Now printing stats

	/*
    printf("Averge time taken for crossing %d to %d is %lf\n",source,dest,Avg);
	printf("Maximum time %lf Minimum time %lf Std Dev %lf seconds\n",TMax,TMin,StdDev );
    */
    
    /*fh<<"Average time taken for crossing from "<<source<<" to "<<dest<<" is "<<Avg<<endl;
    fh<<"Maximum time: "<<TMax<<endl;
    fh<<"Minimum time: "<<TMin<<endl;
    fh<<"Standard Deviation: "<<StdDev<<endl;
    
	//Printing Histogram
	//printf("Histogram is as follows \n");
	fh<<"Histogram is as follows :"<<endl;
	for (int i = 0; i < buckets; ++i)
	{
		//printf("%d, ",Hist[i] );
		fh<<Hist[i]<<", ";
	}
    */
    fh<<endl;
    delete[] Hist;
    delete EQ;
	//printf("\n");



}
