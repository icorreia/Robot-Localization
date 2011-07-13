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

using namespace std;

/* CONSTRUCTORS & DESTRUCTORS */
Algorithms::Algorithms(int nAP, Map *m)
{
    noAccessPoints = nAP;
    map = m;

    /* Initializes all the particles on the map. */
    particlesGenerator();
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

                updateDistances(particle);

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
        updateDistances(particle);

    }

}

/* Calculates the mean and standard deviation, page 2, equation (1) and (2). */
void Algorithms::estimator(point p, Edge *edge)
{
	double firstDist, secondDist, distVertices;
        Vertix *v1 = edge->begin, *v2 = edge->end;
	int i;

	firstDist = distance(p, v1->position);
	secondDist = distance(p, v2->position);
	distVertices = distance(v1->position, v2->position);

	/* For each component (from 1 to the number of access points),
	 * we calculate the array of means and standard deviations, as
	 * described by the formulas (1) and (2) on the second page of
	 * the paper.
	 */
	for (i = 0; i < noAccessPoints; i++)
        {
            /* First, saves the previous values.*/
            previousMeans[i] = currentMeans[i];
            previousSds[i] = currentSds[i];
            /* Then, updates the current values. */
            currentMeans[i] = (firstDist*(v1->signalMeans[i]) + secondDist*(v2->signalMeans[i]))/(distVertices);
            currentSds[i] = (firstDist*(v1->signalSDs[i]) + secondDist*(v2->signalSDs[i]))/(distVertices);;
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
double Algorithms::distance(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/* Finds the best edge associated with a given particle.*/
Edge* Algorithms::findBestEdge(Particle &particle)
{
    /* The best associated edge of a given particle is the one that presents
     * the smaller offset.
     */
    double minOffset = -1;
    Edge *bestEdge;

    /* Goes throught all the edges and finds the min offset. */
    for (int i = 0; i < map->getNoEdges(); i++)
    {
        Edge *edge = map->getEdge(i);
        
        double x1 = edge->begin->position.x;
        double x2 = edge->end->position.x;
        double y1 = edge->begin->position.y;
        double y2 = edge->end->position.y;

        vector u = edge->end->position - edge->begin->position;

        u.x *= (x2 - x1);
        u.y *= (y2 - y1);

        /* Now, we have the intersection point. */
        
        point intersection = particle.edge->begin->position + u;
        vector offsetVector = intersection - particle.position;
        double offset = sqrtf(offsetVector*offsetVector);

        if (offset < minOffset | minOffset == -1)
        {
            minOffset = offset;
            bestEdge = edge;
        }
    }

    return bestEdge;
}

/* This method should only be called after updating the edge best associated
 * with this particle.
 * See: http://paulbourke.net/geometry/pointline/
 */
void Algorithms::updateDistances(Particle &particle)
{
    double x1 = particle.edge->begin->position.x;
    double x2 = particle.edge->end->position.x;
    double y1 = particle.edge->begin->position.y;
    double y2 = particle.edge->end->position.y;

    vector u = particle.edge->end->position - particle.edge->begin->position;
    u.x *= (x2 - x1);
    u.y *= (y2 - y1);
    /* Now, we have the intersection point. */
    point intersection = particle.edge->begin->position + u;
    /* To update the distances, namely the offset of the particle to the edge
     * as well as the value of d, we have to use the distance between the
     * intersection point calculated above and the beginning of the edge and
     * the coordinates of the particle.
     */
    vector dVector = intersection - particle.edge->begin->position;
    vector offsetVector = intersection - particle.position;
    particle.d = sqrtf(dVector*dVector);
    particle.offset = sqrtf(offsetVector*offsetVector);

}

double Algorithms::getRandom(double lower, double higher)
{
    /* Sets the initial seed. */
    srand((unsigned)time(0));
    /* We are looking for a three decimal precision.*/
    int range=(higher*100 - lower)+1;

    return (lower+int(range*rand()/(RAND_MAX + 1.0)))/100.0;
}

/* Method to generate all the particles. */
void Algorithms::particlesGenerator()
{
    double width = map->getWidth(), height = map->getHeight();


    for (int i = 0; i < NO_PARTICLES; i++)
    {
        particles[i].position.x = getRandom(0, width);
        particles[i].position.y = getRandom(0, height);
    }
}