#ifndef __CQ_H__
#define __CQ_H__


#include <iostream>
#include <list>
#include <vector>

#include "Events.h"

#define TOTAL_TIME 120*60
// Number of total buckets
#define BUCKET_COUNT 1000000
#define BUCKET_SIZE 0.0001
#define CALENDER_PERIOD BUCKET_COUNT*BUCKET_SIZE 

using namespace std;

typedef std::list<EventBase*> bucket;

/**
	Name changed from prioqueue to calender_queue for sake of clearity
**/

class calender_queue
{
      private:
             std::vector<bucket>  buckets;

             int Qsize; //number in prioqueue
             int bucket_count;
             double time_frame_size;
             int cur_time_frame; // It keeps index of bucket, from which last event was popped
             
             
      public:
             void enqueue(EventBase*); //Insert into priority queue
             
             void dequeue(EventBase*); //Dequeues event pointed to by EventBase *
             
             EventBase* PopNext(); //Pops Next event

             EventBase* next_event(int); //returns pointer to next event(event.time is min) in a bucket

             void remove_event(int ,EventBase*); 
             
             //Checks if there are anymore events left in the queue to be scheduled
             int isEmpty();

             int get_bucket_count();
             
             calender_queue(); //Constructor      
};


#endif