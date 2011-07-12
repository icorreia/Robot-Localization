/* 
 * File:   Map.h
 * Author: Ivo
 *
 * Created on 12 de Julho de 2011, 13:07
 */

#ifndef MAP_H
#define	MAP_H

#include "Structures.h"

class Map {
public:
    Map(int nV, int nAP);
    Map(const Map& orig);
    virtual ~Map();

    /* GETTERS & SETTERS */
    Edge *getAdjacency(int one, int two);
    void setAdjacency(int one, int two, Edge* edge);

    Vertix *getVertix(int n);
    void setVertix(int n, Vertix* v);
    

private:
    /* In the adjacency matrix, if the value i,j is different from
     * NULL, then we have a link between node i and node j. In that
     * cell, we will have the information about that edge.
     */
    //Edge **adjacencyMatrix;
    Edge *adjacencyMatrix[NO_VERTICES][NO_VERTICES];

    /* Records the information about the vertices. */
    //Vertix *vertices;
    Vertix *vertices[NO_VERTICES];

    /* Number of vertices in the map. */
    int noVertices, noAccessPoints;

};

#endif	/* MAP_H */

