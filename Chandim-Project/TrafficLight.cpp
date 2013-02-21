#include "TrafficLight.h"
#include "CommonDefs.h"
#include "IntersectionwithSignal.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


extern Simulator* sim;

TrafficLight::TrafficLight()
{
	type=0;
}

TrafficLight::TrafficLight(int id, int typ, state initialState, state initialstate2, double Ph1, double Ph2, double Ph3, double Ph4, 
     double Ph5, double Ph6, IntersectionwithSignal* p, Time_t timetoStart, Time_t timetoStart2)
{
	type	  = typ; 			//set the type
	curstate  = initialState;	//set the initial state of the trafficlight
	leftstate = initialstate2;
	//setting the time intervals for each state
	GLT=Ph1;	YLT=Ph2;	RLT=Ph3;	GTR=Ph4;	YTR=Ph5;	RTR=Ph6;
	parent = p;

	if(id>-1 && id<4)
		myid=id;
	else
	{
		printf("error in getting myid!\n");
		cin.get();
        exit(1);
	}

    int check1 = parent->getID();
    
	sim->Schedule(timetoStart, &TrafficLight::cyclestate, this, 0); //cycle currstate
	if (type == 2)
	   sim->Schedule(timetoStart2, &TrafficLight::cyclestate, this, 1); //cycle left state



}


TrafficLight::~TrafficLight()
{
}


void TrafficLight:: cyclestate(int leftorthru)
{
      
      //Cycles signal to next state	
      Time_t timetoNextSignal;
      state newstate;
      if(type==1)
        newstate = (state)((curstate+1)%6);
      else if (type ==0)
        newstate = (state)(((curstate+1)%3) + 3 );
      else if (type == 2 && leftorthru == 0)
      {
        newstate = (state)(((curstate+1)%3) + 3 );
      }
      else if (type == 2 && leftorthru == 1)
      {
        newstate = (state)(((leftstate+1)%3));
      }
      
      
        switch (newstate)
        {
          case 0:
               timetoNextSignal = GLT;
               break;
          case 1:
               timetoNextSignal = YLT;
               break;
          case 2:
               timetoNextSignal = RLT;
               break;
          case 3:
               timetoNextSignal = GTR;
               break;
          case 4:
               timetoNextSignal = YTR;
               break;
          case 5:
               timetoNextSignal = RTR;
               break;        
        }
        
        leftorthru==0 ? curstate = newstate : leftstate = newstate;
        //cout<<"Traffic Light change on Intersection "<<parent->getID()<<" and current state is "<<curstate<<" and time is "<<sim->getNow()<<endl;
		
		
		
		sim->Schedule(0, &IntersectionwithSignal::changeSignalTrigger, parent, this->myid, leftorthru );  
        
        int check1=parent->getID();  //(debug)
        
        sim->Schedule(timetoNextSignal, &TrafficLight::cyclestate, this, leftorthru);
		//return (state)(  (   (curstate+1)%((type+1)*3)  ) +  ((1-type)*3)  );
		//cout << "ID: " << myid << " : cyclestate, parent=" << parent->getID()<<" time="<<sim->getNow() << endl;
}

