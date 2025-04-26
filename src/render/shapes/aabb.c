#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"
#include "libft.h"

t_aabb create_aabb_from_vectors(const t_vector *a, const t_vector *b)
{
	t_aabb aabb;

	aabb.interval[0] = create_interval(fmin(a->x, b->x), fmax(a->x, b->x));
	aabb.interval[1] = create_interval(fmin(a->y, b->y), fmax(a->y, b->y));
	aabb.interval[2] = create_interval(fmin(a->z, b->z), fmax(a->z, b->z));
	// aabb.aabb_color = create_color(random_double_range(0, 255), random_double_range(0, 255), random_double_range(0, 255));
	return (aabb);
}

t_aabb create_aabb_from_aabb(const t_aabb *a, const t_aabb *b)
{
	t_aabb aabb;

	for (int axis = 0; axis < 3; ++axis)
	{
		aabb.interval[axis] = interval_expansion(&a->interval[axis], &b->interval[axis]);
	}
	// aabb.aabb_color = create_color(random_double_range(0, 255), random_double_range(0, 255), random_double_range(0, 255));
	return (aabb);
}

t_aabb *compute_sphere_aabb(t_sphere *sphere)
{
	t_vector vec;
	t_aabb *aabb;
	t_vector a;
	t_vector b;

	vec = create_vector(sphere->radius, sphere->radius, sphere->radius);
	a = vec3_sub_vec3(sphere->pos, vec);
	b = vec3_add_vec3(sphere->pos, vec);
	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&a, &b);
	return (aabb);
}

t_aabb	*compute_cylinder_aabb(t_cylinder *cylinder)
{
	t_vector vec;
	t_aabb *aabb;
	t_vector a;
	t_vector b;

	vec = create_vector(cylinder->diameter / 2, cylinder->diameter / 2, cylinder->height / 2);
	a = vec3_sub_vec3(vec3_sub_vec3(cylinder->pos, cylinder->axis), vec);
	b = vec3_add_vec3(vec3_add_vec3(cylinder->pos, cylinder->axis), vec);
	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&a, &b);
	return (aabb);
}

bool	hit_aabb(const t_aabb *aabb, const t_ray *r)
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