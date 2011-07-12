/* The structures that are used by the localizer, namely information about
 * the vertices, the edges and so on.
 */

typedef struct
{
	double x, y;
	/* These two arrays will hold the information about the
	 * the signal mean and standard deviation to each access
	 * point in the map.
	 */
	double *signalMeans;
	double *signalSDs;
}Vertix;

typedef struct
{
	double width, length;
}Edge;

/* A given particle used in the Monte Carlo Localization. */
typedef struct
{
    Edge* edge;
    double d; // The project location of the particle on the edge.
    double offset;
    double x, y;
    double angle; // The orientation of the particle with respect to the global reference frame.
    double w; // The normalized weight
    double wC; // The map constrained weight of the particle (calculed on the Constraint step).


}Particle;
 

