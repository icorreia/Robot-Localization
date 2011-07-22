/* 
 * File:   Map.cpp
 * Author: Ivo
 * 
 * Created on 21 de Julho de 2011, 20:15
 */

#include "Structures.h"
#include "RandomNumbers.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>


RandomNumbers::RandomNumbers(int seed)
{
    srand(seed);
    hasExtraNumber = false;
}

double RandomNumbers::normal(double mean,double sd){
    double u1, u2, v1 = 0, v2 = 0, w = 2, y1, y2;

    if(hasExtraNumber){
        hasExtraNumber = false;
        return secondNumber;
    }

    while(w>1)
    {
        u1 = uniform(0,1);
        u2 = uniform(0,1);

        v1 = 2*u1 - 1;
        v2 = 2*u2 - 1;
        w = v1*v1 + v2*v2;
    }

    y1 = v1*sqrt((-2*log(w))/w);
    y2 = v2*sqrt((-2*log(w))/w);

    secondNumber = mean + y2*sd;
    hasExtraNumber = true;

    return mean+y1*sd;
}


double RandomNumbers::uniform(double lower, double higher)
{
    /* We are looking for a three decimal precision and that's why
     * we multiple it by 100 and then, when returning, divide it
     * by 100.0.*/
    int range=(higher*100 - lower) + 1;

    return (lower + int(range*(rand()/(RAND_MAX + 1.0))))/100.0;
}

