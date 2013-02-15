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

