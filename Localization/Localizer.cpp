#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"
#include "RandomNumbers.h"

using namespace std;

void simulation(Robot *robot)
{
    cout << endl << "STARTING SIMULATION...\n";

    for (int i = 0; i < NO_MOVES; i++)
    {
        robot->moveRobot(i);
        //robot->printPosition();
    }
  
}


int main()
{
    point startPoint = {180, 0};
    Robot *robot = new Robot(startPoint, 0);
    //TestBench bench;
    //bench.calculateParticleProbability();

    /* Strats the simulation of the algorithm. */
    simulation(robot);


    delete robot;

    cout << endl << "SIMULATION SUCCESSFULY TERMINATED!\n";

    return 0;
}

/* SUPPORT FUNCTIONS */
double distanceBetweenPoints(point p1, point p2)
{
    double no = sqrtf(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    if (no == 0)
        cout << no << endl;
    return no;
}
