#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "FunctionPrototypes.h"

/* In the adjacency matrix, if the value i,j is different from
 * NULL, then we have a link between node i and node j. In that
 * cell, we will have the information about that edge.
 */
Edge **adjacencyMatrix;

/* Records the information about the vertices. */
Vertix *vertices;

/* Number of vertices in the map. */
int noVertices, noAccessPoints;

/* Used to perform all the mean and standard deviation calculation at a given
 * location.
 */
double *means;
double *sds;

int main(){
	int i, j, nodeOne, nodeTwo;
	double width, length;
	Edge *singleEdge;
	
	/* Reads the number of vertices and allocates enough space for
	 * all the structures. */
	scanf("%d %d", &noVertices, &noAccessPoints);
	
	adjacencyMatrix = (Edge **)malloc(sizeof(Edge *)*noVertices*noVertices);
	vertices = (Vertix *)malloc(sizeof(Vertix)*noVertices);
	
	/* Cleans the working space. */
	for (i = 0; i < noVertices; i++)
		for (j = 0; j < noVertices; j++)
			adjacencyMatrix[i*noVertices + j] = NULL;
	
	/* Reads the rest of the input, namely the information concerning
     * the vertices and the edges.
	 */
	for (i = 0; i < noVertices; i++)
	{
		scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
		/* Allocates the space for holding the signal information
		 * for each vertex.
		 */
		vertices[i].signalMeans = (double *)malloc(sizeof(double)*noAccessPoints);
		vertices[i].signalSDs = (double *)malloc(sizeof(double)*noAccessPoints);
	}

	/* Reads the information about the edges till there is nothing more to read. */
	while(scanf("%d %d %lf %lf", &nodeOne, &nodeTwo, &width, &length) == 4)
	{
		singleEdge = (Edge *)malloc(sizeof(Edge));
		singleEdge->width = width;
		singleEdge->length = length;
		/* It's a two-way connection. */
		adjacencyMatrix[nodeOne*noVertices + nodeTwo] = singleEdge;
		adjacencyMatrix[nodeTwo*noVertices + nodeOne] = singleEdge;
	}
	
	/* Frees the allocated space. */
	freeAdjacencyMatrixAndVertices();
	
	printf("Ended\n");
	return 0;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* Function used to free the allocated space. */
void freeAdjacencyMatrixAndVertices(){
	int i, j;
	
	/* We will only cover the upper triangle of the matrix,
	 * as the pointers in the lower triangle point to the
	 * same structures.
	 */
	for (i = 0; i < noVertices; i++)
		for (j = i + 1; j < noVertices; j++)
			if (adjacencyMatrix[i*noVertices + j] != NULL)
				free(adjacencyMatrix[i*noVertices + j]);
				
	/* The vertices information. */			
	free(vertices);			
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
