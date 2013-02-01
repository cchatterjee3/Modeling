#include<math.h>
#include "calender_queue.h"

#define DEBUG 

int calender_queue::getQsize()
{
  return Qsize;
}

int calender_queue::gettimeframe()
{
  return cur_time_frame;   
}

void calender_queue::insert(EventBase* E1)
{
	// This function adds the event *E1 in the calender queue
       

	//Finding out which bukcet this event belongs to
	Time_t t1 = E1->getTime();
	
	int bucket_id = (int) (fmod(t1,  CALENDER_PERIOD)/BUCKET_SIZE);
	/*

	*/
	cout<<"Inserted event into "<<bucket_id<<endl;
	if (bucket_id == 659)
	{
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<"ATTENTION!!!!!!!!!!!!!!!!!:"<<endl;
	   cout<<E1->getTime()<<endl;
    } 
	bucket* cur_bucket;
	cur_bucket = &buckets[bucket_id];
	
	//Add this event to the end of the present queue
	
	/*bucket::iterator it;
	it = cur_bucket->end();
	cur_bucket->insert(it,E1);*/
	cur_bucket->push_back(E1);
	if (bucket_id == 659)
	   cout<<"Inside 659 Pulled out object after pushing "<<(*cur_bucket->begin())->getTime()<<endl;
	//Increment the size of array
	Qsize++;

}

void calender_queue::check659bucket()
{
     cout<<"Check 659: "<<((*buckets[659].begin())->getTime())<<" "<<(buckets[659].size())<<endl;     
}
void calender_queue::dequeue(EventBase* E1)
{
	//This function removes an arbitrary event E1 from
	//calender queue

	Time_t t1 = E1->getTime();
	int bucket_id = (int) (fmod(t1,  CALENDER_PERIOD)/BUCKET_SIZE);
	
	buckets[bucket_id].remove(E1);

	
	Qsize--;


}

EventBase* calender_queue::PopNext()
{
	// this functions pops the next event to scheduled

	//if  Q is empty return NULL
	EventBase* E1;
	E1 = NULL;
	//cout<<"Inside PopNext "<<Qsize<<endl;
	cout<<cur_time_frame<<endl;
	if(Qsize==0) return E1;
    check659bucket();
	//Now search for the next events from  
	 int count = 0;
	while(E1==NULL)
	{	int cur_bucket = cur_time_frame%BUCKET_COUNT;
 	    //cout <<"Inside While LOOP Iteration number:"<<count<<endl;  
		EventBase* temp;
		
		temp = next_event(cur_bucket);
		if (temp!=NULL)
		{
            if (temp->getTime()< (cur_time_frame+1)*time_frame_size)
    		{
                //cout<<"DANGER"<<endl;
    			remove_event(cur_bucket,temp);
    			if (cur_bucket == 659)
    			   cout<<"Inside Danger Zone: "<<temp->getTime()<<endl;
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

EventBase* calender_queue::next_event(int bucket_id)
{
    if (buckets[bucket_id].empty() == true)
       return NULL;
	bucket::iterator it;
	Time_t min_t;
	EventBase* mint_Event;
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

void calender_queue::remove_event(int i,EventBase* E1)
{
     if (i == 659)
        cout<<"Checking 659th bucket's size and contents:\n "<<E1->getTime()<<endl;
     cout<<"before removing event "<<buckets[i].size()<<endl;
	buckets[i].remove(E1);
	cout<<"after removing event "<<buckets[i].size()<<endl;
	Qsize--;
}

int calender_queue::get_bucket_count()
{
	return bucket_count;
}

calender_queue::calender_queue()
{
	bucket* temp;
	for (int i = 0; i < BUCKET_COUNT; ++i)
	{	
		temp = new bucket;
		buckets.push_back(*temp);
	}

	Qsize=0;
	cur_time_frame =0;
	bucket_count = 72000;
	time_frame_size =0.1;

}
