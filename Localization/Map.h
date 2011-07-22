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

    void buildMap();
    void learningPhase();
    double getSignalStrengthMean(int function, double strength, double distance);
    double getSignalStrengthSD();

    /* GETTERS & SETTERS */
    Edge *getEdge(int n);
    Vertix *getVertix(int n);
    double getWidth();
    double getHeight();
    int getNoEdges();
    double getAccessPointStrength(int n);
    point getAccessPointPosition(int n);

private:
    Edge edges[NO_EDGES];
    Vertix vertices[NO_VERTICES];
    AccessPoint accessPoints[NO_ACCESS_POINTS];

    int noVertices, noEdges, noAccessPoints;
    int width, height;

};

#endif	/* MAP_H */

