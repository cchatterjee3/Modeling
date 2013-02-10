#include "TrafficLight.h"
#include "Intersection.h"
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"
#include <iostream>

using namespace std;

class _Topology
{
	public:
	

	Intersection *I1; //10th street
	Intersection *I2; //11th street
	Intersection *I3; //12th street
	Intersection *I4; //13th street
	Intersection *I5; //14th street

	VehicleQueue* ExitQ;
	
	_Topology(){
		I1=new IntersectionwithSignal	(1);
		I2=new IntersectionwithSignal	(2);
		I3=new IntersectionwithSignal	(3);
		I4=new IntersectionwithoutSignal(4);
		I5=new IntersectionwithSignal	(5);
		
		// setting connections
		I1->NInter=I2;	I1->SInter=NULL;	
		I2->NInter=I3;	I2->SInter=I1;	
		I3->NInter=I4;	I3->SInter=I2;	
		I4->NInter=I5;	I4->SInter=I3;	
		I5->NInter=NULL;I5->SInter=I4;	
		
        // setting exit Queue
		ExitQ = new VehicleQueue;
		I1->ExitQ=ExitQ;
		I2->ExitQ=ExitQ;
		I3->ExitQ=ExitQ;
		I4->ExitQ=ExitQ;
		I5->ExitQ=ExitQ;


	}
	
    //IntersectionwithSignal		I2(2); //11th street
    //IntersectionwithSignal		I3(3); //12th street
    //IntersectionwithoutSignal	I4(4); //13th street
    //IntersectionwithSignal		I5(5); //14th street
};

