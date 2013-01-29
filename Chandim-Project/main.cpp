
#include <iostream>
#include <conio.h>
#include "Simulator.h"
<<<<<<< HEAD
#include "Topology.h"
=======
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"
>>>>>>> 93ee5eea49a9a2ad2de3187ff3497fb2c36d760f

using namespace std;

//class Simulator;
extern Simulator* sim = new Simulator();

int main()
{
    //sim = new Simulator();
    sim->StopAt(100);
    getch();
    return 0;
}
