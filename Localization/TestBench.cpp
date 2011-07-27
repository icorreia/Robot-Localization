/* 
 * File:   TestBench.cpp
 * Author: Ivo
 * 
 * Created on 23 de Julho de 2011, 10:10
 */

#include "TestBench.h"
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double TestBench::calculateParticleProbability()
{
    double accumulatedProb = 1, prob = 0;

    /* If the signal strength hasn't been registered yet (i.e, Si = 0),
     * we simply ignore it.
     */
    double signalStrength = -50;
    double mean = -50, sd = -10;

    /* See the formula on the second page of the paper. */
    double p, q, r;

    point particle = {0, 0};
    point accessPoint = {100, 0};

    p = 2*EPSILON/(sqrtf(2*PI)*distanceBetweenPoints(particle, accessPoint));
    q = pow(signalStrength - mean, 2);
    r = 2*pow(sd,2);
    prob = pow(p,q/r);

    printf("%lf %lf %lf\n", p, q, r);

    cout << "Returning " << prob << " has " << exp(q/r) << endl;

    return accumulatedProb;
}


double TestBench::calculateOffset()
{
    
    Edge edges[3];
    Vertix vertices[4];
    Particle particle;

    vertices[0].position.x = 0;
    vertices[0].position.y = 0;
    vertices[1].position.x = 2;
    vertices[1].position.y = 0;
    vertices[2].position.x = 4;
    vertices[2].position.y = 0;
    vertices[3].position.x = 6;
    vertices[3].position.y = 0;

    edges[0].begin = &vertices[0];
    edges[0].end = &vertices[1];
    edges[0].length = 2;
    edges[0].width = 2;
    edges[1].begin = &vertices[1];
    edges[1].end = &vertices[2];
    edges[1].length = 2;
    edges[1].width = 2;
    edges[2].begin = &vertices[2];
    edges[2].end = &vertices[3];
    edges[2].length = 2;
    edges[2].width = 2;

    particle.position.x = 4.2;
    particle.position.y = 2;

    point intersection = calculateIntersectionPoint(particle, &edges[0]);
    vector offsetVector = intersection - particle.position;
    double offset1 = sqrtf(offsetVector*offsetVector);

    intersection = calculateIntersectionPoint(particle, &edges[1]);
    offsetVector = intersection - particle.position;
    double offset2 = sqrtf(offsetVector*offsetVector);

    intersection = calculateIntersectionPoint(particle, &edges[2]);
    offsetVector = intersection - particle.position;
    double offset3 = sqrtf(offsetVector*offsetVector);

    printf("We have %lf %lf %lf\n", offset1, offset2, offset3);

    return 0;
}


point TestBench::calculateIntersectionPoint(Particle &particle, Edge *edge)
{
    vector v = edge->end->position - edge->begin->position;
    vector w = particle.position - edge->begin->position;

    double c1 = w*v;
    if ( c1 <= 0 )
        return edge->begin->position;

    double c2 = v*v;
    if ( c2 <= c1 )
        return edge->end->position;

    return edge->begin->position + (c1 / c2) * v;
}