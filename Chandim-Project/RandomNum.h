/**
 *  @file RandomNum.h
 *	A Random number generator class. This class describes the implementation
 * 	number genrator
 */

#define MINSTDX 1			/**< Default starting state */
#define MINSTDM 2147483647	/**< Modulus for random number genrator */
#define MINSTDG 16807		/**< Multiplier for random number genrator */

unsigned long gettime();

class RandomNumGen
{
	private:
		
		unsigned long X;  /**< Stores current state of the multiplier */

		//multiplier
		unsigned long g;  /**< Stores the multiplier */

		//modulo base
		unsigned long m; /**< Stores the large prime as modulo base */

	public:
		
		/**
		*	Constructor: Initializes the default parameters of Random number
		*	genrator
		*/
		RandomNumGen(); 	

		/**
		*	Constuctor: Initializes the starting state with x0
		*	@param x0 is long input, if 0 takes starting point 
		* 	seed as time, otherwise  sets x0 as the internal state
		*
		*/
		RandomNumGen(unsigned long x0);

		/**
		*	Genrates next random number
		*
		*/
		double Next();			

		/**
		*	Resets the random number generator
		*
		*/
		void Reset();		

		/**
		*	Gives state of random genrator.
		*	Used for debugging purpose
		*/
		unsigned long GetState();

		/**
		*	Destructor for random number genrator
		*
		*/
		~RandomNumGen();

};
