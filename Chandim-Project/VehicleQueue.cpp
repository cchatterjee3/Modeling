/***
brief definiation of for vehicle queue class ,defined in vehicleQueue.h

*/

#include "VehicleQueue.h"

VehicleQueue::VehicleQueue()
{
	maxLength = 30; //(debug)
    //set the time of last evicted 
    LastSentCar=-1;
	//length=0;
	busy=0;

}

VehicleQueue::VehicleQueue(VehicleQueue* Q)
{
  this->maxLength = Q->maxLength;
  this -> busy = Q->busy;
  this->LastSentCar = Q->LastSentCar;
  this->Q1 = Q->Q1;                        
}

VehicleQueue::VehicleQueue(int maxL)
{
  maxLength = maxL;                 
}

bool VehicleQueue::empty()
{
	return Q1.empty();
}

VehicleClass* VehicleQueue::front()
{
	return Q1.front();
}

void VehicleQueue::push(VehicleClass* V1)
{
	Q1.push_back(V1);
}

void VehicleQueue::pop()
{

	Q1.pop_front();
}

VehicleClass* VehicleQueue::back()
{
    return Q1.back();
}


int VehicleQueue::GetMaxLen()
{
	return maxLength;
}

int VehicleQueue::GetLen()
{
	return Q1.size();
}

bool VehicleQueue::isBusy()
{
	return busy!=0;
}
