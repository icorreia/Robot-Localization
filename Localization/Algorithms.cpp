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
#include <cstdio>

using namespace std;

Algorithms::Algorithms(int nAP, RandomNumbers *rG)
{
    noAccessPoints = nAP;
    randGenerator = rG;

    map = new Map(NO_VERTICES, NO_ACCESS_POINTS, MAP_WIDTH, MAP_HEIGHT);

    /* Initializes all the particles on the map. */
    particlesGenerator();
}

Algorithms::~Algorithms()
{
    delete map;
}

void Algorithms::particlesGenerator()
{
    double width = map->getWidth(), height = map->getHeight();

    for (int i = 0; i < NO_PARTICLES; i++)
    {

        particles[i].position.x = randGenerator->uniform(0, width);
        particles[i].position.y = randGenerator->uniform(0, height);

        particles[i].edge = findBestEdge(particles[i]);
        updateDistance(particles[i]);
        particles[i].offset = calculateOffset(particles[i], particles[i].edge);

        particles[i].angle = PI/2;
        particles[i].w = 1.0/NO_PARTICLES;
        particles[i].wC = 0;

        particles[i].id = i;

        /* Calculate the signal strength mean and standard deviation vectors
         * for this given particle.
         */
        calculateSignalStrengthVectors(particles[i]);

    }
}

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

    constraint();
}

void Algorithms::constraint()
{
    double wCsum = 0;

    for (int i = 0; i < NO_PARTICLES; i++)
    {
        Particle &particle = particles[i];
        Edge *edge = particle.edge;
        double fr = particle.d/edge->length;

        if (fr > 1.0 - threshold || fr < threshold)
        {
            Edge *newEdge = findBestEdge(particle);

            /* Updates the new edge associated with this particle, as well
             * as all the other information associated with, namely the distance
             * to the origin of the edge and the offset. */
            if (newEdge != edge)
            {
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

/* Finds the best edge associated with a given particle.*/
Edge* Algorithms::findBestEdge(Particle &particle)
{
    /* The best associated edge of a given particle is the one that presents
     * the smaller offset.
     */
    double minOffset = -1;
    Edge *bestEdge;

    for (int i = 0; i < NO_EDGES; i++)
    {
        Edge *edge = map->getEdge(i);
        double offset = calculateOffset(particle, edge);

        if (offset < minOffset || minOffset == -1)
        {
            minOffset = offset;
            bestEdge = edge;
        }
    }

    return bestEdge;
}

void Algorithms::update()
{
    for (int i = 0; i < NO_PARTICLES; i++)
        particles[i].w = calculateParticleProbability(&particles[i]);

    resample();
}

/* Calculates the mean and standard deviation, page 2, equation (1) and (2). */
void Algorithms::calculateSignalStrengthVectors(Particle &particle)
{
    double firstDist, secondDist, distVertices;
    point p = particle.position;
    Vertix *v1 = particle.edge->begin, *v2 = particle.edge->end;
    
    firstDist = distanceBetweenPoints(p, v1->position);
    secondDist = distanceBetweenPoints(p, v2->position);
    distVertices = distanceBetweenPoints(v1->position, v2->position);

    /* For each component (from 1 to the number of access points),
     * we calculate the array of means and standard deviations, as
     * described by the formulas (1) and (2) on the second page of
     * the paper.
     */

    
    for (int i = 0; i < noAccessPoints; i++)
    {
        particle.means[i] = (firstDist*(v1->signalMeans[i]) + secondDist*(v2->signalMeans[i]))/(distVertices);
        particle.sds[i] = (firstDist*(v1->signalSDs[i]) + secondDist*(v2->signalSDs[i]))/(distVertices);
    }

    return;
}

/* By increasing order of wC. */
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

        wCsum += particle.wC;
    }

    N += int(NO_PARTICLES * min(N_MAX*1.0/NO_PARTICLES, max(N_MIN*1.0/NO_PARTICLES, wCsum)));

    /* Just to make sure... */
    if (N > NO_PARTICLES)
        N = NO_PARTICLES;

    cout << "We are going to resample " << N << endl;

    for (int i = 0; i < N; i++)
    {
        Particle &particle = particles[i];
        double xLowerBound, yLowerBound, xUpperBound, yUpperBound;
        
        /* If we have already defined the current particle, we can use it's
         * location. Otherwise, the resample will be completely random across
         * the whole map.
         */
        if (currentParticle != NULL)
        {
            /* Sets the location of the new particles to an area surrounding the
             * current particle location, bounded within the RESAMPLE_RANGE.
             * This way, we try to assure that the new particles will stick
             * close to the current assumed position of the robot.
             */

            xLowerBound = max(0.0, currentParticle->position.x - RESAMPLE_RANGE);
            yLowerBound = max(0.0, currentParticle->position.y - RESAMPLE_RANGE);
            xUpperBound = min(MAP_WIDTH*1.0, currentParticle->position.x + RESAMPLE_RANGE);
            yUpperBound = min(MAP_HEIGHT*1.0, currentParticle->position.y + RESAMPLE_RANGE);
            
        } else
        {
            xLowerBound = 0.0;
            yLowerBound = 0.0;
            xUpperBound = MAP_WIDTH;
            yUpperBound = MAP_HEIGHT;
        }

        particle.position.x = randGenerator->uniform(xLowerBound, xUpperBound);
        particle.position.y = randGenerator->uniform(yLowerBound, yUpperBound);

        particle.edge = findBestEdge(particle);
        updateDistance(particle);
        particle.offset = calculateOffset(particle, particle.edge);
        
        particle.wC = particle.w = calculateParticleProbability(&particle);

        /* Refresh the values in the vectors. */
        calculateSignalStrengthVectors(particles[i]);
    }


    /* At the end, we have to update the current location belief.*/
    //locationBelief();
}

double Algorithms::calculateParticleProbability(Particle *particle)
{
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
                    map->getAccessPointStrength(i), distanceBetweenPoints(map->getAccessPointPosition(i), particle->position));
        if (signalStrength == 0.0)
            continue;

        /* See the formula on the second page of the paper. */
        double p, q, r;

        p = 2*EPSILON/(sqrtf(2*PI)*distanceBetweenPoints(particle->position, map->getAccessPointPosition(i)));
        q = pow(signalStrength - particle->means[i], 2);
        r = 2*pow(particle->sds[i], 2);
        prob = pow(p,q/r);

        //TODO: printf("%lf %lf %lf\n", p, q, r);
        if (prob != 0)
        {
            accumulatedProb *= prob;
            isNotNull = true;
        }
    }

    if (isNotNull)
    {
        //TODO: Debug: if (accumulatedProb > 0.5)
        //    cout << "Returning " << accumulatedProb << endl;
        return accumulatedProb;
    }

    return 0;
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

void Algorithms::locationBelief(Particle &particle)
{
    /* We know that the particles are ordered by increasing weights. Therefore,
     * the particle with the highest weight and consequently, the particle
     * holding the most likely position of the robot will be standing at the
     * end of the particle set.
     */
    currentParticle = &particles[NO_PARTICLES - 1];


    return;
    //DEBUG PRINT
    cout << "The best particle (no: " << particles[NO_PARTICLES-1].id << ")goes for x: " << particles[NO_PARTICLES-1].position.x
            << " and y: " << particles[NO_PARTICLES-1].position.y << endl;

    if (currentParticle != NULL)
    {
        
        double dist, minDist = distanceBetweenPoints(particles[0].position, particle.position);
        int no = 0;
        for (int i = 1; i < NO_PARTICLES; i++)
        {
            dist = distanceBetweenPoints(particles[i].position, particle.position);
            if (dist < minDist)
            {
                no = i;
                minDist = dist;
            }
        }

        printf("ID: %d (%lf,%lf) against ID: %d (%lf,%lf) with DIST: %lf\n",
                currentParticle->id, currentParticle->position.x, currentParticle->position.y,
                no, particles[no].position.x, particles[no].position.y, minDist);
        printf("PROBS: %lf against %lf\n", particles[NO_PARTICLES-1].w, particles[no].w);
    }
    
}
