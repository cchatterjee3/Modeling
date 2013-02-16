#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "../Topology.h"
#include "../Intersection.h"
#include "../CommonDefs.h"
#include "../VehicleQueue.h"
#include "../Simulator.h"
#include "../RandomNum.h"

void unittest(int numVeh, double time_interval, _Topology* Topology)
{

    RandomNumGen ran2(0);
    int IDCounter=0;
    
    int interID;
    int sdest;
    int fdest;
    int inputDir;
    int inputLane;
    int QDir;
    int QLane;
    double timetag;
    
    Intersection* Inter;
    VehicleClass* vehicle;
    VehicleQueue* joinqueue;
    
    for (int i=0 ; i<numVeh ; ++i)
    {
        //getting random quantities
        sdest  =(int) (floor(ran2.Next()*12));
        do
        {
            fdest  =(int) (floor(ran2.Next()*12));
        } while(fdest==sdest);
        timetag=(ran2.Next()*time_interval);
        
        switch(sdest)
        {
            case 0:
            case 1:
            case 11:
                interID=1;
                break;
            case 2:
            case 10:
                interID=2;
                break;
            case 3:
            case 9:
                interID=3;
                break;
            case 4:
            case 8:
                interID=4;
                break;
            case 5:
            case 6:
            case 7:
                interID=5;
                break;
            default:
                printf("error!\n");
        }

        if(sdest>0 && sdest<6)
            QDir=1;
        else if(sdest>6 && sdest<12)
            QDir=3;
        else if(sdest==0)
            QDir=0;
        else if(sdest==6)
            QDir=2;
        else
            printf("error\n");
        
        Inter=Topology->In[interID-1];
        dir globaldir = Inter->routingtable[fdest];
        int Turn = turn(globaldir, QDir);
        if(Turn==0 || Turn==1)
            QLane=0;
        else
            QLane=1;
        
        vehicle=new VehicleClass(++IDCounter, sdest, fdest, timetag);
        joinqueue = Inter->Qu[QDir][QLane];
        sim->Schedule(timetag, &Intersection::addVehicletoQueue, Inter, joinqueue, vehicle);

    }
}
