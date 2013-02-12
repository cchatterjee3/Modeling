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
	
	if (ID==1) 
    {
      //Traffic light on Peachtree and 10th
	  EB=new TrafficLight(EBtype, (state)3, 8, 1.8, 1.8, 30, 3.8, 55, this);
	  WB=new TrafficLight(WBtype, (state)3, 5, 3.6, 4.2, 28, 3.8, 55, this);
	  NB=new TrafficLight(NBtype, (state)3, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
	  SB=new TrafficLight(SBtype, (state)3, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
    }
    if (ID==2)
    {
      //Traffic light on Peachtree and 11th
      EB=new TrafficLight(EBtype, (state)3, 0, 0, 0, 20.2, 3.6, 76.1, this);
	  WB=new TrafficLight(WBtype, (state)3, 0, 0, 0, 20.3, 3.6, 76.2, this);
	  NB=new TrafficLight(NBtype, (state)3, 0, 0, 0, 41.5, 3.2, 55.4, this);
	  SB=new TrafficLight(SBtype, (state)3, 0, 0, 0, 41.5, 3.2, 55.4, this);            
    }
    if (ID==3)
    {
      //Traffic light on Peachtree and 12th
      EB=new TrafficLight(EBtype, (state)3, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  WB=new TrafficLight(WBtype, (state)3, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  NB=new TrafficLight(NBtype, (state)3, 0, 0, 0, 60.9, 3.2, 35.7, this);
	  SB=new TrafficLight(SBtype, (state)3, 0, 0, 0, 61.4, 3.2, 35.7, this);             
    }
    if (ID==5)
    {
      //Traffic light on Peachtree and 14th
      EB=new TrafficLight(EBtype, (state)3, 9.8, 3.6, 87, 36.9, 3.7, 60.2, this);
	  WB=new TrafficLight(WBtype, (state)3, 0, 0, 0, 22.4, 3.7, 74, this);
	  NB=new TrafficLight(NBtype, (state)3, 8.8, 3.6, 3.6, 34.6, 3.2, 46.1, this);
	  SB=new TrafficLight(SBtype, (state)3, 11.6, 3.6, 0.5, 36.6, 3.2, 45.3, this);          
    }	
}

IntersectionwithSignal::~IntersectionwithSignal(void)
{
                                                     
}

void IntersectionwithSignal::VehiclePass(VehicleClass* vehicle) //Vehicle passes through intersection
{

	cout << "In withSignal::VehiclePass with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;
	
	busy=true;

	//schedule vehicle deprature in service time
	sim->Schedule(PassTime, &IntersectionwithSignal::VehicleDeparture, this, vehicle);//(debug)

	cout << "--> VehicleDeparture scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+PassTime <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

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
		if(ID==5)
		{
			// exit the system
			vehicle->setEndTime(sim->getNow());
			ExitQ->push(vehicle);
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
		}
		//schedule north intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event
			
			cout << "joining northern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

			sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
				NInter , NInter->NBI , vehicle); //(debug)
		}
	}
	else if (dest==S)
	{
		if(ID==1)
		{
			// exit the system
			vehicle->setEndTime(sim->getNow());
			ExitQ->push(vehicle);
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
		}
		//schedule south intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event

			cout << "joining southern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

			sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
				SInter , SInter->SBI , vehicle); //(debug)
		}
	}
	else
	{
		// exit the system
		vehicle->setEndTime(sim->getNow());
		ExitQ->push(vehicle);

	cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	}


	//checking if there is another car in Queue and the light is green
	switch(QCanGo(vehicle->getLastQ()))
	{
		case 1:
			//schedule another vehicle pass in service time
			sim->Schedule(PassTime, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
			break;
	}


}

void IntersectionwithSignal::addVehicletoQueue(VehicleQueue* joinqueue, VehicleClass* vehicle) //Adds to outgoing queue or removes vehicles 
{

	cout << "In withSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	joinqueue->push(vehicle);
	vehicle->setLastQ(joinqueue);
	int Qstate =QCanGo(joinqueue);

	if(  Qstate==1 && !busy )
	{
		VehicleClass* vehicle=joinqueue->front();
		joinqueue->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(joinqueue);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)

		cout << "--> VehiclePass scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+startToPass <<endl;
		cout << "press any key to continue..."<<endl;	cin.get() ;

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
		vehicle=EBI->front();
		EBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(EBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks WBI
	if(QCanGo(WBI)==1)
	{
		vehicle=WBI->front();
		WBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(WBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks NBI
	if(QCanGo(NBI)==1)
	{
		vehicle=NBI->front();
		NBI->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(NBI);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
	//checks SBI
	if(QCanGo(SBI)==1)
	{
		vehicle=SBI->front();
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
	
	//VehicleClass* NextVeh=&(Q->front()); // define a Vehicle pointer
	
	
	dir dest=this->routingtable[Q->front()->getDestination()];

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

