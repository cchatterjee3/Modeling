/**
 *  @file calender_queue.h
 *  @brief declartion of the class calender queue
 *
 */ 

#ifndef __CQ_H__
#define __CQ_H__


#include <iostream>
#include <list>
#include <vector>

#include "../Events.h"

#define TOTAL_TIME 120*60                          /**< Total time of the simulation */
#define BUCKET_COUNT 10000                         /**< Number of Buckets for Calender Queue */
#define BUCKET_SIZE 0.1
#define CALENDER_PERIOD BUCKET_COUNT*BUCKET_SIZE   /**< how much is a "year" for this calender */


class node;
using namespace std;


/**
*    let's describe a small data structure for testing 
*    calender queue function
*
*/

class node
{
    private: 
        int val;
        double time;
    public:
    	double getTime(){return time;}				/**< Gets time of the function */
    	node(int v,double d) {val=v; time=d;} 		/**< constructor */
    	~node() {};									/**< Destructor */

};

typedef std::list<node*> bucket;

/**
*     Calender Queue is priority queue,
*     Ref: Calendar queues: a fast 0(1) priority queue implementation
*     for the simulation event set problem
*
*/

class calender_queue
{
private:
    std::vector<bucket>  buckets; /**< buckets are vectors of event */
    int Qsize;                   /**< Number of events in the priority queue */
    int bucket_count;            /**< Number of buckets in the calender queue */
    double bucket_size;           /**< size of the bucket */
    double interval_width;       /**< total length of the interval */

    double calender_period;      
    double time_frame_size;      /**< Size of the time frame which defines a window */
    int cur_time_frame;          /**< It keeps index of bucket, from which last event was popped */

    int MaxBuckets;             /**< Number of maximum number of buckets */

    bool resizeEnabled;          /**< to dynamically resize the queue */


public:
    /**
    *    Initilizes the queue with num buckets
    *
    */
    void init(int num,double wid,double earliest);
    /**
    *    Inserts an event into the priority list
    *    @param  E1 is the even to be inserted into the list
    *
    */

    /**
    *    Resizes the calender queue based on
    *
    */
    void resize();

    void insert(node* E1); 

    /**
    *    Removes an event E1 from the list (Hence it won't be scheduled)
    *    @param E1 : event pointer to removed from the list  
    *
    */
    void dequeue(node* E1); 

    /**
    *   Pops Next event(event with minimum time stamp) in the list (and removes it as well)
    *   @return Event pointer with minimum time stamp
    */

    node* PopNext(); 

    /**
    *   Returns event with minimum time from bucket-num    
    *   @param bucket_num is the number of bucket from which
    *       you want to get the min time stamp event
    */

    node* next_event(int bucket_num); 

    /**
    *    Removes event E1 from bucket_num^th bucket
    *   @param BUcket_num is the id of bucket from which event is to be removed
    *   @param E1 is pointer to event to be removed
    */
    void remove_event(int bucket_num ,node* E1);

    /**
    *    Checks if there are anymore events left in the list 
    *
    */
    int isEmpty();

    /**
    *    Get number of buckets in the calender queue
    *
    */
    int get_bucket_count();

    /**
    *    Default constructor
    *      constructs an calender queue with buck_count number of buckets
    *
    */
    calender_queue(int bk,double int_width,double bk_sz);

    /**
    *    Returns number of element in the Q
    *
    */
    int getQsize(); 

    /**
    *    Returns the time frame from which last event was popped
    *
    */
    int gettimeframe(); //returns current time frame

    /**
    *    is there debuggin purpose
    *
    */
    void check659bucket();
};

/**
*	here starts a couple of testing routines
*
*/

/**
*	This functions enques N randomly generated numbers into the 
*	priority queue and for Num_trials times enques and deques an
*	Element and take their average
*	@param N number of elements in the priority queue
*	@param CQ pointer to the prioprity queue
*/

void unittest_EqDq(int N,calender_queue* CQ);

/**
*	It queues and deques a number of of nodes and see if they have been evicted in correct order
*	@param N number of buckets
*	@CQ calender queue 
*/

void unittest_cq(int N, calender_queue* CQ);


#endif
