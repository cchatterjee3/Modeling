//for get time of the day 
#ifdef _WIN32
	#include <windows.h>
	#include <time.h>
#else
	#include <sys/time.h> 
#endif

#include "RandomNum.h"


unsigned long gettime(void)
{
	//gives current time for genrating seed for random number

	/*timeval tim;
	gettimeofday(&tim,NULL);
	unsigned long t1=tim.tv_sec*1000000.0+tim.tv_usec;
	return t1; */
	
	unsigned long int t1 = (long int) time(NULL);
	return t1;
}

RandomNumGen::RandomNumGen()
{
	// If we use lehmer type random number genrator
	// there can be couple of options for multiplier 
	// modulo base and starting state
	// http://en.wikipedia.org/wiki/Lehmer_random_number_generator sums up a few of these


	//======= For time being I'm just using MINSTD ======

	X = MINSTDX;
	g = MINSTDG;
	m = MINSTDM;

}

RandomNumGen::RandomNumGen(unsigned long x0)
{
	if (x0==0)
	{
		// use time as initial seed
		x0 = gettime();
	}
	X = x0;
	g = MINSTDG;
	m = MINSTDM;
}

unsigned long RandomNumGen::GetState()
{
	//for some comparisons, it better to do it in int 
	// then doing it in double, this is where this comes handy
	return X;
}


double RandomNumGen::Next()
{
	// In general , when using 32 bit overflow can occure in next step
	// depending on values of x,m ,g overflow can still occure while using 
	// unsigned long. In that case, we must use some protection for overflow
	X = (X * g)%m;

	return (double) X/(double) m ;
}	

		
void RandomNumGen::Reset()
{
	X = MINSTDX;

}	

//destrcutor for rng;
RandomNumGen::~RandomNumGen(){}



#ifdef DEBUG

#include<stdio.h>
void unittest_hist(RandomNumGen* R1,int buckets,int trials)
{
	int* hist;
	hist = new int[buckets];

	for (int i = 0; i < buckets; ++i)
	{
		hist[i]=0;
	}

	double sum,ssum,average,temp;
	sum=0;
	ssum=0;

	for (int i = 0; i < trials; ++i)
	{
		temp=R1->Next();
		sum+=temp;
		ssum+=temp*temp;
		hist[(int )(buckets*temp)]++;
	}

	average = sum/trials;

	double SD = ssum/trials - average*average;

	printf(" \t=======Num trials 			= %d 	=======\n",trials);
	printf(" \t=======Average    			= %lf	=======\n",average);
	printf(" \t=======Standerd Deviation 		= %lf	=======\n",SD);
	printf(" \t=======Histogram=======\n");
	for (int i = 0; i < buckets; ++i)
	{
		printf("%d ",hist[i] );
	}

	printf("\n");

	R1->Reset();

}

unsigned long find_cycle(RandomNumGen *R1)
{
	R1->Reset();
	//printf("Starting state 	%lu \n",R1->GetState());
	int InitSt = R1->GetState();

	int count=0;
	R1->Next();
	while(InitSt != R1->GetState())
	{
		R1->Next();
		count++;
	}

	return count;

}

int main(int argc, char const *argv[])
{
	RandomNumGen R1(0);

	unittest_hist(&R1,10,1000000);
	printf("Cycle is %lu \n", find_cycle(&R1));
	
	return 0;
}


//#elif
	/* code */
#endif 

