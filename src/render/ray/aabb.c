#include "aabb.h"

#include "vector.h" /* t_vector */
#include "interval.h" /* create_interval() */

#include <math.h> /* fmin() | fmax() */

t_aabb	create_aabb_from_vectors(const t_vector *a, const t_vector *b)
{
	t_aabb	aabb;

	aabb.interval[0] = create_interval(fmin(a->x, b->x), fmax(a->x, b->x));
	aabb.interval[1] = create_interval(fmin(a->y, b->y), fmax(a->y, b->y));
	aabb.interval[2] = create_interval(fmin(a->z, b->z), fmax(a->z, b->z));
	return (aabb);
}

t_aabb	create_aabb_from_aabb(const t_aabb *a, const t_aabb *b)
{
	t_aabb	aabb;

	for (int axis = 0; axis < 3; ++axis)
	{
		aabb.interval[axis] = interval_expansion(&a->interval[axis], &b->interval[axis]);
	}
	return (aabb);
}

t_aabb aabb_create_empty()
{
	return ((t_aabb){
		.interval[0] = create_interval(0, 0),
		.interval[1] = create_interval(0, 0),
		.interval[2] = create_interval(0, 0)});
}