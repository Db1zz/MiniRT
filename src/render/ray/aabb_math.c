#include "ray.h"

#include "interval.h" /* t_interval */

#include "minirt_math.h" /* FT_INFINITY */

bool ray_hit_aabb(const t_ray *r, const t_aabb *aabb)
{
	t_interval ray_t = create_interval(0, FT_INFINITY);

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
