#ifndef INTERVAL_H
# define INTERVAL_H

# include <stdbool.h>

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

t_interval	create_interval(double min, double max);
double		interval_size(t_interval interval);
bool		interval_contains(double val, t_interval interval);
bool		interval_surrounds(double val, t_interval interval);
double		interval_bound(double val, t_interval interval);

#endif	// INTERVAL_H