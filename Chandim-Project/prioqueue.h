
#include <iostream>
#include <list>
#include <vector>

#define TOTAL_TIME 120*60
#define BUCKET_COUNT 1000000
#define BUCKET_SIZE TOTAL_TIME/BUCKET_COUNT

using namespace std;

typdef std::list<EventBase*> bucket;

class prioqueue
{
      private:
             std::vector<bucket>  buckets (BUCKET_SIZE);
             int size; //number in prioqueue
             
             
      public:
             void enqueue(EventBase*); //Insert into priority queue
             
             EventBase* dequeue(EventBase*); //Dequeues event pointed to by EventBase *
             
             EventBase* PopNext(); //Pops Next event
             
             bool isEmpty();
             
             prioqueue(); //Constructor      
}
