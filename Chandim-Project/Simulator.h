#include <iostream>
#include "CommonDefs.h"
#include "Events.h"

class Simulator
{
      private:
            static Time_t now;  
            static EventSet_t events;
            static bool stopped;
            
      public:
             Simulator();
             void Stop(); //Stop executing events
             static void Run(); //Start executing events
             static void StopAt(Time_t); //define stopping time  
             Time_t getNow(){
                  return now;     
             }
             
             template <typename T, typename OBJ>
                static void Schedule(double t, void(T::*handler)(void), OBJ* obj)
              {
                EventBase* ev = new Event0<T, OBJ>(t + Simulator::Now(), handler, obj);
                events.insert(ev);
              }
            
              template <typename T, typename OBJ,
                typename U1, typename T1>
                void Schedule(double t, void(T::*handler)(U1), OBJ* obj, T1 t1)
              {
                EventBase* ev = new Event1<T, OBJ, U1, T1>(t + Simulator::Now(), handler, obj, t1);
                events.insert(ev);
              }
            
              template <typename T, typename OBJ,
                typename U1, typename T1,
                typename U2, typename T2>
                void Schedule(double t, void(T::*handler)(U1, U2), OBJ* obj, T1 t1, T2 t2)
              {
                EventBase* ev = new Event2<T, OBJ, U1, T1, U2, T2>(t + Simulator::Now(), handler, obj, t1, t2);
                events.insert(ev);
              }
            
              template <typename T, typename OBJ,
                typename U1, typename T1,
                typename U2, typename T2,
                typename U3, typename T3>
                void Schedule(double t, void(T::*handler)(U1, U2, U3), OBJ* obj, T1 t1, T2 t2, T3 t3)
              {
                EventBase* ev = new Event3<T, OBJ, U1, T1, U2, T2, U3, T3>(t + Simulator::Now(), handler, obj, t1, t2, t3);
                events.insert(ev);
              }   
              
              static Time_t Now();
              static Simulator* instance;
};
