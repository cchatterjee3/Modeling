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
		Qu[0][0]=NBI1; Qu[1][0]=EBI1; Qu[2][0]=SBI1; Qu[3][0]=WBI1; 
		Qu[0][1]=NBI2; Qu[1][1]=EBI2; Qu[2][1]=SBI2; Qu[3][1]=WBI2; 
        
};

int Intersection::getQdirection(VehicleQueue* Q)//, Intersection* Inter)
{
    if(Q==this->NBI1 || Q==this->NBI2)
        return 0;
    else if(Q==this->EBI1 || Q==this->EBI2)
        return 1;
    else if(Q==this->SBI1 || Q==this->SBI2)
        return 2;
    else if(Q==this->WBI1 || Q==this->WBI2)
        return 3;
    else    //does not exist
        return -1;
}

int Intersection::getQlane(VehicleQueue* Q)//, Intersection* Inter)
{
    if(Q==this->NBI1 || Q==this->EBI1 || Q==this->SBI1 || Q==this->WBI1)
        return 0;
    else if(Q==this->NBI2 || Q==this->EBI2 || Q==this->SBI2 || Q==this->WBI2)
        return 1;
    else
        return -1;
}

VehicleQueue* Intersection::NextQ(VehicleQueue* currentQ, VehicleClass* vehicle)
{ 
	// this function returns the queue pointer to this vehicle's next q(the one in the next intersection)
	// NULL means the vehicle will be exiting the system
	int curQDir=Intersection::getQdirection(currentQ);	//current Q ID
	dir curdir=this->routingtable[vehicle->getDestination()]; //current direction from routing table
	int futureQDir=curQDir+turn(curdir,curQDir); //future Q ID
	if( futureQDir==1 || futureQDir==3 || (ID==5 && futureQDir==0 ) || (ID==1 && futureQDir==2 ) )
		return NULL; //the vehicle will not have a next queue under these conditions

	Intersection * NextInter;
	if( futureQDir==0)
		NextInter=this->NInter;
	else
		NextInter=this->SInter;
	dir futuredir = NextInter->routingtable[vehicle->getDestination()];
	int futureTurn=turn(futuredir,futureQDir);
	if(futureTurn == -1)//turning right
		int futureLane=0;
	else if(futureTurn == +1)//turning left
		int futureLane=1;
	else if(futureTurn == 0)//going forward
	{
		if(NextInter->Qu[futureQDir][0]->GetLen() > Qu[futureQDir][1]->GetLen())
			return Qu[futureQDir][1];
		else
			return Qu[futureQDir][0];
	}



}

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

