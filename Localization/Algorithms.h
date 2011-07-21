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

    double conditionalProbCalc(Particle &particle);
    void estimator(Particle &particle);

    /* SUPPORT METHODS */
    Edge *findBestEdge(Particle &particle);
    void updateDistances(Particle &particle);
    double getRandom(double lower, double higher);

    void particlesGenerator();

    void locationBelief();


private:
    Particle particles[NO_PARTICLES];
    int noAccessPoints;
    Map *map;

    /* Used to perform all the mean and standard deviation calculation at a given
     * location.
     */
    double means[NO_ACCESS_POINTS];
    double sds[NO_ACCESS_POINTS];

    /* The current particle that represents the robot's location. */
    Particle *currentParticle;

};

#endif	/* ALGORITHMS_H */

