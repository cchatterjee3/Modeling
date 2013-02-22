#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "Intersection.h"
#include "CommonDefs.h"
#include "Simulator.h"
#include "VehicleQueue.h"
#include <memory.h>

#ifdef test
    #include "testing/test1.h"
#endif

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
        /*
		if(haveSignal)
			cout << "Intersection ID=" << ID << " created with    signal"<<endl;
		else
			cout << "Intersection ID=" << ID << " created without signal"<<endl;
        */
		//setting up array of Queues:
		Qu[0][0]=NBI1; Qu[1][0]=EBI1; Qu[2][0]=SBI1; Qu[3][0]=WBI1; 
		Qu[0][1]=NBI2; Qu[1][1]=EBI2; Qu[2][1]=SBI2; Qu[3][1]=WBI2; 
        
};
Intersection::Intersection(){};
Intersection::~Intersection(){};


void Intersection::VehiclePass(VehicleClass* vehicle, int Turn) //Vehicle passes through intersection
{
#ifdef test
    eventDsc E1;
    E1.type= PSS;
    E1.InterID=ID;
    E1.QDir=0;
    E1.QLane=0;
    E1.timetag=sim->getNow();
    vehicle->EventList.push_back(E1);
#endif
	//cout << "In Intersection::VehiclePass with vehicle ID="<< vehicle->getID()<< " , Intersection:"<< ID << ", Now="<<sim->getNow() <<endl;
	//cin.get() ;
	
	// setting queue to busy
	if(Turn==0) //increase busy flag only when the vehicle is going straight.
		vehicle-> getLastQ() ->busy ++;
	//vehicle->getLastQ()->length -- ; //decrease length of last queue

	//schedule vehicle deprature in service time
	sim->Schedule(PassTime, &Intersection::VehicleDeparture, this, vehicle);//(debug)

	//cout << "--> VehicleDeparture scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+PassTime <<endl;
	//cin.get() ;

#ifdef test
    eventDsc E2;
    E2.type= DPC;
    E2.InterID=ID;
    E2.QDir=0;
    E2.QLane=0;
    E2.timetag=sim->getNow();
    vehicle->EventList.push_back(E2);
#endif
    //send one more car
    if(vehicle->getLastQ()!=NULL)
    {
        if(vehicle->out_of_line == false)
        {
            EvictQ(vehicle->getLastQ());
        }
        else
        {
            vehicle->out_of_line = false;
        }
    }
}

void Intersection::VehicleDeparture (VehicleClass* vehicle) //Depart
{

	//cout << "In Intersection::VehicleDeparture with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
    //cin.get() ;

#ifdef test
    eventDsc E1;
    E1.type= DEP;
    E1.InterID=ID;
    E1.QDir=0;
    E1.QLane=0;
    E1.timetag=sim->getNow();
    vehicle->EventList.push_back(E1);
#endif

	VehicleQueue * LastQ     = vehicle->getLastQ();

	Intersection * NextInter = NULL;
    VehicleQueue * futureQ   = NULL;
	bool isfull=false;
    int Turn;
	
	// getting info about the next Queue and next intersection
	NextQInfo(LastQ, vehicle, NextInter, futureQ, isfull, Turn);
	
	//freeing intersection
	if(Turn==0)
        LastQ->busy --;

	if( futureQ == NULL )
	{
		//the vehicle is exiting the system
		vehicle->setEndTime(sim->getNow());
		ExitQ->push(vehicle);
		//printf("Car ID=%d Exited the system, inter: %d, ExitQ size:%d, at time: %f \n", vehicle->getID(), ID,ExitQ->GetLen(), sim->getNow());

#ifdef test
    eventDsc E2;
    E2.type= RDT;
    E2.InterID=ID;
    E2.QDir=0;
    E2.QLane=0;
    E2.timetag=sim->getNow();
    vehicle->EventList.push_back(E2);
#endif

    
		//cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<" SUCCESS!!!!!!"<<endl;
		//cin.get();
		
	}
	else
	{
		sim->Schedule(roadSegTime - ((double)(futureQ->GetLen()))/((double)(futureQ->GetMaxLen()) * roadSegTime), &Intersection::addVehicletoQueue, NextInter , futureQ , vehicle); //(debug)
		//sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue, NextInter , futureQ , vehicle); //(debug)

#ifdef test
    eventDsc E3;
    E3.type= JQC;
    E3.InterID=ID;
    if(futureQ!=NULL)
        E3.QDir=getQdirection(NextInter, futureQ);
    if(futureQ!=NULL)
        E3.QLane=getQlane( NextInter, futureQ);
    E3.timetag=sim->getNow();
    vehicle->EventList.push_back(E3);
#endif

    //cout << "Will join next intersection, vehicle ID="<< vehicle->getID()<<" , next intersection ID: "<<NextInter->getID()<< 
	//		" in time "<<sim->getNow()+roadSegTime  <<endl ;
		//cin.get() ;
	}

}

void Intersection::EvictQ(VehicleQueue* joinqueue)
{
//	cout << "evictQ called, Qdirection is " << getQdirection(this, joinqueue) << " Q lane is "<< getQlane(this, joinqueue) << 
//					" Inter ID=" << ID << " time=" << sim->getNow() << endl;
    //cin.get();
    
	int Qdirection=getQdirection(this, joinqueue);
    int Qlane=getQlane(this, joinqueue);
        
    int QState=QCanGo(Qdirection, Qlane);

/*	printf("Qstate=%d\n",QState);
	if(QState!=-1)
		printf("Qstate=%d, Inter ID=%d\n",QState,joinqueue->front()->getID());
*/
	if (QState==2) //Queue is not empty, and the light is green, intersection not busy
	{
        Intersection * NextInter = NULL;
        VehicleQueue * futureQ = NULL;
        bool isfull=false;
        int Turn;
		// getting info about the next Queue and next intersection
        NextQInfo(joinqueue, joinqueue->front(), NextInter, futureQ, isfull, Turn);

        if( futureQ==NULL ) //There is no next Queue
        {

#ifdef test
    eventDsc E1;
    E1.type = PSC;
    E1.InterID =ID;
    E1.QDir = getQdirection(this, joinqueue);
    E1.QLane = getQlane(this, joinqueue);
    E1.timetag = sim->getNow();
    joinqueue->front()->EventList .push_back(E1);
#endif

            sim->Schedule( startToPass, &Intersection::VehiclePass, this, joinqueue->front(), Turn);//(debug)
			if(joinqueue->front()->getLastQ() != NULL)
				joinqueue->front()->getLastQ()->LastSentCar=sim->getNow(); //set the time that the queue last sent a car
			joinqueue->pop();
        }
        else if( !isfull ) // next queue is not full
        {

#ifdef test
    eventDsc E2;
    E2.type = PSC;
    E2.InterID =ID;
    E2.QDir = getQdirection(this, joinqueue);
    E2.QLane = getQlane(this, joinqueue);
    E2.timetag = sim->getNow();
    joinqueue->front()->EventList.push_back(E2);
#endif

            sim->Schedule( startToPass, &Intersection::VehiclePass, this, joinqueue->front(), Turn);//(debug)
			if(joinqueue->front()->getLastQ() != NULL)
				joinqueue->front()->getLastQ()->LastSentCar=sim->getNow(); //set the time that the queue last sent a car
			joinqueue->pop();
			//futureQ->length ++ ;
        }
        else // next Q is full, a check will be scheduled for future
        {
#ifdef test
    eventDsc E3;
    E3.type = WTQ;
    E3.InterID =ID;
    E3.QDir = getQdirection(this, joinqueue);
    E3.QLane = getQlane(this, joinqueue);
    E3.timetag = sim->getNow();
    joinqueue->front()->EventList.push_back(E3);
#endif
            
    		sim->Schedule( checkQinterval, &Intersection::EvictQ, this, joinqueue ); //(debug)
        }
	}
    else if(QState == +1) //Queue is not empty, and the light is green, but intersection IS BUSY
    {   //scheduling a check for future

#ifdef test
    eventDsc E4;
    E4.type = WTB;
    E4.InterID =ID;
    E4.QDir = getQdirection(this, joinqueue);
    E4.QLane = getQlane(this, joinqueue);
    E4.timetag = sim->getNow();
    joinqueue->front()->EventList.push_back(E4);
#endif
        
    	sim->Schedule( checkQinterval, &Intersection::EvictQ, this, joinqueue ); //(debug)
    }
    else if(QState == -1) // Q is empty, set the flag to send the first car arriving
    {
        joinqueue->LastSentCar = -1; //ready to send car
    }
    else if(QState == 0)
    {
        
#ifdef test
    eventDsc E5;
    E5.type = WTL;
    E5.InterID =ID;
    E5.QDir = getQdirection(this, joinqueue);
    E5.QLane = getQlane(this, joinqueue);
    E5.timetag = sim->getNow();
    joinqueue->front()->EventList.push_back(E5);
#endif
        
    }
    
}


int  Intersection::getQdirection(Intersection * inter, VehicleQueue* Q)//, Intersection* Inter)
{
    if(Q==inter->NBI1 || Q==inter->NBI2)
        return 0;
    else if(Q==inter->EBI1 || Q==inter->EBI2)
        return 1;
    else if(Q==inter->SBI1 || Q==inter->SBI2)
        return 2;
    else if(Q==inter->WBI1 || Q==inter->WBI2)
        return 3;
    else    //does not exist
        return -1;
}

int  Intersection::getQlane(Intersection * inter, VehicleQueue* Q)//, Intersection* Inter)
{
    if(Q==inter->NBI1 || Q==inter->EBI1 || Q==inter->SBI1 || Q==inter->WBI1)
        return 0;
    else if(Q==inter->NBI2 || Q==inter->EBI2 || Q==inter->SBI2 || Q==inter->WBI2)
        return 1;
    else
        return -1;
}

void Intersection::NextQInfo(VehicleQueue* currentQ, VehicleClass* vehicle, Intersection *  & NextInter, VehicleQueue * & FutureQ, 
	bool & isfull, int & Turn)
{ 
	// this function returns the queue pointer to this vehicle's next q(the one in the next intersection)
	// NULL means the vehicle will be exiting the system
	int curQDir=Intersection::getQdirection(this, currentQ);	//current Q ID
	dir curdir=this->routingtable[vehicle->getDestination()]; //current direction from routing table
    
    Turn=turn(curdir,curQDir);
	
    int futureQDir=reg(curQDir+Turn); //future Q ID
	if( futureQDir==1 || futureQDir==3 || (ID==5 && futureQDir==0 ) || (ID==1 && futureQDir==2 ) )
	{
		FutureQ = NULL; //the vehicle will not have a next queue under these conditions
		return;
	}
	if( futureQDir==0)
		NextInter=this->NInter;
	else
		NextInter=this->SInter;

	dir futuredir = NextInter->routingtable[vehicle->getDestination()];
	int futureTurn=turn(futuredir,futureQDir);
	
    int Lane0Len = NextInter->Qu[futureQDir][0]->GetLen();
    int Lane1Len = NextInter->Qu[futureQDir][1]->GetLen();

    if(Lane0Len + Lane1Len  >=  Qu[futureQDir][0]->GetMaxLen() + Qu[futureQDir][1]->GetMaxLen() )
        isfull=true;
    else
        isfull=false;
    
    int futureLane;
    
	if(futureTurn == 1)//turning right
		futureLane=0;
	else if(futureTurn == -1)//turning left
		futureLane=1;
	else if(futureTurn == 0)//going forward
	{
		if(Lane0Len > Lane1Len)
			futureLane=1;
		else
    		futureLane=0;
	}
    else
    {
        printf("there is an error in NextQInfo!\n");
        futureLane=-1;
    }
    
    FutureQ = NextInter->Qu[futureQDir][futureLane];

}

int  reg(int i)
{
	if(i>3)
		return i-4;
	else if (i<0)
		return i+4;
	else
		return i;
}

int  turn(dir globalDir, int QDirection)
{
	//returns: 
	//  0 : if vehicle must NOT turn
	//  1 : if vehicle must turn right
	// -1 : if vehicle must turn left
	//-100: error

	switch (QDirection)
	{
	case 0: //NorthBound
		switch(globalDir)
		{
		case E:
			return  1; //turn right
			break;
		case N:
			return  0; //no turn, go forward
			break;
		case W:
			return -1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 1: //EastBound
		switch(globalDir)
		{
		case S:
			return  1; //turn right
			break;
		case E:
			return  0; //no turn, go forward
			break;
		case N:
			return -1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 2: //SouthBound
		switch(globalDir)
		{
		case W:
			return  1; //turn right
			break;
		case S:
			return  0; //no turn, go forward
			break;
		case E:
			return -1; //turn left
			break;
		default:
			return -100;
		}
		break;

	case 3: //WestBound
		switch(globalDir)
		{
		case N:
			return  1; //turn right
			break;
		case W:
			return  0; //no turn, go forward
			break;
		case S:
			return -1; //turn left
			break;
		default:
			return -100;
		}
		break;
	
	default:
		return -100;
	}
}
