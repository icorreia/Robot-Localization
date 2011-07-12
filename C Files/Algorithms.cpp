#include "FunctionPrototypes.h"
#include "ExternalVariables.h" 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cmath>
#include <algorithm>
using namespace std;

#define threshold 0.1
#define NO_PARTICLES 10

Particle particles[NO_PARTICLES];

void predict()
{
    
}

void resample()
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

    //TODO: Correct this
    N += int(NO_PARTICLES * min(N*1.0/NO_PARTICLES, max(N*1.0/NO_PARTICLES, wCsum)));

    for (int i = 0; i < N; i++)
    {
        Particle &particle = particles[i];
        //TODO: Correct to prob = P(S| x, y);
        double prob = 0;
        //TODO: Draw (x,y) with probability P(S| x, y).
        particle.wC = particle.w = prob;
        particle.offset = 0;

        particle.edge = findBestEdge(particle);
        calculateNewD(particle);

    }

}

void update()
{

    resample();
}

/* Finds the best edge associated with a given particle.*/
Edge *findBestEdge(Particle &particle)
{
    //TODO: Complete this function.
    
    return NULL;
}

void calculateNewD(Particle &particle)
{
    //TODO: Complete this function.
    particle.d = 0;
}

/* This function must be called numberOfParticles times. */
void constraint()
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

                calculateNewD(particle);

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

void navigation()
{
    
}

int sortParticles(const void *a, const void *b)
{
    const Particle *ia = (const Particle *)a;
    const Particle *ib = (const Particle *)b;
    return ia->wC  - ib->wC;
}

/* Starts at the prediction step when there's new odometry, and then goes one
 * throught the five steps.
 */
void makeAllSteps()
{
    //TODO: Predict
    //TODO: Update
    //TODO: ConstraintIt
    //TODO: Resample
    //TODO: Navigation

}

/* Function executed whenever there's new odometry from the robot. */
void newOdometry()
{
    predict();
    constraint();
}