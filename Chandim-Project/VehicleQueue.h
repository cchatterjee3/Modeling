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
		std::queue<VehicleClass* > Q1;
		
		bool busy;

	public:
		//constructor
		VehicleQueue();

		VehicleClass* front();

		bool empty();
		void push(VehicleClass*);
		void pop();
		//int GetMaxLen();
		int GetLen();
		bool isBusy();
		void setBusy(bool);
};

#endif
