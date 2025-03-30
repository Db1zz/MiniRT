#ifndef AABB_H
# define AABB_H

#include "vector.h"
#include "object.h"

typedef struct s_interval {
	float	min;
	float	max;
}	t_interval;

typedef struct s_aabb
{
	t_interval	interval[3];
}	t_aabb;

float	interval_clamp(const t_interval *interval, float x);
t_interval	create_interval(float min, float max);

t_aabb	create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb	compute_sphere_aabb(t_sphere *sphere);
#endif  // AABB_H