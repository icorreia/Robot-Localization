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
    Map(int nV, int nAP, int w, int h);
    Map(const Map& orig);
    virtual ~Map();

    /* GETTERS & SETTERS */
    Edge *getEdge(int n);
    void setEdge(int n, Edge* v);
    Vertix *getVertix(int n);
    void setVertix(int n, Vertix* v);
    double getWidth();
    double getHeight();
    int getNoEdges();
    

private:
    /* Records the information concerning the edges. */
    Edge *edges[NO_EDGES];

    /* Records the information about the vertices. */
    Vertix *vertices[NO_VERTICES];

    /* Number of vertices in the map. */
    int noVertices, noEdges, noAccessPoints;
    int width, height;

};

#endif	/* MAP_H */

