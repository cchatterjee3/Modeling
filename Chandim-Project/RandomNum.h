/*
Brief implementation of number genrator and utilities 

*/

#define MINSTDX 1
#define MINSTDM 2147483647
#define MINSTDG 16807

unsigned long gettime();

class RandomNumGen
{
	private:
		//current state of the multiplier
		unsigned long X; 

		//multiplier
		unsigned long g; 

		//modulo base
		unsigned long m; 
	public:
		//Constructor
		RandomNumGen(); 	

		RandomNumGen(unsigned long x0);

		//Generates next number
		double Next();			

		//Resets the random number genrator
		void Reset();		

		// Gives state of random genrator
		unsigned long GetState();

		//Desctructor
		~RandomNumGen();

};