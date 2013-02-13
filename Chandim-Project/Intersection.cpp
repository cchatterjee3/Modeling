#include <iostream>

#include "Intersection.h"
#include "CommonDefs.h"
#include "VehicleQueue.h"
#include <memory.h>

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
		EBI1=new VehicleQueue;
		WBI1=new VehicleQueue;
		EBI2=new VehicleQueue;
		WBI2=new VehicleQueue;
		NBI1=new VehicleQueue;
		SBI1=new VehicleQueue;
		NBI2=new VehicleQueue;
		SBI2=new VehicleQueue;
		
		NBIlength = 25;
		SBIlength = 25;
		
		
		//initialize routing table
		
		switch (ID){
			
			case 1: //(debug)
			{
				dir routingtables1[12]={S,W,N,N,N,N,N,N,N,N,N,E};
				memcpy(routingtable, routingtables1, 12*sizeof(dir));
				break;
            }
			case 2:
            {
                dir routingtables2[12]={S,S,W,N,N,N,N,N,N,N,E,S};
                memcpy(routingtable, routingtables2, 12*sizeof(dir));
				break; 
            }
			case 3:
            {
                 dir routingtables3[12]={S,S,S,W,N,N,N,N,N,E,S,S};
                 memcpy(routingtable, routingtables3, 12*sizeof(dir));
				 break;
            }
	        case 4:
            {
                 dir routingtables4[12]={S,S,S,S,W,N,N,N,E,S,S,S};
                 memcpy(routingtable, routingtables4, 12*sizeof(dir));
				 break;
            }
		    case 5:
            {
                 dir routingtables5[12]={S,S,S,S,S,W,N,E,S,S,S,S};
                 memcpy(routingtable, routingtables5, 12*sizeof(dir));
				 break;
            }
		}
		
		
		
		if(haveSignal)
			cout << "Intersection ID=" << ID << " created with    signal"<<endl;
		else
			cout << "Intersection ID=" << ID << " created without signal"<<endl;
		
};

Intersection::Intersection(){};
Intersection::~Intersection(){};

