/* 
 * File:   Structures.h
 * Author: Ivo Correia
 *
 * Created on 12 de Julho de 2011, 12:56
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#define threshold 0.1
#define NO_PARTICLES 10
#define NO_VERTICES 10
#define NO_EDGES 9
#define NO_ACCESS_POINTS 5

#define PI 3.14159265358979323846
#define NEPER 2.71828182845904523536
#define EPSILON 1

#include "Space.h"
#include <cmath>

/* The structures that are used by the localizer, namely information about
 * the vertices, the edges and so on.
 */

typedef struct
{
    point position;
    /* These two arrays will hold the information about the
     * the signal mean and standard deviation to each access
     * point in the map.
     */
    double signalMeans[NO_ACCESS_POINTS];
    double signalSDs[NO_ACCESS_POINTS];
}Vertix;

typedef struct
{
	double width, length;
        Vertix *begin, *end;
}Edge;

typedef struct
{
	point position;
        double strength;
}AccessPoint;

/* A given particle used in the Monte Carlo Localization. */
typedef struct
{
    Edge* edge;
    double d; // The project location of the particle on the edge.
    double offset;
    point position;
    double angle; // The orientation of the particle with respect to the global reference frame.
    double w; // The normalized weight
    double wC; // The map constrained weight of the particle (calculed on the Constraint step).


}Particle;


/* SUPPORT FUNCTIONS*/
double distanceBetweenPoints(point p1, point p2);

#endif	/* STRUCTURES_H */

