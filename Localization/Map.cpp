/* 
 * File:   Map.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:07
 */

#include "Map.h"
#include <iostream>

Map::Map(int nV, int nAP)
{
    noVertices = nV;
    noAccessPoints = nAP;

    /* Initializes the adjacency matrix, as well as the array that will hold the
     * list of vertices.
     */
    //adjacencyMatrix = (Edge **)malloc(sizeof(Edge *)*noVertices*noVertices);
    //vertices = (Vertix *)malloc(sizeof(Vertix)*noVertices);

    /* Cleans the working space. */
    for (int i = 0; i < noVertices; i++)
            for (int j = 0; j < noVertices; j++)
                    adjacencyMatrix[i][j] = NULL;

    

}

Map::Map(const Map& orig)
{
    
}

Map::~Map()
{

}

/* GETTERS & SETTERS */

Edge * Map::getAdjacency(int one, int two) { return adjacencyMatrix[one][two]; }
void Map::setAdjacency(int one, int two, Edge* edge) { adjacencyMatrix[one][two] = edge; }

Vertix *Map::getVertix(int n) { return vertices[n]; }
void Map::setVertix(int n, Vertix* v) { vertices[n] = v;}
