#include "minirt_math.h"

double	interval_size(double v1, double v2)
{
	return (v1 - v2);
}

bool	interval_contains(double val, double min, double max)
{
	return (min <= val && max >= val);
}

bool	interval_surrounds(double val, double min, double max)
{
	return (min < val && max > val);
}

double	interval_bound(double val, double min, double max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	return (val);
}
