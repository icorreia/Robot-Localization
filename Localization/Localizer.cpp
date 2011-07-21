#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"

using namespace std;

Map *map;
Algorithms *algorithms;
Robot *robot;

void simulation()
{

    for (int i = 0; i < NO_MOVES; i++)
    {
        robot->moveRobot(i);
        //robot->printPosition();
        algorithms->update();
    }

    
}


int main()
{
        map = new Map(NO_VERTICES, NO_ACCESS_POINTS, 1500, 1500);
        algorithms = new Algorithms(NO_ACCESS_POINTS, map);
        point startPoint = {1200, 0};
        vector startDirection = {0, 1};
        robot = new Robot(startPoint, startDirection);

        /* Strats the simulation of the algorithm. */
        simulation();

	/* Frees the allocated space. */
        delete map;
        delete algorithms;

        cout << endl << "SIMULATION SUCCESSFULY TERMINATED!\n";

	return 0;
}

/* SUPPORT FUNCTIONS */
double distanceBetweenPoints(point p1, point p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }
