#include <iostream>

class Simulator
{
      private:
            Time_t Now;  
      public:
             Simulator();
             void Stop(); //Stop executing events
             static void Run(); //Start executing events
             static void StopAt(Time_t); //define stopping time  
             void getNow(){
                  return Now;     
             }   
};
