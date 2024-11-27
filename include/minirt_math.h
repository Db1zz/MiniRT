#ifndef MINIRT_MATH_H
#define MINIRT_MATH_H

#include <math.h>
#include <stdbool.h>

/* Useful math constants */
# define M_PI		3.14159265358979323846	/* pi */
# define M_INFINITY	INFINITY

/* Functions */
double	degrees_to_radians(double degrees);
double	interval_size(double v1, double v2);
bool	interval_contains(double val, double min, double max);
bool	interval_surrounds(double val, double min, double max);

#endif // MINIRT_MATH_H