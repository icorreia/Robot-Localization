/* 
 * File:   Map.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:07
 */

#include "Map.h"
#include <iostream>
#include <cstdio>
#include <cmath>

double functionSD = 1/50.0;

Map::Map(int nV, int nAP, int w, int h)
{
    
    noVertices = nV;
    noAccessPoints = nAP;
    width = w;
    height = h;

    
    buildMapTwo();
    learningPhase();

    
}

/* GETTERS & SETTERS */
Edge *Map::getEdge(int n) { return &edges[n]; }

Vertix *Map::getVertix(int n) { return &vertices[n]; }

double Map::getWidth() { return width; }
double Map::getHeight() { return height; }

int Map::getNoEdges() { return noEdges;}

void Map::learningPhase()
{
    for (int i = 0; i < NO_VERTICES; i++)
    {
        for (int j = 0; j < NO_ACCESS_POINTS; j++)
        {
           vertices[i].signalMeans[j] = getSignalStrengthMean(LINEAR,
                    accessPoints[j].strength, distanceBetweenPoints(accessPoints[j].position, vertices[i].position));

            
            std::cout << vertices[i].signalMeans[j] << " ";

            vertices[i].signalSDs[j] = getSignalStrengthSD();
        }
        std::cout << std::endl;
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
    return 5;
}

double Map::getAccessPointStrength(int n) { return accessPoints[n].strength; }
point Map::getAccessPointPosition(int n) { return accessPoints[n].position; }

void Map::buildMapOne()
{
    /* Map Format
     *
     *  -> 4 accesspoints
     *  -> 6 vertices
     *  -> 5 edges
     *
     *  Units: Meters
     *
     *    --------------------------------- 1500
     *    |                        |      |
     *    |                        |      |
     *    |                 A      |      |  1400
     *    |                        |      |
     *    |                        |      |
     *    |              |----------      | 1000
     *    |              |                |
     *    |              |                |
     *    |        A     |         A      |   650
     *    |              |                |
     *    |              |                |
     *    |              |---------|      |  500
     *    |                        |      |
     *    |                        |      |
     *    |                  A     |      |  150
     *    |                        |      |
     *    --------------------------------- 0
     *   0       500   750  900   1200   1500
     */

    /* Vertices */
    vertices[0].position.x = 1200;
    vertices[0].position.y = 0;
    vertices[1].position.x = 1200;
    vertices[1].position.y = 500;
    vertices[2].position.x = 750;
    vertices[2].position.y = 500;
    vertices[3].position.x = 750;
    vertices[3].position.y = 1000;
    vertices[4].position.x = 1200;
    vertices[4].position.y = 1000;
    vertices[5].position.x = 1200;
    vertices[5].position.y = 1500;

    /* Edges */
    edges[0].width = 5;
    edges[0].length = 500;
    edges[0].begin = &vertices[0];
    edges[0].end = &vertices[1];
    edges[1].width = 5;
    edges[1].length = 450;
    edges[1].begin = &vertices[1];
    edges[1].end = &vertices[2];
    edges[2].width = 5;
    edges[2].length = 500;
    edges[2].begin = &vertices[2];
    edges[2].end = &vertices[3];
    edges[3].width = 5;
    edges[3].length = 450;
    edges[3].begin = &vertices[3];
    edges[3].end = &vertices[4];
    edges[4].width = 5;
    edges[4].length = 500;
    edges[4].begin = &vertices[4];
    edges[4].end = &vertices[5];

    /* Access Points*/
    accessPoints[0].position.x = 900;
    accessPoints[0].position.y = 150;
    accessPoints[0].strength = 60;
    accessPoints[1].position.x = 500;
    accessPoints[1].position.y = 650;
    accessPoints[1].strength = 80;
    accessPoints[2].position.x = 1200;
    accessPoints[2].position.y = 650;
    accessPoints[2].strength = 100;
    accessPoints[3].position.x = 900;
    accessPoints[3].position.y = 1400;
    accessPoints[3].strength = 80;

}


void Map::buildMapTwo()
{
    /* Map Format
     *
     *  -> 4 accesspoints
     *  -> 250 vertices
     *  -> 249 edges
     *
     *  Units: Meters
     *
     *    --------------------------------- 200
     *    |           |                   |
     *    |           |         A         |
     *    |           |                   |
     *    |           |                   |
     *    |           |                   |
     *    |           |                   |
     *    |           |               A   |
     *    |    A      |-------------      |  100
     *    |                        |      |
     *    |                        |      |
     *    |                        |      |
     *    |                        |      |  
     *    |               A        |      |
     *    |                        |      |
     *    |                        |      |  
     *    |                        |      |
     *    --------------------------------- 0
     *   0       130              180    200
     */

    /* Vertices */
    for (int i = 0; i <= 100; i++)
    {
        vertices[i].position.x = 180;
        vertices[i].position.y = i;
    }

    for (int i = 0; i < 50; i++)
    {
        vertices[101 + i].position.x = 179 - i;
        vertices[101 + i].position.y = 100;
    }

    for (int i = 1; i <= 100; i++)
    {
        vertices[150 + i].position.x = 130;
        vertices[150 + i].position.y = 100 + i;
    }
    

    /* Edges */
    for (int i = 0; i < NO_EDGES; i++)
    {
        edges[i].width = 5;
        edges[i].length = 1;
        edges[i].begin = &vertices[i];
        edges[i].end = &vertices[i + 1];
    }

    /* Access Points*/
    accessPoints[0].position.x = 150;
    accessPoints[0].position.y = 50;
    accessPoints[0].strength = -60;
    accessPoints[1].position.x = 70;
    accessPoints[1].position.y = 100;
    accessPoints[1].strength = -80;
    accessPoints[2].position.x = 190;
    accessPoints[2].position.y = 120;
    accessPoints[2].strength = -100;
    accessPoints[3].position.x = 170;
    accessPoints[3].position.y = 180;
    accessPoints[3].strength = -80;

}