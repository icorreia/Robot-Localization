#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"

int main(){
	int i, j, nodeOne, nodeTwo;
	double width, length;
	Edge *singleEdge;
        Map *map;
        Algorithms *algorithms;

        map = new Map(NO_VERTICES, NO_ACCESS_POINTS, 100, 100);
        algorithms = new Algorithms(NO_ACCESS_POINTS, map);


	/* Frees the allocated space. */
        delete map;
        delete algorithms;

	return 0;
}
