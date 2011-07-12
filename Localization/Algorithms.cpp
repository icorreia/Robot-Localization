/* 
 * File:   Algorithms.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 12:55
 */

#include "Algorithms.h"
#include <algorithm>
#include <cmath>
using namespace std;

/* CONSTRUCTORS & DESTRUCTORS */
Algorithms::Algorithms(int nAP, Map *m)
{
    noAccessPoints = nAP;
    map = m;
}

Algorithms::Algorithms(const Algorithms& orig)
{
}

Algorithms::~Algorithms()
{
}

/* ALGORITHM */
void Algorithms::predict()
{

}


void Algorithms::update()
{

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

/* Calculates the mean and standard deviation, page 2, equation (1) and (2). */
void Algorithms::estimator(double lX, double lY, int vertexOne, int vertexTwo)
{
	double firstDist, secondDist,distVertices;
        Vertix *v1 = map->getVertix(vertexOne), *v2 = map->getVertix(vertexTwo);
	int i;

	firstDist = distance(lX, lY, v1->x, v1->y);
	secondDist = distance(lX, lY, v2->x, v2->y);
	distVertices = distance(v1->x, v1->y, v2->x, v2->y);

	/* Allocates the space for the vectors containing the means
	 * and standard deviations at the current position.
	 */
	double *means = (double *)malloc(sizeof(double)*noAccessPoints);
	double *sds = (double *)malloc(sizeof(double)*noAccessPoints);

	/* For each component (from 1 to the number of access points),
	 * we calculate the array of means and standard deviations, as
	 * described by the formulas (1) and (2) on the second page of
	 * the paper.
	 */
	for (i = 0; i < noAccessPoints; i++)
        {
		means[i] = (firstDist*(v1->signalMeans[i]) + secondDist*(v2->signalMeans[i]))/(distVertices);
		sds[i] = (firstDist*(v1->signalSDs[i]) + secondDist*(v2->signalSDs[i]))/(distVertices);;
	}

        return;

}



//TODO: Signal strengths must be calculated.
double Algorithms::conditionalProbCalc(double *means, double *sds, double *signalStrengths)
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
        if (signalStrengths[i] == 0.0)
            continue;

        /* See the formula on the second page of the paper. */
        double parcelOne, parcelTwo, parcelThree;
        double dX = 1;
        /*TODO: Check parcel one.*/
        parcelOne = 2*EPSILON/(sqrtf(2*PI)*dX);
        parcelTwo = pow(signalStrengths[i] - means[i], 2);
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
double Algorithms::distance(double x, double y, double x2, double y2)
{
    return sqrt(pow(x - x2, 2) + pow(y - y2, 2));
}

/* Finds the best edge associated with a given particle.*/
Edge* Algorithms::findBestEdge(Particle &particle)
{
    //TODO: Complete this function.

    return NULL;
}

void Algorithms::calculateNewD(Particle &particle)
{
    //TODO: Complete this function.
    particle.d = 0;
}