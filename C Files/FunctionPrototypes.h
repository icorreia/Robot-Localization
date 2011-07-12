/* The prototypes of all the functions used in the program. */

/* LOCALIZER.CPP */

/* Freeing function. */
void freeAdjacencyMatrixAndVertices();

/* MEANANDSDCALCS.CPP */
void estimator(double lX, double lY, int vertexOne, int vertexTwo, double *means, double *sds);
double distance(double x, double y, double x2, double);
