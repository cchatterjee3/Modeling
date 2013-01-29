
#include <iostream>
#include <conio.h>
#include "Simulator.h"
#include "IntersectionwithSignal.h"
#include "IntersectionwoSignal.h"

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
