
#include "Simulator.h"
#include <iostream>

using namespace std;

Time_t Simulator::now = 0;
EventSet_t Simulator::events ;
bool Simulator::stopped = false;
Simulator* Simulator::instance =0;

Simulator::Simulator()
{
   instance = this;                      
}

void Simulator::Stop()
{
  cout << "Simuator stopped!!" << endl;
  stopped = true;
}

void Simulator::Run()
{
    cout << "Simluator Started" << endl;
  while (!stopped && !events.empty())
    {
      // Get the next event
      EventBase* currentEvent = *events.begin();
      // Remove from queue
      events.erase(events.begin());
      // Advance Simulation Time
      now = currentEvent->time;  // Advance simulation time to time of event
      // call the event
      currentEvent->CallHandler();
    }  
}

void Simulator::StopAt(Time_t t)
{
  Simulator::Schedule(t - Simulator::Now(), &Simulator::Stop, Simulator::instance);
}

Time_t Simulator::Now()
{
  return now;
}
