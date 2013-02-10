#include "TrafficLight.h"
#include "CommonDefs.h"

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
}


TrafficLight::~TrafficLight()
{
}


state TrafficLight:: cyclestate()
{
      //Cycles signal to next state	
      if(type==1)
        return (state)((curstate+1)%6);
      else
        return (state)(((curstate+1)%3) + 3 );

//	return (state)(  (   (curstate+1)%((type+1)*3)  ) +  ((1-type)*3)  );
}

