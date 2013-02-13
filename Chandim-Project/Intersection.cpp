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

		//setting up array of Queues:
		/*
			VehicleQueue* EBI1;
	VehicleQueue* EBI2;
	VehicleQueue* WBI1;
	VehicleQueue* WBI2;
	VehicleQueue* NBI1;
	VehicleQueue* NBI2;
	VehicleQueue* SBI1;
	VehicleQueue* SBI2;

	VehicleQueue* Q[4][2];

	*/
		Qu[0][0]=NBI1; Qu[1][0]=EBI1; Qu[2][0]=SBI1; Qu[3][0]=WBI1; 
		Qu[0][1]=NBI2; Qu[1][1]=EBI2; Qu[2][1]=SBI2; Qu[3][1]=WBI2; 

};

Intersection::Intersection(){};
Intersection::~Intersection(){};

int reg(int i)
{
	if(i>3)
		return i-4;
	else if (i<0)
		return i+4;
	else
		return -1;
}

int turn(dir globalDir, int QDirection)
{
	//returns: 
	//  0 : if vehicle must NOT turn
	// -1 : if vehicle must turn right
	//  1 : if vehicle must turn left
	//-100: error

	switch (QDirection)
	{
	case 0: //NorthBound
		switch(globalDir)
		{
		case E:
			return -1; //turn right
			break;
		case N:
			return  0; //no turn, go forward
			break;
		case W:
			return +1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 1: //EastBound
		switch(globalDir)
		{
		case S:
			return -1; //turn right
			break;
		case E:
			return  0; //no turn, go forward
			break;
		case N:
			return +1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 2: //SouthBound
		switch(globalDir)
		{
		case W:
			return -1; //turn right
			break;
		case S:
			return  0; //no turn, go forward
			break;
		case E:
			return +1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 3: //WestBound
		switch(globalDir)
		{
		case N:
			return -1; //turn right
			break;
		case W:
			return  0; //no turn, go forward
			break;
		case S:
			return +1; //turn left
			break;
		default:
			return -100;
		}
		break;
	
	default:
		return -100;
	}
}
