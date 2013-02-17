#pragma once

//#define test

#define test
#include <iostream>
//#include "../Topology.h"

/*
#event types ::

1. contructor               CNS
2. Join Queue               JQU
3. join Q Scheduled         JQC
4. Pass                     PSS
5. Pass Scheduled           PSC       
6. Departure                DEP        
7. Departure Scheduled      DPC
8. Waiting light            WTL
9. waiting Busy Intersection WTB
10. Full next Queue         WTQ
11. Reaching Destination    RDT

*/

enum {CNS, JQU, JQC, PSS, PSC, DEP, DPC, WTL, WTB, WTQ, RDT};

struct eventDsc
{
    int type;
    int InterID;
    int QDir;
    int QLane;
    int QSize;
    double timetag;
};

class _Topology;

void unittest(int numVeh, double time_interval, _Topology* Topology);

void PrintEventDsc(eventDsc E1);

void PrintEventList(VehicleClass* V1);
