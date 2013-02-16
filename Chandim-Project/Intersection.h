#pragma once

#include <queue>
#include "CommonDefs.h"
#include "TrafficLight.h"
#include "VehicleClass.h"
#include "VehicleQueue.h"

//#include "TrafficLight.h"


class Intersection
{
  protected:
	int ID;
	bool haveSignal;

	bool busy; // busy or not
	

public:
	VehicleQueue* EBI1;
	VehicleQueue* EBI2;
	VehicleQueue* WBI1;
	VehicleQueue* WBI2;
	VehicleQueue* NBI1;
	VehicleQueue* NBI2;
	VehicleQueue* SBI1;
	VehicleQueue* SBI2;

	VehicleQueue* Qu[4][2];
	
	dir routingtable[12]; //for routing cars
	/*VehicleQueue* EBI;
	VehicleQueue* WBI;
	VehicleQueue* SBI;
	VehicleQueue* NBI;*/
	
	//int EBIlength;
	//int WBIlength;
	int NBIlength;
	int SBIlength;

	VehicleQueue* ExitQ;

	Intersection* NInter;	//neighboring intersection in the North
	Intersection* SInter;	//neighboring intersection in the South
	
	Intersection();
	Intersection(int);
	~Intersection();

	int getID()	{return ID;}
	
	void VehiclePass(VehicleClass* vehicle, int Turn); //Vehicle passes through intersection
	void VehicleDeparture (VehicleClass* vehicle); //Depart
	void EvictQ (VehicleQueue* joinqueue);

	virtual void addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle)=0;
	virtual int  QCanGo (int direction, int lane)=0; 

    int getQdirection(VehicleQueue* Q);
    int getQlane(VehicleQueue* Q);
	void NextQInfo(VehicleQueue* currentQ, VehicleClass* vehicle, Intersection * &  NextInter, VehicleQueue * & FutureQ, bool & isfull, int & Turn);

};

