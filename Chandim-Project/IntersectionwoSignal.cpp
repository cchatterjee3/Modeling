#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "TrafficLight.h"
#include "IntersectionwoSignal.h"
#include "Simulator.h"
#include "VehicleQueue.h"

extern Simulator* sim ;

IntersectionwithoutSignal::IntersectionwithoutSignal( )
{

}

IntersectionwithoutSignal::IntersectionwithoutSignal(int nID) : Intersection(nID)
{

}

IntersectionwithoutSignal::~IntersectionwithoutSignal(void)
{
	
}

void IntersectionwithoutSignal::VehiclePass(VehicleClass* vehicle, int Turn) //Vehicle passes through intersection
{

	cout << "In NoSignal::VehiclePass with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	// setting queue to busy
	if(Turn==0) //increase busy flag only when the vehicle is going straight.
		vehicle-> getLastQ()-> busy ++;

	//schedule vehicle departure in service time
	sim->Schedule(PassTime, &IntersectionwithoutSignal::VehicleDeparture, this, vehicle);//(debug)
	vehicle->getLastQ()->LastSentCar=sim->getNow(); //set the time that the queue last sent a car

	cout << "--> VehicleDeparture scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+PassTime <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

}

void IntersectionwithoutSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{

	cout << "In NoSignal::VehicleDeparture with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
    cin.get() ;

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

		cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<"SUCCESS!!!!!!"<<endl;
		cin.get();
		
	}
	else
	{
		sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue, NextInter , futureQ , vehicle); //(debug)

		cout << "Will join next intersection, vehicle ID="<< vehicle->getID()<<" , next intersection ID: "<<NextInter->getID()<< 
			" in time "<<sim->getNow()+roadSegTime  <<endl ;
		cin.get() ;
	}

}

void IntersectionwithoutSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	cout << "In WithoutSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cin.get() ;

	joinqueue->push(vehicle);
    //joinqueue->length ++;
	vehicle->setLastQ(joinqueue);
    if(joinqueue->GetLen() == 1) //(debug)
    {
        cout << "joinqueue has only 1 car, evictQ called" << endl ;
        if(joinqueue->LastSentCar==-1) // send the car now
        {
			cout << "did not wait" << endl;
            this->EvictQ(joinqueue);
        }
        else // send the car in the future
		{
			cout << "will wait for for " << max( BurstTime - (sim->getNow() - joinqueue->LastSentCar)  , 0.0 ) << endl;
			sim->Schedule( max( BurstTime - (sim->getNow() - joinqueue->LastSentCar)  , 0.0 ), 
                    &IntersectionwithoutSignal::EvictQ, this, joinqueue ); //(debug)
		}
    }
	else
	{
		cout << "waiting in line" << endl;
	}
}

void IntersectionwithoutSignal::EvictQ(VehicleQueue* joinqueue)
{
    cout << "evictQ called, Qdirection is " << this->getQdirection(joinqueue) << " Q lane is "<< this->getQlane(joinqueue) << endl;
    cin.get();
    
	int Qdirection=getQdirection(joinqueue);
    int Qlane=getQlane(joinqueue);
        
    int QState=QCanGo(Qdirection, Qlane);

	if(QState!=-1)
		printf("Qstate=%d, Inter ID=%d\n",QState,joinqueue->front()->getID());

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
    		sim->Schedule( startToPass, &IntersectionwithoutSignal::VehiclePass, this, joinqueue->front(), Turn);//(debug)
			joinqueue->pop();
        }
        else if( !isfull ) // next queue is not full
        {
    		sim->Schedule( startToPass, &IntersectionwithoutSignal::VehiclePass, this, joinqueue->front(), Turn);//(debug)
			joinqueue->pop();
			//futureQ->length ++ ;
        }
        else // next Q is full, a check will be scheduled for future
        {
    		sim->Schedule( checkQinterval, &IntersectionwithoutSignal::EvictQ, this, joinqueue ); //(debug)
        }
	}
    else if(QState == +1) //Queue is not empty, and the light is green, but intersection IS BUSY
    {   //scheduling a check for future
    	sim->Schedule( checkQinterval, &IntersectionwithoutSignal::EvictQ, this, joinqueue ); //(debug)
    }
    else if(QState == -1) // Q is empty, set the flag to send the first car arriving
    {
        joinqueue->LastSentCar = -1; //ready to send car
    }
}

int IntersectionwithoutSignal::QCanGo (int Qdirection, int lane) //Improved Version
	//checks its signals for a specific Queue
{

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	//+1: The queue is not empty, intersection is BUSY
	//+2: The queue is not empty, the intersection is not busy
	
	int canGo ;
	VehicleQueue* Q = Qu[Qdirection][lane];

	if(Q->empty())
		return -1;
	
	dir dest=this->routingtable[Q->front()->getDestination()];
	int Turn=turn(dest, Qdirection);

    if(Qdirection==0 || Qdirection==2) //major queues
    {
        if(Turn==0)	// moving forward
            canGo=+2;
        else if(lane==0 && Turn==+1) // turning right from right lane
            canGo=+2;
        else if(lane==1 && Turn==-1) // turning left from left lane
        {
            if(!(  (!(Qu[reg(Qdirection+2)][0])->isBusy()) //(debug)
                && (!(Qu[reg(Qdirection+2)][1])->isBusy()) ))
            {
                canGo=1;
            }
            else
                canGo=2;
        }
        else
        {
            printf("error inside QCanGo, unexpected condition.\n");
            exit(1); //exit with error
        }
    }
    else //secondary queues
    {
        if(Turn==0)	// moving forward
        {
            if(!(  (!(Qu[reg(Qdirection+1)][0])->isBusy()) //(debug)
                && (!(Qu[reg(Qdirection+1)][1])->isBusy()) 
                && (!(Qu[reg(Qdirection-1)][0])->isBusy()) 
                && (!(Qu[reg(Qdirection-1)][1])->isBusy()) ))
            {
                canGo=1;
            }
            else
                canGo=2;
        }
        else if(lane==0 && Turn==+1) // turning right from right lane
        {
            if(!(  (!(Qu[reg(Qdirection+1)][0])->isBusy()) )) //(debug)
                canGo=1; //busy
            else
                canGo=2; //free
        }
        else if(lane==1 && Turn==-1) // turning left from left lane
        {
            if(!(  (!(Qu[reg(Qdirection+1)][0])->isBusy()) //(debug)
                && (!(Qu[reg(Qdirection+1)][1])->isBusy()) 
                && (!(Qu[reg(Qdirection-1)][1])->isBusy()) 
                && (!(Qu[reg(Qdirection+2)][0])->isBusy()) 
                && (!(Qu[reg(Qdirection+2)][1])->isBusy()) ))
            {
                canGo=1;
            }
            else
                canGo=2;
        }
        else
        {
            printf("error inside QCanGo, unexpected condition.\n");
            exit(1); //exit with error
        }
    }

	return canGo;

}

