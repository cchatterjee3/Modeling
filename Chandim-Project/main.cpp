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
    
    ofstream fh0("CollectedData//1_5.csv", fstream::app), fh1("CollectedData//1_6.csv", fstream::app), fh2("CollectedData//1_7.csv", fstream::app), fh3("CollectedData//0_5.csv", fstream::app),
    fh4("CollectedData//0_6.csv", fstream::app), fh5("CollectedData//0_7.csv", fstream::app), fh6("CollectedData//11_5.csv", fstream::app), fh7("CollectedData//11_6.csv", fstream::app), 
    fh8("CollectedData//11_7.csv", fstream::app), fh9("CollectedData//5_1.csv", fstream::app), fh10("CollectedData//5_0.csv", fstream::app), fh11("CollectedData//5_11.csv", fstream::app), 
    fh12("CollectedData//6_1.csv", fstream::app), fh13("CollectedData//6_0.csv", fstream::app), fh14("CollectedData//6_11.csv", fstream::app), fh15("CollectedData//7_1.csv", fstream::app), 
    fh16("CollectedData//7_0.csv", fstream::app), fh17("CollectedData//7_11.csv", fstream::app);
    
    
    /*for (int sender = 0; sender<12; sender++)
    {
      for (int receiver = 0; receiver<12; receiver++)
      {
        if (sender!=receiver)
          if (((sender==0 || sender==1 || sender==11) && (receiver==5 || receiver==6 || receiver==7))
            || ((sender==5 || sender==6 || sender==7) && (receiver==0 || receiver==1 || receiver==11)))
            PostProcStats(Topology->ExitQ, 1000,  30, sender, receiver, fh);
      }
    }*/
    
    PostProcStats(Topology->ExitQ, 1000,  30, 1, 5, fh0);
    PostProcStats(Topology->ExitQ, 1000,  30, 1, 6, fh1);
    PostProcStats(Topology->ExitQ, 1000,  30, 1, 7, fh2);
    PostProcStats(Topology->ExitQ, 1000,  30, 0, 5, fh3);
    PostProcStats(Topology->ExitQ, 1000,  30, 0, 6, fh4);
    PostProcStats(Topology->ExitQ, 1000,  30, 0, 7, fh5);
    PostProcStats(Topology->ExitQ, 1000,  30, 11, 5, fh6);
    PostProcStats(Topology->ExitQ, 1000,  30, 11, 6, fh7);
    PostProcStats(Topology->ExitQ, 1000,  30, 11, 7, fh8);
    PostProcStats(Topology->ExitQ, 1000,  30, 5, 1, fh9);
    PostProcStats(Topology->ExitQ, 1000,  30, 5, 0, fh10);
    PostProcStats(Topology->ExitQ, 1000,  30, 5, 11, fh11);
    PostProcStats(Topology->ExitQ, 1000,  30, 6, 1, fh12);
    PostProcStats(Topology->ExitQ, 1000,  30, 6, 0, fh13);
    PostProcStats(Topology->ExitQ, 1000,  30, 6, 11, fh14);
    PostProcStats(Topology->ExitQ, 1000,  30, 7, 1, fh15);
    PostProcStats(Topology->ExitQ, 1000,  30, 7, 0, fh16);
    PostProcStats(Topology->ExitQ, 1000,  30, 7, 11, fh17);
    
    fh0.close();
    fh1.close();
    fh2.close();
    fh3.close();
    fh4.close();
    fh5.close();
    fh6.close();
    fh7.close();
    fh8.close();
    fh9.close();
    fh10.close();
    fh11.close();
    fh12.close();
    fh13.close();
    fh14.close();
    fh15.close();
    fh16.close();
    fh17.close();
    
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
