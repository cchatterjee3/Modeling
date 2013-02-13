#pragma once

#include "CommonDefs.h"

//#include "IntersectionwithSignal.h"
#include "CommonDefs.h"
#include "VehicleClass.h"
#include "Simulator.h"

extern Simulator* sim ;
class IntersectionwithSignal;

class TrafficLight
{
      private:
              double GLT; //Green Left
              double YLT; //Yellow Left
              double RLT; //Right Left
              double GTR; //Green Through
              double YTR; //Yellow Through
              double RTR; //Right Through
              
              state curstate;
              int type; //0 if 3 states and 1 if 6 states
              IntersectionwithSignal* parent; // Intersection it belongs to
			  int myid;
      public:
              int getType()
              {
                return type;    
              }
              
              state getState()
              {
                    return curstate;      
              }
			  //constructors
			  TrafficLight();
			  // (type, initialState GLT, YLT, RLT, GTR, YTR, RTR)
			  // put zeros if any was inapplicable
			  TrafficLight(int typ, state initialState, double Ph1, double Ph2, double Ph3, double Ph4, double Ph5, double Ph6, IntersectionwithSignal* p);

			  //destructor
			  ~TrafficLight();
          
			  //cyclestate
              void cyclestate(); 


};
