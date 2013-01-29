#pragma once
<<<<<<< HEAD
#include "CommonDefs.h"

class IntersectionwithSignal;
=======

#include "CommonDefs.h"
#include "VehicleClass.h"
//#include "IntersectionwithSignal.h"
>>>>>>> 93ee5eea49a9a2ad2de3187ff3497fb2c36d760f

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
