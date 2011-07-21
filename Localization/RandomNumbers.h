/* 
 * File:   Map.h
 * Author: Ivo
 *
 * Created on 12 de Julho de 2011, 13:07
 */

#ifndef RANDOM_NUMBERS_H
#define	RANDOM_NUMBERS_H

#include "Structures.h"
#include <iostream>

class RandomNumbers {
public:
    RandomNumbers(int seed);
    double normal (double mean,double sd);
    double uniform(double lower, double higher);

private:
    bool hasExtraNumber;
    double secondNumber;
    int seed;
};

#endif	/* RANDOM_NUMBERS_H */

