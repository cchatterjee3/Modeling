/***
brief definiation of for vehicle queue class ,defined in vehicleQueue.h

*/

#include "VehicleQueue.h"

void VehicleQueue::setBusy(bool b)
{
  busy = b;     
}

VehicleQueue::VehicleQueue()
{
	//length = len;

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

/*int VehicleQueue::GetMaxLen()
{
	return length;
}*/

int VehicleQueue::GetLen()
{
	return (int) Q1.size();
}

bool VehicleQueue::isBusy()
{
	return busy;
}
