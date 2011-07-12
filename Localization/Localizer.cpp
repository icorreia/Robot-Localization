#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "Map.h"
#include "Algorithms.h"
#include "Robot.h"

/* Used to perform all the mean and standard deviation calculation at a given
 * location.
 */
double *means;
double *sds;

int main(){
	int i, j, nodeOne, nodeTwo, noVertices, noAccessPoints;
	double width, length;
	Edge *singleEdge;
        Map *map;
        Algorithms *algorithms;
        
	/* Reads the number of vertices and allocates enough space for
	 * all the structures. */
	scanf("%d %d", &noVertices, &noAccessPoints);

        map = new Map(noVertices, noAccessPoints);
        algorithms = new Algorithms(noAccessPoints, map);


	/* Reads the rest of the input, namely the information concerning
         * the vertices and the edges.
	 */
	/*for (i = 0; i < noVertices; i++)
	{
		scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
		// Allocates the space for holding the signal information
		// for each vertex.
		vertices[i].signalMeans = (double *)malloc(sizeof(double)*noAccessPoints);
		vertices[i].signalSDs = (double *)malloc(sizeof(double)*noAccessPoints);
	}

	// Reads the information about the edges till there is nothing more to read.
	while(scanf("%d %d %lf %lf", &nodeOne, &nodeTwo, &width, &length) == 4)
	{
		singleEdge = (Edge *)malloc(sizeof(Edge));
		singleEdge->width = width;
		singleEdge->length = length;
		// It's a two-way connection.
		adjacencyMatrix[nodeOne*noVertices + nodeTwo] = singleEdge;
		adjacencyMatrix[nodeTwo*noVertices + nodeOne] = singleEdge;
	}
        */

	/* Frees the allocated space. */
        delete map;

	printf("Ended\n");
	return 0;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

