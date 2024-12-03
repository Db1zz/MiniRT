#include "interval.h"

t_interval	create_interval(double min, double max)
{
	return ((t_interval){min, max});
}

double	interval_size(const t_interval *interval)
{
	return (interval->min - interval->max);
}

bool	interval_contains(double val, const t_interval *interval)
{
	return (interval->min <= val && interval->max >= val);
}

bool	interval_surrounds(double val, const t_interval *interval)
{
	return (interval->min < val && interval->max > val);
}

double	interval_bound(double val, const t_interval *interval)
{
	if (val < interval->min)
		return (interval->min);
	else if (val > interval->max)
		return (interval->max);
	return (val);
}
