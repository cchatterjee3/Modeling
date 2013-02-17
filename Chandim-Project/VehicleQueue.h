/***
brief decs for vehicle queue class , which was originally just typedef with a queue

*/
#ifndef VEHICLEQUEUE_H
#define VEHICLEQUEUE_H

#include "VehicleClass.h"


class VehicleQueue
{
	private:
		//to hold the list of the queues
        int maxLength;

	public:
		std::queue<VehicleClass* > Q1;

		int busy;
        double LastSentCar;

        //constructor
		VehicleQueue();

		VehicleClass* front();

		bool empty();
		void push(VehicleClass*);
		void pop();
		VehicleClass* back();
		int  GetMaxLen();
		int  GetLen();
		bool isBusy();
};

#endif
