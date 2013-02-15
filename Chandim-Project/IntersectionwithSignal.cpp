#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "TrafficLight.h"
#include "IntersectionwithSignal.h"
#include "CommonDefs.h"
#include "VehicleQueue.h"
#include "Simulator.h"

extern Simulator* sim ;

IntersectionwithSignal::IntersectionwithSignal(){

};

IntersectionwithSignal::IntersectionwithSignal(int nID) : Intersection(nID)
{

	//setting each traffic light's type
	int EBtype, WBtype, NBtype, SBtype;
    
	if( ID ==1 || ID ==5 )
	{
		EBtype=1; WBtype=1; NBtype=1; SBtype=1;
		if( ID==5)
		{
			WBtype=0;
		}
	}
	else
	{
		EBtype=0; WBtype=0; NBtype=0; SBtype=0;
	}
	
	if (ID==1) 
    {
      //Traffic light on Peachtree and 10th
	  EB=new TrafficLight(1, EBtype, (state)5, 8, 1.8, 1.8, 30, 3.8, 55, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 5, 3.6, 4.2, 28, 3.8, 55, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
    }
    if (ID==2)
    {
      //Traffic light on Peachtree and 11th
      EB=new TrafficLight(1, EBtype, (state)5, 0, 0, 0, 20.2, 3.6, 76.1, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 20.3, 3.6, 76.2, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 0, 0, 0, 41.5, 3.2, 55.4, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 0, 0, 0, 41.5, 3.2, 55.4, this);            
    }
    if (ID==3)
    {
      //Traffic light on Peachtree and 12th
      EB=new TrafficLight(1, EBtype, (state)5, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 0, 0, 0, 60.9, 3.2, 35.7, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 0, 0, 0, 61.4, 3.2, 35.7, this);             
    }
    if (ID==5)
    {
      //Traffic light on Peachtree and 14th
      EB=new TrafficLight(1, EBtype, (state)5, 9.8, 3.6, 87, 36.9, 3.7, 60.2, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 22.4, 3.7, 74, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 8.8, 3.6, 3.6, 34.6, 3.2, 46.1, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 11.6, 3.6, 0.5, 36.6, 3.2, 45.3, this);          
    }

	//set traffic lights array
	TLight[0]=NB; TLight[1]=EB; TLight[2]=SB; TLight[3]=WB;

}

IntersectionwithSignal::~IntersectionwithSignal(void)
{
                                                     
}

void IntersectionwithSignal::changeSignalTrigger( int LightID) //checks its own signals 
{
	//When a light changes, triggers the relevant Queues to send vehicles out.

	if (TLight[LightID]->getState() == GTR)
	{
        //cout << "state:GTR , ID=" << this->getID() << " light: " << LightID << endl;

		this->EvictQ( Qu[LightID][0] );
		this->EvictQ( Qu[LightID][1] );
	}
	else if (TLight[LightID]->getState() == GLT)
	{
        //cout << "state:GLT , ID=" << this->getID() << " light: " << LightID << endl;
		this->EvictQ( Qu[LightID][1]);
	}
    else
    {
        //cout << "nobody called - ID=" << this->getID() << " light: " << LightID << endl;
    }
}

void IntersectionwithSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	cout << "In WithSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
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
                    &IntersectionwithSignal::EvictQ, this, joinqueue ); //(debug)
		}
    }
	else
	{
		cout << "waiting in line" << endl;
	}

}

int IntersectionwithSignal::QCanGo (int Qdirection, int lane) //Improved Version
	//checks its signals for a specific Queue
{

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the direction of the first member of Queue
	//+1: The queue is not empty, the traffic light is OK, But the intersection is busy
	//+2: The queue is not empty, the traffic light is OK, and the intersection is not busy
	
	int canGo;
	VehicleQueue* Q = Qu[Qdirection][lane];

	if(Q->empty())
		return -1;
	
	dir dest=this->routingtable[Q->front()->getDestination()];
	int Turn=turn(dest, Qdirection);

	if(Turn==0)	// moving forward
    {
        if(TLight[Qdirection]->getState()==GTR)
        {
            canGo=+2; // light is OK, But:
			/*
			if(!(  (!(Qu[reg(Qdirection+1)][0])->isBusy()) //(debug)
                && (!(Qu[reg(Qdirection+1)][1])->isBusy())
                && (!(Qu[reg(Qdirection-1)][0])->isBusy())
                && (!(Qu[reg(Qdirection-1)][1])->isBusy()) )  )
                canGo=+1; //light is OK,but intersection is busy
				*/
        }
        else
            canGo= 0; //light is NOT OK
    }
	else if(lane==0 && Turn==+1) // turning right from right lane
    {
        if(  !(Qu[reg(Qdirection+1)][0])->isBusy()  )
            canGo=+2; // OK, vehicle can pass
        else
            canGo=+1; // intersection is busy
    }
	else if(lane==1 && Turn==-1) // turning left from left lane
	{
		if(TLight[Qdirection]->getType()==1) // 6states
		{
			if(TLight[Qdirection]->getState()==GLT)
				canGo=+2;
			else
				canGo= 0;
		}
		else //3 states
		{
			if(TLight[Qdirection]->getState()==GTR)
			{
            canGo=+2; // light is OK, But:
			if(! (!(Qu[reg(Qdirection+1)][0])->isBusy() 
				&& (!(Qu[reg(Qdirection+1)][1])->isBusy()) 
				&& (!(Qu[reg(Qdirection-1)][1])->isBusy()) 
				&& (!(Qu[reg(Qdirection+2)][0])->isBusy()) 
				&& (!(Qu[reg(Qdirection+2)][1])->isBusy())) )
                canGo=+1; //light is OK,but intersection is busy
			}
			else
	            canGo= 0; //light is NOT OK
		}
	}
	else //no other case is acceptable
    {
		printf("error inside QCanGo, unexpected condition.\n");
		exit(1); //exit with error
    }

	return canGo;

}
