#include "minirt_math.h"
#include "color.h"
#include "libft.h"

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
