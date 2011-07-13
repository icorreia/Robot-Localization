/* 
 * File:   Map.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:07
 */

#include "Map.h"
#include <iostream>

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