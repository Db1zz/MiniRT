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

typedef struct s_bvh_node
{
	t_aabb			box;
	t_object_list	*objects;
	t_bvh_node		*left;
	t_bvh_node		*right;
}	t_bvh_node;

float	interval_clamp(const t_interval *interval, float x);
t_interval	create_interval(float min, float max);

t_interval	interval_expansion(const t_interval *i1, const t_interval *i2);

t_aabb	create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb	compute_sphere_aabb(t_sphere *sphere);

#endif  // AABB_H