/* 
 * File:   Map.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:07
 */

#include "Map.h"
#include <iostream>
#include <cmath>

#define LINEAR 0
#define GAUSSIAN 1

double functionSD = 1;

Map::Map(int nV, int nAP, int w, int h)
{
    noVertices = nV;
    noAccessPoints = nAP;
    width = w;
    height = h;

}

Map::Map(const Map& orig)
{
    
}

Map::~Map()
{

}

/* GETTERS & SETTERS */
Edge *Map::getEdge(int n) { return edges[n]; }
void Map::setEdge(int n, Edge* v) { edges[n] = v;}

Vertix *Map::getVertix(int n) { return vertices[n]; }
void Map::setVertix(int n, Vertix* v) { vertices[n] = v;}

double Map::getWidth() { return width; }
double Map::getHeight() { return height; }

int Map::getNoEdges() { return noEdges;}

void Map::learningPhase()
{
    for (int i = 0; i < NO_VERTICES; i++)
        for (int j = 0; j < NO_ACCESS_POINTS; j++)
        {
            vertices[i]->signalMeans[j] = getSignalStrengthMean(GAUSSIAN,
                    accessPoints[j].strength, distanceBetweenPoints(accessPoints[j].position, vertices[i]->position));

            vertices[i]->signalSDs[j] = getSignalStrengthSD();
        }

    
}

double Map::getSignalStrengthMean(int function, double strength, double distance)
{
    switch(function)
    {
        case LINEAR:
            return -functionSD*distance + strength;
        case GAUSSIAN:
            return (1.0/sqrtf(2*PI*pow(functionSD, 2))*pow(NEPER, -pow(distance, 2)/(2*pow(functionSD, 2))))*strength;
    }
}

double Map::getSignalStrengthSD()
{
    return 0.2;
}