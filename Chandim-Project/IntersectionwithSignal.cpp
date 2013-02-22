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

#include<list>
using namespace std;

#define useEvictL



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
	  EB=new TrafficLight(1, 1, (state)0, (state)0, 8, 1.8, 1.8, 30, 3.8, 55, this, 8, 0);
	  WB=new TrafficLight(3, 1, (state)0, (state)0, 5, 3.6, 4.2, 28.8, 3.8, 55, this, 3.8, 0);
	  NB=new TrafficLight(0, 1, (state)5, (state)0, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this, 45.4, 0);
	  SB=new TrafficLight(2, 1, (state)5, (state)0, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this, 45.4, 0);
    }
    if (ID==2)
    {
      //Traffic light on Peachtree and 11th
      EB=new TrafficLight(1, 0, (state)3, (state)0, 0, 0, 0, 20.3, 3.6, 76.2, this, 20.3, 0);
	  WB=new TrafficLight(3, 0, (state)3, (state)0, 0, 0, 0, 20.3, 3.6, 76.2, this,20.3, 0);
	  NB=new TrafficLight(0, 0, (state)5, (state)0, 0, 0, 0, 41.5, 3.2, 55.4, this, 43.7, 0);
	  SB=new TrafficLight(2, 0, (state)5, (state)0, 0, 0, 0, 41.5, 3.2, 55.4, this, 43.7, 0);            
    }
    if (ID==3)
    {
      //Traffic light on Peachtree and 12th
      EB=new TrafficLight(1, 0, (state)3, (state)0, 0, 0, 0, 27.4, 3.6, 69.2, this, 27.4, 0);
	  WB=new TrafficLight(3, 0, (state)3, (state)0, 0, 0, 0, 27.4, 3.6, 69.2, this, 27.4, 0);
	  NB=new TrafficLight(0, 0, (state)5, (state)0, 0, 0, 0, 61.3, 3.2, 35.7, this, 31, 0);
	  SB=new TrafficLight(2, 0, (state)5, (state)0, 0, 0, 0, 61.3, 3.2, 35.7, this, 31, 0);       
    }
    if (ID==5)
    {
    //TrafficLight(int id, int typ, state initialState, state initialstate2, 
    //double Ph1, double Ph2, double Ph3, double Ph4, 
    // double Ph5, double Ph6, IntersectionwithSignal* p, Time_t timetoStart, Time_t timetoStart2);

      //Traffic light on Peachtree and 14th
      EB=new TrafficLight(1, 2, (state)3, (state)0, 9.9, 3.6, 87, 36.6, 3.7, 60.2, this, 9.9, 36.6);
	  WB=new TrafficLight(3, 0, (state)5, (state)0, 0, 0, 0, 22.8, 3.7, 74, this, 13.5, 0);
	  NB=new TrafficLight(0, 1, (state)5, (state)0, 8.8, 3.6, 3.6, 35.2, 3.2, 46.1, this, 40, 0);
	  SB=new TrafficLight(2, 1, (state)5, (state)0, 11.3, 3.6, 0.5, 36.6, 3.2, 45.3, this, 40, 0);          
    }

	//set traffic lights array
	TLight[0]=NB; TLight[1]=EB; TLight[2]=SB; TLight[3]=WB;

}

IntersectionwithSignal::~IntersectionwithSignal(void)
{
                                                     
}

void IntersectionwithSignal::EvictL (VehicleQueue* joinqueue)
{
//	cout << "evictL called, Qdirection is " << getQdirection(this, joinqueue) << " Q lane is "<< getQlane(this, joinqueue) << 
//					" Inter ID=" << ID << " time=" << sim->getNow() << endl;
    //cin.get();
    
	int Qdirection=getQdirection(this, joinqueue);
    int Qlane=getQlane(this, joinqueue);
        
    int QState = QCanGo2 (Qdirection, 1);
    
    bool sendcar = false;
    bool carExists = false;
    
    list<VehicleClass*>::iterator it;
 
	dir dest;
	int Turn;
    
    
	if (QState==2) //Queue is not empty, and the light is green, intersection not busy
	{
        //find next candidate vehicle
        
        carExists = false;
        for (it = joinqueue->Q1.begin() ; it != joinqueue->Q1.end() ; ++it )
        {
            if( it != joinqueue->Q1.begin() )
            {
                dest = this->routingtable[(*it)->getDestination()];
                Turn = turn(dest, Qdirection);
                if(Turn == -1)
                {
                    carExists = true;
                    break;
                }
            }
        }
        if (!carExists )
        {
        	sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
            return;
        }
        
        Intersection * NextInter = NULL;
        VehicleQueue * futureQ = NULL;
        bool isfull=false;
        int Turn;
		// getting info about the next Queue and next intersection
        NextQInfo(joinqueue, (*it), NextInter, futureQ, isfull, Turn);

        if( futureQ==NULL ) //There is no next Queue
        {

#ifdef test
    eventDsc E1;
    E1.type = PSC;
    E1.InterID =ID;
    E1.QDir = getQdirection(this, joinqueue);
    E1.QLane = 1;
    E1.timetag = sim->getNow();
    (*it)->EventList.push_back(E1);
#endif

            sim->Schedule( startToPass, &Intersection::VehiclePass, this, (*it), Turn);//(debug)
            (*it)->out_of_line = true;
        	sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
			if((*it)->getLastQ() != NULL)
				(*it)->getLastQ()->LastSentCar=sim->getNow(); //set the time that the queue last sent a car
			joinqueue->Q1.erase(it);
        }
        else if( !isfull ) // next queue is not full
        {

#ifdef test
    eventDsc E2;
    E2.type = PSC;
    E2.InterID =ID;
    E2.QDir = getQdirection(this, joinqueue);
    E2.QLane = 1;
    E2.timetag = sim->getNow();
    (*it)->EventList.push_back(E2);
#endif

            sim->Schedule( startToPass, &Intersection::VehiclePass, this, (*it), Turn);//(debug)
            (*it)->out_of_line = true;
        	sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
			if((*it)->getLastQ() != NULL)
				(*it)->getLastQ()->LastSentCar=sim->getNow(); //set the time that the queue last sent a car
			joinqueue->Q1.erase(it);
			//futureQ->length ++ ;
        }
        else // next Q is full, a check will be scheduled for future
        {
    		sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
        }
	}
    else if(QState == +1) //Queue is not empty, and the light is green, but intersection IS BUSY
    {   //scheduling a check for future
        
    	sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
    }
    else if(QState == -1) // Q is empty, set the flag to send the first car arriving
    {
        sim->Schedule( checkQinterval, &IntersectionwithSignal::EvictL, this, joinqueue ); //(debug)
    }
    else if(QState == 0) // light is red
    {
        //stops checking
    }
    
}

void IntersectionwithSignal::changeSignalTrigger( int LightID, int leftorthru) //checks its own signals 
{
	//When a light changes, triggers the relevant Queues to send vehicles out.
    if (TLight[LightID]->type==0 || TLight[LightID]->type==1)
    {
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
            #ifdef useEvictL
                this->EvictL( Qu[LightID][1]);
            #endif         
            
            
    	}
        else
        {
            //cout << "nobody called - ID=" << this->getID() << " light: " << LightID << endl;
        }
     }
     else
     {
           if (leftorthru==0)
           {
            	if (TLight[LightID]->getState() == GTR)
            	{
                    //cout << "state:GTR , ID=" << this->getID() << " light: " << LightID << endl;
            
            		this->EvictQ( Qu[LightID][0] );
            		this->EvictQ( Qu[LightID][1] );
            	}
            
           }
           else
           {
            	if (TLight[LightID]->getLeftState() == GLT)
            	{
                    //cout << "state:GLT , ID=" << this->getID() << " light: " << LightID << endl;
            		this->EvictQ( Qu[LightID][1]);
                    #ifdef useEvictL
                        this->EvictL( Qu[LightID][1]);
                    #endif         
            	}
            	
           }
              
     }
}

void IntersectionwithSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	//cout << "In WithSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	//cin.get() ;


#ifdef test
    eventDsc E1;
    E1.type= JQU;
    E1.InterID=ID;
    E1.QDir=getQdirection(this, joinqueue);
    E1.QLane=getQlane(this, joinqueue);
    E1.QSize=joinqueue->Q1.size();
    E1.timetag=sim->getNow();
    vehicle->EventList.push_back(E1);
#endif

	joinqueue->push(vehicle);
    //joinqueue->length ++;
	vehicle->setLastQ(joinqueue);
    if(joinqueue->GetLen() == 1) //(debug)
    {
        //cout << "joinqueue has only 1 car, evictQ called" << endl ;
//        if(joinqueue->LastSentCar==-1) // send the car now
//        {
		//	cout << "did not wait" << endl;
            this->EvictQ(joinqueue);
/*        }
        else // send the car in the future
		{
			//cout << "will wait for for " << max( BurstTime - (sim->getNow() - joinqueue->LastSentCar)  , 0.0 ) << endl;
			sim->Schedule( max( BurstTime - (sim->getNow() - joinqueue->LastSentCar)  , 0.0 ), 
                    &IntersectionwithSignal::EvictQ, this, joinqueue ); //(debug)
		}
*/
    }
	else
	{
		//cout << "waiting in line" << endl;
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
		if(TLight[Qdirection]->getType()==1 ) // 6states
		{
			if(TLight[Qdirection]->getState()==GLT)
				canGo=+2;
			else
				canGo= 0;
		}
		else if(TLight[Qdirection]->getType()==2) 
		{
			if(TLight[Qdirection]->getLeftState()==GLT)
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
		printf("error inside QCanGo, 1, unexpected condition.\n");
		printf("Intersection ID: %d, vehID: %d, sdest: %d, fdest: %d .\n", ID, Q->front()->getID(), Q->front()->getSource(), Q->front()->getDestination());
		printf("Turn=%d, local destination=%d , direction=%d, lane=%d .\n", Turn, dest, Qdirection, lane);
		cin.get();
		exit(1); //exit with error
    }

	return canGo;

}








int IntersectionwithSignal::QCanGo2 (int Qdirection, int lane) //Improved Version
	//checks its signals for a specific Queue
{

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the direction of the first member of Queue
	//+1: The queue is not empty, the traffic light is OK, But the intersection is busy
	//+2: The queue is not empty, the traffic light is OK, and the intersection is not busy

    lane=1;
	
	int canGo;
	VehicleQueue* Q = Qu[Qdirection][lane];

	if(Q->empty())
		return -1;

    // turning left from left lane
    if(TLight[Qdirection]->getType()==1 ) // 6states
    {
        if(TLight[Qdirection]->getState()==GLT)
            canGo=+2;
        else
            canGo= 0;
    }
    else if(TLight[Qdirection]->getType()==2) 
    {
        if(TLight[Qdirection]->getLeftState()==GLT)
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

	return canGo;

}
