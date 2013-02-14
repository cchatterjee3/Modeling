#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "TrafficLight.h"
#include "IntersectionwithSignal.h"
#include "CommonDefs.h"
#include "VehicleQueue.h"

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
	  EB=new TrafficLight(1, EBtype, (state)5, 8, 1.8, 1.8, 30, 3.8, 55, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 5, 3.6, 4.2, 28, 3.8, 55, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 7, 3.6, 2.2, 34.7, 3.6, 49.3, this);
    }
    if (ID==2)
    {
      //Traffic light on Peachtree and 11th
      EB=new TrafficLight(1, EBtype, (state)5, 0, 0, 0, 20.2, 3.6, 76.1, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 20.3, 3.6, 76.2, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 0, 0, 0, 41.5, 3.2, 55.4, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 0, 0, 0, 41.5, 3.2, 55.4, this);            
    }
    if (ID==3)
    {
      //Traffic light on Peachtree and 12th
      EB=new TrafficLight(1, EBtype, (state)5, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 27.3, 3.6, 69.2, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 0, 0, 0, 60.9, 3.2, 35.7, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 0, 0, 0, 61.4, 3.2, 35.7, this);             
    }
    if (ID==5)
    {
      //Traffic light on Peachtree and 14th
      EB=new TrafficLight(1, EBtype, (state)5, 9.8, 3.6, 87, 36.9, 3.7, 60.2, this);
	  WB=new TrafficLight(3, WBtype, (state)5, 0, 0, 0, 22.4, 3.7, 74, this);
	  NB=new TrafficLight(0, NBtype, (state)5, 8.8, 3.6, 3.6, 34.6, 3.2, 46.1, this);
	  SB=new TrafficLight(2, SBtype, (state)5, 11.6, 3.6, 0.5, 36.6, 3.2, 45.3, this);          
    }

	//set traffic lights array
	TLight[0]=NB; TLight[1]=EB; TLight[2]=SB; TLight[3]=WB;

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
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<"SUCCESS!!!!!!"<<endl; cin.get();
		}
		//schedule north intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event
			
			cout << "joining northern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

            dir futuredir = NInter->routingtable[vehicle->getDestination()];
            switch (futuredir)
            {
               case N:
                 if (NInter->NBI1->GetLen()<NInter->NBI2->GetLen()) 
                 {
    			    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  NInter , NInter->NBI1 , vehicle); //(debug)
                 }
                 else
                 {
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  NInter , NInter->NBI2 , vehicle);   
                 }
                 break;
               case E:
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  NInter , NInter->NBI1 , vehicle); 
    				  break;
               case W:
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  NInter , NInter->NBI2 , vehicle); 
    				  break;
            }
		}
	}
	else if (dest==S)
	{
		if(ID==1)
		{
			// exit the system
			vehicle->setEndTime(sim->getNow());
			ExitQ->push(vehicle);
			cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<"SUCCESS!!!!!!"<<endl; cin.get();
		}
		//schedule south intersection addVehicletoQueue
		else
		{
			//schedule next intersection join queue event

			cout << "joining southern intersection ID="<< vehicle->getID()<<" , next intersection ID: "<<NInter->getID()<< " in time "<<sim->getNow()+roadSegTime  <<endl;
			cout << "press any key to continue..."<<endl;	cin.get() ;

			dir futuredir = SInter->routingtable[vehicle->getDestination()];
            switch (futuredir)
            {
               case N:
                 if (SInter->SBI1->GetLen()<SInter->SBI2->GetLen()) 
                 {
    			    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  SInter , SInter->SBI1 , vehicle); //(debug)
                 }
                 else
                 {
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  SInter , SInter->SBI2 , vehicle);   
                 }
                 break;
               case E:
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  SInter , SInter->SBI2 , vehicle); 
    				  break;
               case W:
                    sim->Schedule(roadSegTime, &Intersection::addVehicletoQueue,
    				  SInter , SInter->SBI1 , vehicle); 
    				  break;
            }
		}
	}
	else
	{
		// exit the system
		vehicle->setEndTime(sim->getNow());
		ExitQ->push(vehicle);

	    cout << "--> vehicle ID="<< vehicle->getID()<<" , reached destination on t="<<sim->getNow()<<"SUCCESS!!!!!!"<<endl; cin.get();
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

    int check1=ID;
    int check2=vehicle->getID();
    
	cout << "In withSignal::addVehicletoQueue with vehicle ID="<< vehicle->getID()<<" , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;

	joinqueue->push(vehicle);
	vehicle->setLastQ(joinqueue);
    if(joinqueue->empty()) //(debug)
    {
        cout << "joinqueue is empty, evictQ called";
        this->EvictQ(joinqueue);
    }

/*	int Qstate =QCanGo(joinqueue);

	if(  Qstate==1 )
	{
		VehicleClass* vehicle=joinqueue->front();
		joinqueue->pop();
		//schedule vehicle pass in startToPass time
		vehicle->setLastQ(joinqueue);
		sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)

		cout << "--> VehiclePass scheduled for vehicle ID="<< vehicle->getID()<<" , for time Now+startToPass="<<sim->getNow()+startToPass <<endl;
		cout << "press any key to continue..."<<endl;	cin.get() ;

	}
    else
    {
        cout<<"Waiting at Signal at "<<this->getID()<<endl; cin.get();
    }
*/


}

void IntersectionwithSignal::EvictQ(VehicleQueue* joinqueue)
{
    cout << "evictQ called, Qdirection is " << this->getQdirection(joinqueue) << " Q lane is "<< this->getQlane(joinqueue) << endl;
    cin.get();
    
	int Qdirection=getQdirection(joinqueue);
	int Qlane=getQlane(joinqueue);
	int QState=QCanGo(Qdirection, Qlane);
	if (QState==1) //Queue is not empty, and the vehicle can go
	{
		//if(
		//sim->Schedule(startToPass, &IntersectionwithSignal::VehiclePass, this, vehicle);//(debug)
	}
/*

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

*/
}

void IntersectionwithSignal::changeSignalTrigger( int LightID) //checks its own signals 
{
	//When a light changes, triggers the relevant Queues to send vehicles out.

	if (TLight[LightID]->getState() == GTR)
	{
        cout << "state:GTR , ID=" << this->getID() << " light: " << LightID << endl;

		this->EvictQ( Qu[LightID][0] );
		this->EvictQ( Qu[LightID][1] );
	}
	else if (TLight[LightID]->getState() == GLT)
	{
        cout << "state:GLT , ID=" << this->getID() << " light: " << LightID << endl;
		this->EvictQ( Qu[LightID][1]);
	}
    else
    {
        cout << "nobody called - ID=" << this->getID() << " light: " << LightID << endl;
    }
}

int IntersectionwithSignal::QCanGo (int Qdirection, int lane) //Improved Version
	//checks its signals for a specific Queue
{

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the direction of the first member of Queue
	//+1: Yes, the queue is not empty and the trafficc light is green for the first member
	
	bool canGo = false;
	VehicleQueue* Q = Qu[Qdirection][lane];

	if(Q->empty())
		return -1;
	
	dir dest=this->routingtable[Q->front()->getDestination()];
	int Turn=turn(dest, Qdirection);

	if(Turn==0)	// moving forward
		canGo=
			(TLight[Qdirection]->getState()==GTR)	&& (!(Qu[reg(Qdirection+1)][0])->isBusy())
													&& (!(Qu[reg(Qdirection+1)][1])->isBusy())
													&& (!(Qu[reg(Qdirection-1)][0])->isBusy())
													&& (!(Qu[reg(Qdirection-1)][1])->isBusy());
	else if(lane==0 && Turn==-1) // turning right from right lane
		canGo=!(Qu[reg(Qdirection-1)][0])->isBusy();
	else if(lane==1 && Turn==+1) // turning left from left lane
	{
		if(TLight[Qdirection]->getType()==1) // 6states
			canGo = (TLight[Qdirection]->getState()==GLT);
		else //3 states
			canGo =(!(Qu[reg(Qdirection+1)][0])->isBusy() 
				&& (!(Qu[reg(Qdirection+1)][1])->isBusy()) 
				&& (!(Qu[reg(Qdirection-1)][1])->isBusy()) 
				&& (!(Qu[reg(Qdirection+2)][0])->isBusy()) 
				&& (!(Qu[reg(Qdirection+2)][1])->isBusy())); 
	}
	else //no other case is acceptable
		printf("error inside QCanGo, unexpected condition.");
		exit(1); //exit with error

}

int IntersectionwithSignal::QCanGo(VehicleQueue* Q) //First Version
	//checks its signals for a specific Queue
{

	/*cout << "In withSignal::QCanGo  , Now="<<sim->getNow() <<endl;
	cout << "press any key to continue..."<<endl;	cin.get() ;*/

	//test whether a certain queue can start sending vehicles out
	//-1: Q is empty
	// 0: Light is not green for the direction of the first member of Queue
	//+1: Yes, the queue is not empty and the trafficc light is green
	
	bool canGo = false;

	if(Q->empty())
	{
		return -1;
	}
	
	//VehicleClass* NextVeh=&(Q->front()); // define a Vehicle pointer
	
	
	dir dest=this->routingtable[Q->front()->getDestination()];

	//--------------------------------------------
	if(Q==EBI1)
	{
		switch(dest)
		{
			case S:
				if (SBI1->isBusy()==false)
				   canGo = true;
				break;
			case E:
				canGo=(EB->getState()==GTR) && (!SBI1->isBusy()) && (!SBI2->isBusy()) && (!NBI2->isBusy()) && (!NBI1->isBusy());
				break;
		}	
	}
	else if (Q==EBI2)
	{
       switch (dest)
       {
         case E :
            canGo=(EB->getState()==GTR) && (!SBI1->isBusy()) && (!SBI2->isBusy()) && (!NBI2->isBusy()) && (!NBI1->isBusy());
	        break;  
         case N:
              if (EB->getType())
                canGo = (EB->getState()==GLT); 
              else
              {
                canGo = (!SBI1->isBusy() && (!SBI2->isBusy()) && (!NBI2->isBusy()) &&(!WBI1->isBusy()) && (!WBI2->isBusy()));   
              }   
       }     
    }
	//--------------------------------------------
	if(Q==SBI1)
	{
		switch(dest)
		{
			case W:
				if (WBI1->isBusy()==false)
				   canGo = true;
				break;
			case S:
				canGo=(SB->getState()==GTR) && (!WBI1->isBusy()) && (!WBI2->isBusy()) && (!EBI2->isBusy()) && (!EBI1->isBusy());
				break;
		}	
	}
	else if (Q==SBI2)
	{
       switch (dest)
       {
         case S :
            canGo=(SB->getState()==GTR) && (!WBI1->isBusy()) && (!WBI2->isBusy()) && (!EBI2->isBusy()) && (!EBI1->isBusy());
	        break;  
         case E:
              if (SB->getType())
                canGo = (SB->getState()==GLT); 
              else
              {
                canGo = (!WBI1->isBusy() && (!WBI2->isBusy()) && (!EBI2->isBusy()) &&(!NBI1->isBusy()) && (!NBI2->isBusy()));   
              }   
       }     
    }
    //--------------------------------------------
	if(Q==WBI1)
	{
		switch(dest)
		{
			case N:
				if (NBI1->isBusy()==false)
				   canGo = true;
				break;
			case W:
				canGo=(WB->getState()==GTR) && (!NBI1->isBusy()) && (!NBI2->isBusy()) && (!SBI2->isBusy()) && (!SBI1->isBusy());
				break;
		}	
	}
	else if (Q==WBI2)
	{
       switch (dest)
       {
         case W :
            canGo=(WB->getState()==GTR) && (!NBI1->isBusy()) && (!NBI2->isBusy()) && (!SBI2->isBusy()) && (!SBI1->isBusy());
	        break;  
         case S:
              if (WB->getType())
                canGo = (WB->getState()==GLT); 
              else
              {
                canGo = (!NBI1->isBusy() && (!NBI2->isBusy()) && (!SBI2->isBusy()) &&(!EBI1->isBusy()) && (!EBI2->isBusy()));   
              }   
       }     
    }
	//--------------------------------------------
	if(Q==NBI1)
	{
		switch(dest)
		{
			case E:
				if (EBI1->isBusy()==false)
				   canGo = true;
				break;
			case N:
				canGo=(NB->getState()==GTR) && (!EBI1->isBusy()) && (!EBI2->isBusy()) && (!WBI2->isBusy()) && (!WBI1->isBusy());
				break;
		}	
	}
	else if (Q==NBI2)
	{
       switch (dest)
       {
         case N :
            canGo=(NB->getState()==GTR) && (!EBI1->isBusy()) && (!EBI2->isBusy()) && (!WBI2->isBusy()) && (!WBI1->isBusy());
	        break;  
         case W:
              if (NB->getType())
                canGo = (NB->getState()==GLT); 
              else
              {
                canGo = (!EBI1->isBusy() && (!EBI2->isBusy()) && (!WBI2->isBusy()) &&(!SBI1->isBusy()) && (!SBI2->isBusy()));   
              }   
       }     
    }
	
	if(canGo==true)
		return 1;
	else
		return 0;

}

