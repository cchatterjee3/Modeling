#pragma once

#include "CommonDefs.h"

#include "CommonDefs.h"
#include "VehicleClass.h"

class IntersectionwithSignal;

class TrafficLight
{
      private:
              int GLT;
              int YLT;
              int RLT;
              int GTR;
              int YTR;
              int RTR;
              state curstate;
              int type; //0 if 3 states and 1 if 6 states
              IntersectionwithSignal* parent; // Intersection it belongs to
      public:
              state getState()
              {
                    return curstate;      
              }
			  //constructors
			  TrafficLight();
			  // (type, initialState GLT, YLT, RLT, GTR, YTR, RTR)
			  // put zeros if any was inapplicable
			  TrafficLight(int typ, state initialState, int Ph1, int Ph2, int Ph3, int Ph4, int Ph5, int Ph6);

			  //destructor
			  ~TrafficLight();
          
			  //cyclestate
              state cyclestate(); 


};
