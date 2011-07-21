/* 
 * File:   Algorithms.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 12:55
 */

#include "Algorithms.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

/* CONSTRUCTORS & DESTRUCTORS */
Algorithms::Algorithms(int nAP, RandomNumbers *rG)
{
    noAccessPoints = nAP;
    randGenerator = rG;

    map = new Map(NO_VERTICES, NO_ACCESS_POINTS, 1500, 1500);

    /* Initializes all the particles on the map. */
    particlesGenerator();
}

Algorithms::~Algorithms()
{
    delete map;
}

/* ALGORITHM */
void Algorithms::predict(double xMotionIncrease, double yMotionIncrease, double angleIncrease)
{
    for (int i = 0; i < NO_PARTICLES; i++)
    {
        particles[i].angle += angleIncrease;
        particles[i].position.x += xMotionIncrease;
        particles[i].position.y += yMotionIncrease;
        particles[i].offset = calculateOffset(particles[i], particles[i].edge);
        updateDistance(particles[i]);
    }
}


void Algorithms::update()
{
    for (int i = 0; i < NO_PARTICLES; i++)
    {
        particles[i].w = conditionalProbCalc(particles[i]);
    }

    constraint();
    resample();
}

/* This function must be called numberOfParticles times. */
void Algorithms::constraint()
{
    double wCsum = 0;

    /* Goes throught all the particles. */
    for (int i = 0; i < NO_PARTICLES; i++)
    {
        Particle &particle = particles[i];
        Edge *edge = particle.edge;
        double fr = particle.d/edge->length;

        if (fr > 1.0 - threshold || fr < threshold)
        {
            Edge *newEdge = findBestEdge(particle);

            if (newEdge != edge)
            {
                /* Updates the new edge associated with this particle. */
                edge = particle.edge = newEdge;

                updateDistance(particle);

                particle.offset = 0;
            }
        }

        if (abs(particle.offset) > edge->width)
            particle.wC = particle.w*pow(exp(-abs(particle.offset) - edge->width/2),2);
        else
            particle.wC = particle.w;

        wCsum += particle.wC;

    }

    /* Now, normalizes the weights wC.*/
    for (int i = 0; i < NO_PARTICLES; i++)
        particles[i].wC /= wCsum;

}


int sortParticles(const void *a, const void *b)
{
    const Particle *ia = (const Particle *)a;
    const Particle *ib = (const Particle *)b;
    return ia->wC  - ib->wC;
}

void Algorithms::resample()
{
    int N = 0;
    double wCsum = 0;

    qsort(particles, NO_PARTICLES, sizeof(Particle), sortParticles);

    for (int i = 0; i < NO_PARTICLES; i++)
    {
        Particle &particle = particles[i];

        /* We have sorted the particles before, so the wCmin will belong to the
         * first particle of the set.
         */
        if (particle.wC < particles[0].wC)
            N++;

        /* Performs the calculation of the sum of all wC's. */
        wCsum += particle.wC;
    }

    N += int(NO_PARTICLES * min(N_MAX*1.0/NO_PARTICLES, max(N_MIN*1.0/NO_PARTICLES, wCsum)));

    /* Just to make sure... */
    if (N > NO_PARTICLES)
        N = NO_PARTICLES;
    
    for (int i = 0; i < N; i++)
    {
        Particle &particle = particles[i];
        //TODO: Draw (x,y) with probability P(S| x, y).
        particle.wC = particle.w = conditionalProbCalc(particle);
        particle.offset = 0;

        particle.edge = findBestEdge(particle);
        updateDistance(particle);

    }

}

/* Calculates the mean and standard deviation, page 2, equation (1) and (2). */
void Algorithms::estimator(Particle &particle)
{
    double firstDist, secondDist, distVertices;
    Vertix *v1 = particle.edge->begin, *v2 = particle.edge->end;
    int i;
    point p = particle.position;

    firstDist = distanceBetweenPoints(p, v1->position);
    secondDist = distanceBetweenPoints(p, v2->position);
    distVertices = distanceBetweenPoints(v1->position, v2->position);

    /* For each component (from 1 to the number of access points),
     * we calculate the array of means and standard deviations, as
     * described by the formulas (1) and (2) on the second page of
     * the paper.
     */
    for (i = 0; i < noAccessPoints; i++)
    {
        /* Then, updates the current values. */
        means[i] = (firstDist*(v1->signalMeans[i]) + secondDist*(v2->signalMeans[i]))/(distVertices);
        sds[i] = (firstDist*(v1->signalSDs[i]) + secondDist*(v2->signalSDs[i]))/(distVertices);;
    }

    return;
}



//TODO: Signal strengths must be calculated.
double Algorithms::conditionalProbCalc(Particle &particle)
{
    /* First, calculates the vectors related to signal strength. */
    estimator(particle);

    /* We use this variable because if all the parcels
     * are zero, than we will return 1 and that is
     * not correct.
     */
    bool isNotNull = false;
    double accumulatedProb = 1, prob = 0;

    for (int i = 0; i < noAccessPoints; i++)
    {
        /* If the signal strength hasn't been registered yet (i.e, Si = 0),
         * we simply ignore it.
         */
        double signalStrength = map->getSignalStrengthMean(LINEAR,
                    map->getAccessPointStrength(i), distanceBetweenPoints(map->getAccessPointPosition(i), particle.position));;
        if (signalStrength == 0.0)
            continue;

        /* See the formula on the second page of the paper. */
        double parcelOne, parcelTwo, parcelThree;
        double dX = 1;
        /*TODO: Check parcel one.*/
        parcelOne = 2*EPSILON/(sqrtf(2*PI)*dX);
        parcelTwo = pow(signalStrength - means[i], 2);
        parcelThree = 2*pow(sds[i], 2);
        prob = parcelOne*exp(parcelTwo/parcelThree);

        if (prob != 0)
        {
            accumulatedProb *= prob;
            isNotNull = true;
        }
    }

    if (isNotNull)
        return accumulatedProb;
    
    return 0;
}


/* SUPPORT METHODS */

/* Finds the best edge associated with a given particle.*/
Edge* Algorithms::findBestEdge(Particle &particle)
{
    /* The best associated edge of a given particle is the one that presents
     * the smaller offset.
     */
    double minOffset = -1;
    Edge *bestEdge;

    /* Goes throught all the edges and finds the min offset. */
    for (int i = 0; i < NO_EDGES; i++)
    {
        Edge *edge = map->getEdge(i);
        double offset = calculateOffset(particle, edge);

        if (offset < minOffset | minOffset == -1)
        {
            minOffset = offset;
            bestEdge = edge;
        }
    }

    return bestEdge;
}

double Algorithms::calculateOffset(Particle &particle, Edge *edge)
{
    point intersection = calculateIntersectionPoint(particle, edge);
    
    vector offsetVector = intersection - particle.position;
    double offset = sqrtf(offsetVector*offsetVector);

    return offset;
}

/* This method should only be called after updating the edge best associated
 * with this particle.
 */
void Algorithms::updateDistance(Particle &particle)
{
    point intersection = calculateIntersectionPoint(particle, particle.edge);

    vector dVector = intersection - particle.edge->begin->position;
    particle.d = sqrtf(dVector*dVector);

}

/* See: http://softsurfer.com/Archive/algorithm_0102/algorithm_0102.htm
 *  or: http://paulbourke.net/geometry/pointline/
 */
point Algorithms::calculateIntersectionPoint(Particle &particle, Edge *edge)
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

void Algorithms::locationBelief()
{
    double integral = 0;
    double outcome = 0;

    /* Calculate the integral. */
    for (int i = 0; i <= MAP_WEIGHT; i++)
        for (int i = 0; i <= MAP_HEIGHT; i++)
            integral += 0;

    
}

/* Method to generate all the particles. */
void Algorithms::particlesGenerator()
{
    double width = map->getWidth(), height = map->getHeight();

    for (int i = 0; i < NO_PARTICLES; i++)
    {
        
        particles[i].position.x = randGenerator->uniform(0, width);
        particles[i].position.y = randGenerator->uniform(0, height);

        particles[i].edge = findBestEdge(particles[i]);
        updateDistance(particles[i]);

        particles[i].angle = PI/2;
        particles[i].w = conditionalProbCalc(particles[i]);
        particles[i].wC = 0;

    }
}