#include "minirt_math.h"
#include "color.h"
#include "libft.h"
#include <stdlib.h>

double	degrees_to_radians(double degrees)
{
	return ((FT_PI / 180) * degrees);
}

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp_value(double val, double min, double max)
{
	if (val > max)
		return (max);
	else if (val < min)
		return (min);
	return (val);
}

bool	quadratic(double a, double b, double c, double *result)
{
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	sqrt_discriminant = sqrt(discriminant);
	result[0] = (-b + sqrt_discriminant) / (2 * a);
	result[1] = (-b - sqrt_discriminant) / (2 * a);
	return (true);
}