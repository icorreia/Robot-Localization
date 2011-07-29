/* 
 * File:   Algorithms.h
 * Author: Ivo Correia
 *
 * Created on 12 de Julho de 2011, 12:55
 */

#include "Structures.h"
#include "Map.h"
#include "RandomNumbers.h"

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H

#define RESAMPLE_RANGE 2

class Algorithms {
public:
    Algorithms(int nAP, RandomNumbers *rG);
    Algorithms(const Algorithms& orig);
    virtual ~Algorithms();

    /* The methods that make the algorithm itself. */
    void predict(double xMotionIncrease, double yMotionIncrease, double angleIncrease);
    void update();
    void constraint();
    void resample();

    double calculateParticleProbability(Particle *particle);
    void calculateSignalStrengthVectors(Particle &particle);
    Edge *findBestEdge(Particle &particle);
    void updateDistance(Particle &particle);
    double calculateOffset(Particle &particle, Edge *edge);
    point calculateIntersectionPoint(Particle &particle, Edge *edge);
    void particlesGenerator();
    void locationBelief(Particle &particle);

    /* DEBUGGING */
    void printParticles();
    void printParticle(Particle &particle);

private:
    Particle particles[NO_PARTICLES];
    int noAccessPoints;
    Map *map;
    RandomNumbers *randGenerator;

    /* The current particle that represents the robot's location. */
    Particle *currentParticle;

    bool isToPrint;



};

#endif	/* ALGORITHMS_H */

