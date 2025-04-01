#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# ifndef EPSILON
#  define EPSILON 1e-4
# endif // EPSILON

# include <math.h>
# include <stdbool.h>

/* Useful math constants */
# define FT_PI		3.14159265358979323846
# define FT_INFINITY	INFINITY

/* Functions */
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_range(double min, double max);
double	clamp_value(double val, double min, double max);
bool	quadratic(double a, double b, double c, double *result);
int		rand_int(int min, int max);

#endif // MINIRT_MATH_H