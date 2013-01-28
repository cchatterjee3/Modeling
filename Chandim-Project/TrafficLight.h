#include "CommonDefs.h"



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
              
              state cyclestate(); //cyclestate
}
