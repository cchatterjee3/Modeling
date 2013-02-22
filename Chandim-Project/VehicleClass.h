/**
*    @file VehicleClass.h
*   Contains description of vehicle class
*/

#pragma once
#define DEF_VLENGTH
#include "CommonDefs.h"


#include "testing/test1.h"



#ifdef test
    #include <list>
    #include "Simulator.h"
    extern Simulator* sim ;
#endif

class VehicleClass;
class VehicleQueue;
//typedef std::queue<VehicleClass> VehicleQueue;

class VehicleClass
{
  private:
         int fDestination;  /**< //final location */
         int sDestination;  /**< //starting location */
         int length;        /**< //vehicle length */
         int ID;            /**< //car ID for simulation purpose */
         dir currentDirection;  /**< //current direction */
         VehicleQueue* LastQ;
  public:
      bool out_of_line;
      
      Time_t startTime;  /**< Time when a car comes into existance */
         Time_t endTime;    /**< Time when a car exits out of the system */

#ifdef test
      std::list<eventDsc> EventList;
#endif      
  		/**
        *    Sets the end time
        *
        */
        void setEndTime(Time_t t);
        /**
        *    Gets the ID of the car
        *
        */
  		int getID();
         //VehicleClass(int ID, int sDestination...)     !!Constructor
         //!!Constructor

        /**
        *    Updated the direction of the car 
        *
        */
         void updateDirection (dir Direction);

         /**
         *    outputs the direction of the car
         *
         */
		 dir getDirection ();

         /**
         *    Sets the Vehicle queue to which the car eblonged
         *
         */
		 void setLastQ (VehicleQueue* Q);


         /**
         *    outputs the last queue
         *
         */
		 VehicleQueue* getLastQ ();
         
         /**
         *    Returns the start time
         *
         */
         Time_t StartTime(){return startTime;};
         /**
         *    Returns endtime of the car
         *
         */
         Time_t EndTime(){return endTime;};
         
         /**
         *    Returns destination of the car
         *
         */
         int getDestination ();

         /**
         *    Returns the source of the car
         *
         */
		 int getSource ();
         
         /**
         *    Default constructor
         *
         */
         VehicleClass(int id, int start, int Dest, Time_t starttime);
         VehicleClass();
         /**
         *    Default destructor
         *
         */
         ~VehicleClass();
};
