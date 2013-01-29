#include "TrafficLight.h"
#include "CommonDefs.h"

TrafficLight::TrafficLight()
{
	type=0;
}

TrafficLight::TrafficLight(int typ, state initialState, int Ph1, int Ph2, int Ph3, int Ph4, int Ph5, int Ph6)
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
	//Goes to the next step
	
	//option 1:
	//	if(type==1)
	//		return (state)((curstate+1)%6);
	//	else
	//		return (state)(  ((curstate+1)%3) + 3 );
	//

	//option 2:
	return (state)(  (   (curstate+1)%((type+1)*3)  ) +  ((1-type)*3)  );

}

