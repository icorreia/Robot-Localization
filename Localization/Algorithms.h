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
    void estimator(double lX, double lY, int vertexOne, int vertexTwo);

    /* SUPPORT METHODS */
    double distance(double x, double y, double x2, double y2);
    Edge *findBestEdge(Particle &particle);
    void calculateNewD(Particle &particle);


private:
    Particle particles[NO_PARTICLES];
    int noAccessPoints;
    Map *map;

};

#endif	/* ALGORITHMS_H */

