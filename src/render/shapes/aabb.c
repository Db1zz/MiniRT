#include "aabb.h"
#include "vector.h"
#include "ray.h"
#include "interval.h"
#include "minirt_math.h"
#include "libft.h"

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

bool	hit_aabb(const t_aabb *aabb, const t_ray *r)
{
	t_interval	ray_t = create_interval(0, FT_INFINITY);

	for (int axis = 0; axis < 3; ++axis)
	{
		const t_interval *ax = &aabb->interval[axis];
		const double adinv = 1.0 / ((double *)(&r->direction))[axis];

		double t0 = (ax->min - ((double *)(&r->origin))[axis]) * adinv;
		double t1 = (ax->max - ((double *)(&r->origin))[axis]) * adinv;

		if (t0 < t1)
		{
			if (t0 > ray_t.min)
				ray_t.min = t0;
			if (t1 < ray_t.max)
				ray_t.max = t1;
		}
		else
		{
			if (t1 > ray_t.min)
				ray_t.min = t1;
			if (t0 < ray_t.max)
				ray_t.max = t0;
		}
		if (ray_t.max <= ray_t.min)
			return false;
	}
	return true;
}

t_aabb aabb_create_empty()
{
	return ((t_aabb){
		.interval[0] = create_interval(0, 0),
		.interval[1] = create_interval(0, 0),
		.interval[2] = create_interval(0, 0)});
}