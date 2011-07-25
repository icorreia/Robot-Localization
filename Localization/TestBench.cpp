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

