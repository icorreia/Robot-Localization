/* 
 * File:   Structures.h
 * Author: Ivo Correia
 *
 * Created on 12 de Julho de 2011, 12:56
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#define threshold 0.1
#define NO_PARTICLES 121
#define NO_VERTICES 21
#define NO_EDGES 20
#define NO_ACCESS_POINTS 4
#define N_MAX 20
#define N_MIN 5
#define MAP_HEIGHT 20
#define MAP_WIDTH 20
#define NORMALIZATION_CONSTANT 0.1
#define NO_MOVES 40

#define LINEAR 0
#define GAUSSIAN 1

#define PI 3.14159265358979323846
#define NEPER 2.71828182845904523536
#define EPSILON 1

#include "Space.h"
#include <cmath>


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

        int id;
}Edge;

typedef struct
{
	point position;
        double strength;
}AccessPoint;


typedef struct
{
    Edge* edge;
    double d; // The project location of the particle on the edge.
    double offset;
    point position;
    double angle; // The orientation of the particle with respect to the global reference frame.
    double w; // The normalized weight
    double wC; // The map constrained weight of the particle (calculed on the Constraint step).

    /* TODO: Debug purposes only. */
    int id;

    /* Used to perform all the mean and standard deviation calculation at a given
     * location.
     */
    double means[NO_ACCESS_POINTS];
    double sds[NO_ACCESS_POINTS];

}Particle;

/* These variables should be seen as the rotation the robot will take and how
 * much it will advance in the x and y direction.
 */
typedef struct
{
    double x, y;
    double rotation;
}Move;


/* SUPPORT FUNCTIONS*/
double distanceBetweenPoints(point p1, point p2);

#endif	/* STRUCTURES_H */

