/*
#event types ::

1. contructor 					CNS
2. Join Queue 					JQU
3. join Q Scheduled 			JQC
4. Pass 						PSS
5. Pass Scheduled 				PSC 
6. Departure 					DEP 
7. Departure Scheduled 			DPC
8. Waiting light 				WTL
9. waiting Busy Intersection 	WTB
10. Full next Queue 			WTQ
11. Reaching Destination 		RDT

*/

//enum {CNS,JQ,JQS,P,PS,DEP,WL,WBI, WFQ,RD}

#include "../VehicleClass.h"
#include "test1.h"
#include <iostream>

#include <list>

using namespace std;

//contains  auxillairy functions for testing

void PrintEventDsc(eventDsc E1)
{
                   
	switch(E1.type)
	{
		case CNS :
			cout<<"Vehicle Started at time "<<E1.timetag<<endl;
			break;

		case JQU :
			cout<<"Vehicle joined queue ["<< E1.QDir<<","<<E1.QLane <<"] , Qsize=" << E1.QSize << " InterID="<<E1.InterID  <<"at time "<<E1.timetag<<endl;
			break;
		case JQC :
			cout<<"Vehicle join queue ["<< E1.QDir<<","<<E1.QLane <<"]" << " InterID="<<E1.InterID  <<" scheduled at time "<<E1.timetag<<endl;
			break;
		case PSS :
			cout<<"Vehicle passed intersection"<<  E1.InterID <<" at time "<<E1.timetag<<endl;
			break;
		case PSC :
			cout<<"Vehicle passed intersection "<<  E1.InterID <<" Scheduled at time "<<E1.timetag<<endl;
			break;
		case DEP :
			cout<<"Vehicle Departed intersection "<< E1.InterID  <<" at time "<<E1.timetag<<endl;
			break;
		case DPC :
			cout<<"Vehicle Depart intersection "<< E1.InterID  <<" scheduled at time "<<E1.timetag<<endl;
			break;
		case WTL :
			cout<<"waiting on traffic light queue ["<< E1.QDir<<","<<E1.QLane <<"]" << " InterID="<<E1.InterID << " at time "<<E1.timetag<<endl;
			break;
		case WTB :
			cout<<"waiting on busy intersection queue ["<< E1.QDir<<","<<E1.QLane <<"]" << " InterID="<<E1.InterID << " at time "<<E1.timetag<<endl;
			break;
		case WTQ :
			cout<<"waiting next queue full, queue ["<< E1.QDir<<","<<E1.QLane <<"]" << " InterID="<<E1.InterID << " at time "<<E1.timetag<<endl;
			break;
		case RDT :
			cout<<"Vehicle is reached destination "<<" at time "<<E1.timetag<<endl;
			break;


				
	}
	


}

void PrintEventList(VehicleClass* V1)
{
	/*
		Takes a vehicle and prints its event history
	*/

	std::list<eventDsc>* ED1;
	ED1 = &(V1->EventList);
	cout<<"Vehicle ID " << V1->getID() << " Source="<< V1->getSource()
            << " Destination=" << V1->getDestination() << endl ;

	for (std::list<eventDsc>::iterator it=ED1->begin(); it != ED1->end();it++)
	{
		PrintEventDsc(*it);
	}

}
