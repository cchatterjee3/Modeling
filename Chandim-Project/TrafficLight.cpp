#include "TrafficLight.h"
#include "CommonDefs.h"
#include "IntersectionwithSignal.h"
#include <iostream>

using namespace std;


extern Simulator* sim;

TrafficLight::TrafficLight()
{
	type=0;
}

TrafficLight::TrafficLight(int typ, state initialState, double Ph1, double Ph2, double Ph3, double Ph4, double Ph5, double Ph6)
{
	type	  = typ; 			//set the type
	curstate  = initialState;	//set the initial state of the trafficlight
	//setting the time intervals for each state
	GLT=Ph1;	YLT=Ph2;	RLT=Ph3;	GTR=Ph4;	YTR=Ph5;	RTR=Ph6;
	
    Time_t timetoNextSignal;
    switch (initialState)
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
     
	sim->Schedule(timetoNextSignal, &TrafficLight::cyclestate, this);
}


TrafficLight::~TrafficLight()
{
}


void TrafficLight:: cyclestate()
{

      //Cycles signal to next state	
      Time_t timetoNextSignal;
      state newstate;
      if(type==1)
        newstate = (state)((curstate+1)%6);
      else
        newstate = (state)(((curstate+1)%3) + 3 );
      
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
        curstate = newstate;
        cout<<"Traffic Light change on Intersection "<<parent->getID()<<" and current state is "<<curstate<<" and time is "<<sim->getNow()<<endl;
        sim->Schedule(timetoNextSignal, &TrafficLight::cyclestate, this);
//	return (state)(  (   (curstate+1)%((type+1)*3)  ) +  ((1-type)*3)  );
}

