#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"
#include "RandomNumbers.h"
#include "TestBench.h"

using namespace std;

void simulation(Robot *robot)
{
    cout << endl << "STARTING SIMULATION...\n";

    for (int i = 0; i < NO_MOVES; i++)
    {

        printf("ITERATION %d\n", i);
        getchar();

        robot->moveRobot(i);
        robot->printPosition();
    }

    cout << endl << "SIMULATION SUCCESSFULY TERMINATED!\n";
}


int main()
{
    point startPoint = {10, 0};
    Robot *robot = new Robot(startPoint, 0);
    //TestBench bench;
    //bench.calculateOffset();

    /* Strats the simulation of the algorithm. */
    simulation(robot);

    delete robot;

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
