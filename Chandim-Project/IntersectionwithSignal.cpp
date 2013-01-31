#include <iostream>
#include <queue>
#include "TrafficLight.h"
#include "IntersectionwithSignal.h"
#include "CommonDefs.h"

#include <memory.h>
#include "Simulator.h"

extern Simulator* sim ;

IntersectionwithSignal::IntersectionwithSignal(){

};

IntersectionwithSignal::IntersectionwithSignal(int nID) : Intersection(nID)
{

	//setting each traffic light's type
	int EBtype, WBtype, NBtype, SBtype;

	if( ID ==1 || ID ==5 )
	{
		EBtype=1; WBtype=1; NBtype=1; SBtype=1;
		if( ID==5)
		{
			WBtype=0;
		}
	}
	else
	{
		EBtype=0; WBtype=0; NBtype=0; SBtype=0;
	}


	EB=new TrafficLight(1, (state)3, 100, 100, 100, 100, 100, 100);
	WB=new TrafficLight(1, (state)3, 100, 100, 100, 100, 100, 100);
	NB=new TrafficLight(1, (state)3, 100, 100, 100, 100, 100, 100);
	SB=new TrafficLight(1, (state)3, 100, 100, 100, 100, 100, 100);
/*
	EB=new TrafficLight(EBtype, (state)3, 100, 100, 100, 100, 100, 100);
	WB=new TrafficLight(WBtype, (state)3, 100, 100, 100, 100, 100, 100);
	NB=new TrafficLight(NBtype, (state)3, 100, 100, 100, 100, 100, 100);
	SB=new TrafficLight(SBtype, (state)3, 100, 100, 100, 100, 100, 100);
*/	
}

IntersectionwithSignal::~IntersectionwithSignal(void)
{
	
}

void IntersectionwithSignal::VehiclePass(VehicleClass* vehicle) //Vehicle passes through intersection
{

	cout << "In withSignal::VehiclePass with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	dir dest;
	//schedule vehicle deprature in service time
	sim->Schedule(PassTime, &IntersectionwithSignal::VehicleDeparture, this, vehicle);//(debug)
	//checking if there is another car in Queue and the light is green
	switch(QCanGo(vehicle->getLastQ()))
	{
		case 1:
			this->busy=true;
			//schedule another vehicle pass in service time
			sim->Schedule(PassTime, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
			break;
	}
}

void IntersectionwithSignal::VehicleDeparture (VehicleClass* vehicle) //Depart
{

	cout << "In withSignal::VehicleDeparture with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	//freeing intersection
	this->busy=false;

	//scheduling next queue join
	dir dest=this->routingtable[vehicle->getDestination()]; // finds routing direction
	if(dest==N)
	{
		//schedule north intersection addVehicletoQueue
	}
	else if (dest==S)
	{
		//schedule south intersection addVehicletoQueue
	}
	else
	{
		// schedule exit
	}
}

void IntersectionwithSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	cout << "In withSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

		cout<< "here1" << endl;

	joinqueue->push(*vehicle);

		cout<< "here2" << endl;

	int Qstate =QCanGo(joinqueue);
	
	cout << "i="<< Qstate<<endl;
	
	if(  Qstate==1  )
	{
		cout<< "here3" << endl;
		VehicleClass* vehicle=&(joinqueue->front());
		joinqueue->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(joinqueue);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)

		cout << "In withSignal, VehiclePass scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+startToPass <<endl;
		cout << "press any key to continue..."<<endl;	cin.get() ;

	}
	else if(  Qstate==1  )
	{
		
	}
	
}

void IntersectionwithSignal::changeSignalTrigger() //checks its own signals 
{

	cout << "In withSignal::changeSignalTrigger , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	//check each Q to see if they can go, schedule a pass if they could
	//checks EBI
	VehicleClass* vehicle;
	if(QCanGo(EBI)==1)
	{
		vehicle=&(EBI->front());
		EBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(EBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks WBI
	if(QCanGo(EBI)==1)
	{
		vehicle=&(WBI->front());
		WBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(WBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks NBI
	if(QCanGo(NBI)==1)
	{
		vehicle=&(NBI->front());
		NBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(NBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks SBI
	if(QCanGo(SBI)==1)
	{
		vehicle=&(SBI->front());
		SBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(SBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
}

int IntersectionwithSignal::QCanGo(VehicleQueue* Q) //checks its signals for a specific Queue
{

	cout << "In withSignal::QCanGo  , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the direction of the first member of Queue
	//+1: Yes, the queue is not empty and the trafficc light is green
	
	bool canGo;

	if(Q->empty())
	{
		return -1;
	}
	VehicleClass* NextVeh=&(Q->front()); // define a Vehicle pointer
	dir dest=this->routingtable[NextVeh->getDestination()];
	//--------------------------------------------
	if(Q==EBI)
	{
		switch(dest)
		{
			case S:
				canGo=(EB->getState()==GTR);
				break;
			case E:
				canGo=(EB->getState()==GTR);
				break;
			case N:
				canGo=(EB->getState()==GLT); // or, the other direction is not busy(debug)
				break;
		}
	}
	//--------------------------------------------
	else if(Q==WBI)
	{
		switch(dest)
		{
			case N:
				canGo=(WB->getState()==GTR);
				break;
			case W:
				canGo=(WB->getState()==GTR);
				break;
			case S:
				canGo=(WB->getState()==GLT);
				break;
		}
	}
	//--------------------------------------------
	else if(Q==NBI)
	{
		cout << "there 1 "<<dest <<endl;	cin.get() ;
		
		switch(dest)
		{
			case E:
				canGo=(NB->getState()==GTR);
				break;
			case N:
				canGo=(NB->getState()==GTR);
				break;
			case W:
				canGo=(NB->getState()==GLT);
				break;
		}
	}
	//--------------------------------------------
	else if(Q==SBI)
	{
		switch(dest)
		{
			case W:
				canGo=(SB->getState()==GTR);
				break;
			case S:
				canGo=(SB->getState()==GTR);
				break;
			case E:
				canGo=(SB->getState()==GLT);
				break;
		}
	}
	if(canGo==true)
		return 1;
	else
		return 0;

}

