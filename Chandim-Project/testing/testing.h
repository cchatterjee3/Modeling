#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include "../Events.h"
#include "../calender_queue.h"

#define EPS 0.001
#define ABS
/**
  	enques i element with random time stamp dequeues
  	and verifies if they are done in proper order 
  	generated and verifies the enque opertion
*/
void unittest_CQ_enqueue(int i); 


/**
	prints all the time stamp of each event in the queue
*/
void print_cq(calender_queue *cq); 


#endif 


