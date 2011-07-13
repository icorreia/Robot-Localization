/* 
 * File:   Algorithms.h
 * Author: Ivo Correia
 *
 * Created on 12 de Julho de 2011, 12:55
 */

#include "Structures.h"
#include "Map.h"

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H

class Algorithms {
public:
    Algorithms(int nAP, Map *m);
    Algorithms(const Algorithms& orig);
    virtual ~Algorithms();

    /* The methods that make the algorithm itself. */
    void predict();
    void update();
    void constraint();
    void resample();

    double conditionalProbCalc(double *means, double *sds, double *signalStrengths);
    void estimator(point p, Edge *edge);

    /* SUPPORT METHODS */
    double distance(point p1, point p2);
    Edge *findBestEdge(Particle &particle);
    void updateDistances(Particle &particle);
    double getRandom(double lower, double higher);

    void particlesGenerator();


private:
    Particle particles[NO_PARTICLES];
    int noAccessPoints;
    Map *map;

    /* Used to perform all the mean and standard deviation calculation at a given
     * location.
     */
    double currentMeans[NO_ACCESS_POINTS], previousMeans[NO_ACCESS_POINTS];
    double currentSds[NO_ACCESS_POINTS], previousSds[NO_ACCESS_POINTS];

};

#endif	/* ALGORITHMS_H */

