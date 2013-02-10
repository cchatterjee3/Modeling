/*
Brief implementation of number genrator and utilities 

*/

#define MINSTDX 1
#define MINSTDM 2147483647
#define MINSTDG 16807


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

		//Generates next number
		double Next();			

		//Resets the random number genrator
		void Reset();				

		//Desctructor
		~RandomNumGen();

};