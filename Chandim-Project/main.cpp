/**
*	@file main.cpp
*
*/
#include <iostream>
#include <fstream>
#include "Simulator.h"
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"
#include "Topology.h"
#include "scheduleVehicles.h"
#include "PostProcessing.h"

#include "testing/test1.h"

#include<queue>

using namespace std;

class Simulator;
Simulator* sim = new Simulator();

int main()
{
	//Temporary Initialization Place
	_Topology *Topology = new _Topology();

	scheduleVehicles(Topology, 7200.0);

//    unittest(6000, 6000, Topology);


    sim->StopAt(7200);
    sim->Run();
    cout << "post processing" << endl;
    cout << "ExitQ has " << Topology->ExitQ->Q1.size() << " members";
    cin.get() ;
    
    ofstream fh;
    fh.open("outputfile.txt");
    
    for (int sender = 0; sender<12; sender++)
    {
      for (int receiver = 0; receiver<12; receiver++)
      {
        if (sender!=receiver)
          if (((sender==0 || sender==1 || sender==11) && (receiver==5 || receiver==6 || receiver==7))
            || ((sender==5 || sender==6 || sender==7) && (receiver==0 || receiver==1 || receiver==11)))
            PostProcStats(Topology->ExitQ, 1000,  30, sender, receiver, fh);
      }
    }
    fh.close();
    cin.get();
    
    

    VehicleQueue * Q;
    Intersection * I;

    cout << endl;
    cout <<"missing cars:" << endl;
    cout << endl;

    for (int inter = 0 ; inter<5 ; ++inter)
    {
        for (int direction = 0 ; direction<4 ; ++direction)
        {
            for (int lane = 0 ; lane<2 ; ++lane)
            {
                
                I=Topology->In[inter];
                Q=I->Qu[direction][lane];
                if(Q->Q1.size())
                {
                    cout << Q->Q1.size()<<" Intersection:"<<inter+1<<" Lane:"<<lane<<" Direction:"<<direction<<endl;
                    cout << "   ID: " << Q->Q1.front()->getID() 
                         << " dest: " << Q->Q1.front()->getDestination() 
                         << "start: " << Q->Q1.front()->startTime
						 << "Now: " << sim->getNow()
                         << endl;
    
                }
            }
            
        }
    }
    
    cin.get();

    return 0;
}
