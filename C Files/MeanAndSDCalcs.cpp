#include "FunctionPrototypes.h"
#include "ExternalVariables.h" 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cmath>

#define PI 3.14159265358979323846
#define NEPER 2.71828182845904523536
#define EPSILON 1


exter

/* Calculates the mean and standard deviation, page 2, equation (1) and (2). */
void estimator(double lX, double lY, int vertexOne, int vertexTwo)
{
	double firstDist, secondDist,distVertices;
	int i;
	
	firstDist = distance(lX, lY, vertices[vertexOne].x, vertices[vertexOne].y);
	secondDist = distance(lX, lY, vertices[vertexTwo].x, vertices[vertexTwo].y);
	distVertices = distance(vertices[vertexOne].x, vertices[vertexOne].y, vertices[vertexTwo].x, vertices[vertexTwo].y);

	/* Allocates the space for the vectors containing the means
	 * and standard deviations at the current position.
	 */
	means = (double *)malloc(sizeof(double)*noAccessPoints);
	sds = (double *)malloc(sizeof(double)*noAccessPoints);
	
	/* For each component (from 1 to the number of access points), 
	 * we calculate the array of means and standard deviations, as
	 * described by the formulas (1) and (2) on the second page of
	 * the paper.
	 */
	for (i = 0; i < noAccessPoints; i++)
        {
		means[i] = (firstDist*(vertices[vertexOne].signalMeans[i]) + secondDist*(vertices[vertexTwo].signalMeans[i]))/(distVertices);
		sds[i] = (firstDist*(vertices[vertexOne].signalSDs[i]) + secondDist*(vertices[vertexTwo].signalSDs[i]))/(distVertices);;
	}

        return;
	
}

double distance(double x, double y, double x2, double y2)
{
    return sqrt(pow(x - x2, 2) + pow(y - y2, 2));
}

//TODO: Signal strengths must be calculated.
double conditionalProbCalc(double *means, double *sds, double *signalStrengths)
{
    /* We use this variable because if all the parcels
     * are zero, than we will return 1 and that is
     * not correct.
     */
    bool isNotNull = false;
    double accumulatedProb = 1, prob = 0;
    int i;

    for (i = 0; i < noAccessPoints; i++)
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
