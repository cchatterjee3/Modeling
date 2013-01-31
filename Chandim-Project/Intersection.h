#pragma once

#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"

//#include "TrafficLight.h"

class Intersection
{
  protected:
	int ID;
	bool haveSignal;
/*
	VehicleQueue* EBO;
	VehicleQueue* WBO;
	VehicleQueue* NBO;
	VehicleQueue* SBO;
*/
	bool busy; // busy or not
	dir routingtable[12]; //for routing cars

public:
	VehicleQueue* EBI;
	VehicleQueue* WBI;
	VehicleQueue* NBI;
	VehicleQueue* SBI;

	Intersection* NInter;	//North Intersection
	Intersection* SInter;	//South Intersection

	virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle)=0;
	Intersection();
	Intersection(int);
	~Intersection();

	int getID()	{return ID;}

};

