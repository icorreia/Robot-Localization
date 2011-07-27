/* 
 * File:   TestBench.h
 * Author: Ivo
 *
 * Created on 23 de Julho de 2011, 10:10
 */

#ifndef TESTBENCH_H
#define	TESTBENCH_H
#include "Structures.h"

class TestBench {
public:

    void test();
    double calculateParticleProbability();

    point calculateIntersectionPoint(Particle &particle, Edge *edge);
    double calculateOffset();

private:

};

#endif	/* TESTBENCH_H */

