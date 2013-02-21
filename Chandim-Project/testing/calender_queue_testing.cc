#include<math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef TEST
	#include<sys/time.h>
#endif

#include "calender_queue_testing.h"

typedef double Time_t;


#define NUM_TRIALS 10000	/**< Number of trials for experiments */

/**
*	Time function to measure time 
*
*/
unsigned long gettime(void)
{
	//gives current time for genrating seed for random number

	timeval tim;
	gettimeofday(&tim,NULL);
	unsigned long t1=tim.tv_sec*1000000.0+tim.tv_usec;
	return t1; 
	
	/*
	unsigned long int t1 = (long int) time(NULL);
	return t1;
	*/
}

int calender_queue::getQsize()
{
  	return Qsize;
}

int calender_queue::gettimeframe()
{
  	return cur_time_frame;   
}

void calender_queue::insert(node* E1)
{
	// This function adds the event *E1 in the calender queue
       

	//Finding out which bukcet this event belongs to
	Time_t t1 = E1->getTime();
	
	int bucket_id = (int) (fmod(t1,  calender_period)/bucket_size);

	bucket* cur_bucket;
	cur_bucket = &buckets[bucket_id];
	
	//Add this event to the end of the present queue
	
	cur_bucket->push_back(E1);
	
	//Increment the size of array
	Qsize++;

}

void calender_queue::check659bucket()
{
         
}
void calender_queue::dequeue(node* E1)
{
	//This function removes an arbitrary event E1 from
	//calender queue

	Time_t t1 = E1->getTime();
	int bucket_id = (int) (fmod(t1,  calender_period)/bucket_size);
	
	buckets[bucket_id].remove(E1);

	
	Qsize--;


}

node* calender_queue::PopNext()
{
	// this functions pops the next event to scheduled

	//if  Q is empty return NULL
	node* E1;
	E1 = NULL;
	//cout<<"Inside PopNext "<<Qsize<<endl;
	//cout<<cur_time_frame<<endl;
	if(Qsize==0) return E1;
    check659bucket();
	//Now search for the next events from  
	 int count = 0;
	while(E1==NULL)
	{	int cur_bucket = cur_time_frame%bucket_count;
 	    //cout <<"Inside While LOOP Iteration number:"<<count<<endl;  
		node* temp;
		
		temp = next_event(cur_bucket);
		if (temp!=NULL)
		{
            if (temp->getTime()< (cur_time_frame+1)*time_frame_size)
    		{
                //cout<<"DANGER"<<endl;
    			remove_event(cur_bucket,temp);
    			E1 = temp; 
    			return E1;
    		}
    		else
    		{
    			cur_time_frame++;
    		}
        }
		else
		{
			cur_time_frame++;
		}
		count++;
	}
	


}

int  calender_queue::isEmpty()
{
	//returns 1 is the calender Q is empty
	//else returns 0;
	if (Qsize==0)
	{
		return 1;
	}

	else return 0;
}

node* calender_queue::next_event(int bucket_id)
{
    if (buckets[bucket_id].empty() == true)
       return NULL;
	bucket::iterator it;
	Time_t min_t;
	node* mint_Event;
	mint_Event = *buckets[bucket_id].begin();
	min_t = mint_Event->getTime();
	for (it = buckets[bucket_id].begin(); it != buckets[bucket_id].end(); it++)
	{
		if ((*it)->getTime()<min_t)
		{
			mint_Event = (*it);
			min_t = mint_Event->getTime();
		}
	}

	return mint_Event;

}

void calender_queue::remove_event(int i,node* E1)
{
	buckets[i].remove(E1);
	Qsize--;
}

int calender_queue::get_bucket_count()
{
	return bucket_count;
}

calender_queue::calender_queue(int bk,double int_width,double bk_sz)
{
	bucket_count = bk;
	bucket_size = bk_sz;
	interval_width =int_width;
	calender_period = bucket_size*bucket_count;
	bucket* temp;
	for (int i = 0; i < bucket_count; ++i)
	{	
		temp = new bucket;
		buckets.push_back(*temp);
	}

	Qsize=0;
	cur_time_frame =0;
	
	time_frame_size =0.1;

}


/**
*	Testing procedures
*
*/
#ifdef TEST

void unittest_EqDq(int N,calender_queue* CQ)
{
	srand((unsigned)time(NULL));
	
	node* temp;
	double min_t, max_t, sum_t;

	/**
	*	Initialization of the queue
	*
	*/

	for (int i = CQ->getQsize(); i < N; ++i)
	{
		int tRand = rand();
		double X=((double)rand()/(double)RAND_MAX);
		temp = new node(tRand,X);
		CQ->insert(temp);
		
	}

	/**
	*	running n trials
	*
	*/

	long tStart = gettime();

	for (int i = 0; i < NUM_TRIALS; ++i)
	{	
		int tRand = rand();
		double X=((double)rand()/(double)RAND_MAX);
		temp = new node(tRand,X);
		CQ->insert(temp);
		temp = CQ->PopNext();
	}

	long tEnd = gettime();

	/**
	*	printing states
	*
	*/

	printf("%d\t%lf\n",N,(double)(tEnd-tStart)/(double)NUM_TRIALS);
}

int main(int argc, char const *argv[])
{
	int j=1;
	int i =1;
	calender_queue* temp;
	printf(" Bucket Count =%d \n",j);
	temp = new calender_queue(j,1.0,0.0001);	
	while(i<100000)
	{
		unittest_EqDq(i,temp);	
		i = i*2;
	}
	
	j =10;
	
	while(j<100000)
	{	int i =1;
		printf(" Bucket Count =%d \n",j);
		temp = new calender_queue(j,1.0,0.0001);	
		while(i<1000000)
		{
			unittest_EqDq(i,temp);	
			i = i*2;
		}

		j= j*2;
	}
	
	

	
	return 0;
}

#endif 