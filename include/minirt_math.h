#ifndef MINIRT_MATH_H
#define MINIRT_MATH_H

#include <math.h>
#include <stdbool.h>

/* Useful math constants */
# define FT_PI		3.14159265358979323846	/* pi */
# define FT_INFINITY	INFINITY

/* Functions */
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_range(double min, double max);

#endif // MINIRT_MATH_H