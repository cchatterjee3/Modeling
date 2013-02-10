//for get time of the day 
#include <sys/time.h> 

#include "RandomNum.h"


unsigned long gettime(void)
{
	//gives current time for genrating seed for random number
		         
	timeval tim;
	gettimeofday(&tim,NULL);
	unsigned long t1=tim.tv_sec*1000000.0+tim.tv_usec;
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

RandomNumGen(unsigned long x0)
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