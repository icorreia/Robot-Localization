#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"

void simulation()
{
    
}


int main(){
	Map *map;
        Algorithms *algorithms;

        map = new Map(NO_VERTICES, NO_ACCESS_POINTS, 100, 100);
        algorithms = new Algorithms(NO_ACCESS_POINTS, map);

        /* Strats the simulation of the algorithm. */
        simulation();

	/* Frees the allocated space. */
        delete map;
        delete algorithms;

	return 0;
}

/* SUPPORT FUNCTIONS */
double distanceBetweenPoints(point p1, point p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }
