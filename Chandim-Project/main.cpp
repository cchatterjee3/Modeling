
#include <iostream>
#include <conio.h>
#include "Simulator.h"

using namespace std;

class Simulator;
extern Simulator* sim = new Simulator();

int main()
{
    //sim = new Simulator();
    sim->StopAt(100);
    getch();
    return 0;
}
