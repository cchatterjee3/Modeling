#include <assert.h>
#include <math.h>
#include <iostream>
#include "testing.h"
#include "../Events.h"

#include "quick_sort.cc"

using namespace std;

void unittest_CQ_enqueue(int i)
{

	calender_queue cq;
	
	//generate a list of time stamps for enqueing and dequeing operation
	Time_t *et_list_in,*et_list_out;
	et_list_in = new Time_t[i];

	//Enqueue each of the events into the list one by one
	for (int j = 0; j < i; ++j)
	{
		Time_t t= TOTAL_TIME*((double) rand()/ (double) RAND_MAX);
		EventBase temp(t);
		et_list_in[j] =t;
		cq.enqueue(&temp);

	}

	//sort the event time list
	quickSort(et_list_in, 0, i-1);

	
	//Now dequeue the list and not down the time stamps
	et_list_out = new Time_t[i];

	for (int j = 0; j < i; ++j)
	{

		EventBase* temp;
		temp = cq.PopNext();
		et_list_out[j] =temp->getTime();
	}

	//Now check for error
	for (int j = 0; j < i; ++j)
	{
		assert(ABS(et_list_in[j]-et_list_out[j])<EPS);
	}

	cout<<"Enqueue Dequeue Success......"<<i<<endl;

}

void print_cq(calender_queue *cq)
{
	
}