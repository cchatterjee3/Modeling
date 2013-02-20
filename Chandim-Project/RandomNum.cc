/**
*	@file RandomNum.cc 
*	contains defination of randomnumber generator class
*	And brief testing of the random numbers
*/

//for get time of the day 
#ifdef _WIN32
	#include <windows.h>
	#include <time.h>
#else
	#include <sys/time.h> 
	#include <time.h> 
        #include <stdlib.h>
#endif

#include <math.h>
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
/**
*	\brief functionality to be tested for random number genrator
*
*/

#define UNF_MEAN	0.50
#define UNF_VAR		1.0/12.0
#define ABS(a)	   (((a) < 0) ? -(a) : (a))

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

	double SD = sqrt(ssum/trials - average*average);

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

void rng_mean_test(long long n)
{
	RandomNumGen R1(0);	

	double sum,ssum,average,temp;
	sum=0;
	ssum=0;

	for (long long i = 0; i < n; ++i)
	{
		temp=R1.Next();
		sum+=temp;
		ssum+=temp*temp;
		// hist[(int )(buckets*temp)]++;
	}

	average = (double) sum/(double) n;

	printf("%ld\t%lf\t%lf\n",n,average,ABS(average-UNF_MEAN));
}

void rng_var_test(long long n)
{
	RandomNumGen R1(0);	

	double sum,ssum,average,temp;
	sum=0;
	ssum=0;

	for (long long i = 0; i < n; ++i)
	{
		temp=R1.Next();
		sum+=temp;
		ssum+=temp*temp;
		// hist[(int )(buckets*temp)]++;
	}

	average = (double) sum/(double) n;
	double VAR = (ssum/n - average*average);
	printf("%ld\t%lf\t%lf\n",n,VAR,ABS(VAR-UNF_VAR));
}

void chi_square_test(RandomNumGen* R1,int buckets,int trials)
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

	double SD = sqrt(ssum/trials - average*average);

	double X_s=0;
	int  E_i= trials/buckets ;
	for (int i = 0; i < buckets; ++i)
	{
		X_s += (double)(hist[i]-E_i)*(double)(hist[i]-E_i)/(double)E_i  ;
		
	}

	printf("%d\t%d\t%lf \n",buckets,trials,X_s);

	R1->Reset();

}

int main(int argc, char const *argv[])
{
	RandomNumGen R1(0);
	/**
	*	First Mean test
	*
	*/

	printf(" ===========Mean Test==========\n");
	long long i=2;
	while(i<100000000)
	{	
		rng_mean_test(i);
		i=i*2;
	}

	/**
	*	Varience test
	*
	*/
	printf(" ===========Varience  Test==========\n");

	i=2;
	while(i<100000000)
	{	
		rng_var_test(i);
		i=i*2;
	}

	/**
	*	Chi sqaure test
	*
	*/

	printf(" ===========Chi Square Test==========\n");
	chi_square_test(&R1,10,10000000);
	chi_square_test(&R1,100,10000000);
	chi_square_test(&R1,1000,10000000);
	chi_square_test(&R1,10000,10000000);
	chi_square_test(&R1,100000,10000000);

	unittest_hist(&R1,10,1000000);
	printf("Cycle is %lu \n", find_cycle(&R1));
	
	return 0;
}


//#elif
	/* code */
#endif 

