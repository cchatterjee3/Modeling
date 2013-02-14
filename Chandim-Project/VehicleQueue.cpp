/***
brief definiation of for vehicle queue class ,defined in vehicleQueue.h

*/

#include "VehicleQueue.h"

VehicleQueue::VehicleQueue()
{
	maxLength = 15; //(debug)
    //set the time of last evicted 
    LastSentCar=-1;
	length=0;

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
	Q1.push(V1);
}

void VehicleQueue::pop()
{

	Q1.pop();
}

int VehicleQueue::GetMaxLen()
{
	return maxLength;
}

int VehicleQueue::GetLen()
{
	return length;
}

bool VehicleQueue::isBusy()
{
	return busy!=0;
}
