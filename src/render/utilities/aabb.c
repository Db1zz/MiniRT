#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"

float	interval_clamp(const t_interval *interval, float x) {
	if (x > interval->max) {
		return interval->max;
	} else if (x < interval->min) {
		return interval->min;
	}
	return x;
}

t_interval	create_interval(float min, float max) {
	t_interval interval;

	interval.min = min;
	interval.max = max;
	return (interval);
}

t_interval	interval_expansion(const t_interval *i1, const t_interval *i2) {
	t_interval	expanded_interval;

	if (i1->min <= i2->min) {
		expanded_interval.min = i1->min;
	} else {
		expanded_interval.min = i2->min;
	}
	if (i1->max <= i2->max) {
		expanded_interval.max = i2->max;
	} else {
		expanded_interval.max = i1->max;
	}
	return (expanded_interval);
}

/*
aabb construction:
	aabb() {} // The default AABB is empty, since intervals are empty by default.

    aabb(const interval& x, const interval& y, const interval& z)
      : x(x), y(y), z(z) {}

    aabb(const point3& a, const point3& b) {
        // Treat the two points a and b as extrema for the bounding box, so we don't require a
        // particular minimum/maximum coordinate order.

        x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
        y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
        z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
    }
*/

t_aabb	create_aabb_from_vectors(const t_vector *a, const t_vector *b)
{
	t_aabb	aabb;

	aabb.interval[0] = create_interval(min(a->x, b->x), max(a->x, b->x));
	aabb.interval[1] = create_interval(min(a->y, b->y), max(a->y, b->y));
	aabb.interval[2] = create_interval(min(a->z, b->z), max(a->z, b->z));

	return (aabb);
}

t_aabb	create_aabb_from_aabb(const t_aabb *a, const t_aabb *b) {
	t_aabb	aabb;

	for (int axis = 0; axis < 3; ++axis) {
		aabb.interval[axis] = interval_expansion(&a->interval[axis], &b->interval[axis]);
	}
	return (aabb);
}

t_aabb	compute_sphere_aabb(t_sphere *sphere) {
	t_vector	vec;
	t_aabb		aabb;
	t_vector	a;
	t_vector	b;

	a = vec3_sub_vec3(sphere->pos, vec);
	b = vec3_add_vec3(sphere->pos, vec);
	vec = create_vector(sphere->radius, sphere->radius, sphere->radius);
	aabb = create_aabb_from_vectors(&a, &b);
	return (aabb);
}

bool	hit_aabb(const t_aabb *aabb, const t_ray *r, t_interval ray_t) {
	for (int axis = 0; axis < 3; axis++) {
		const t_interval *ax = &aabb->interval[axis];
		const double adinv = 1.0 / ((float *)(&r->direction))[axis];

		float t0 = (ax->min - ((float *)(&r->origin))[axis]) * adinv;
		float t1 = (ax->max - ((float *)(&r->origin))[axis]) * adinv;

		if (t0 < t1) {
			if (t0 > ray_t.min) ray_t.min = t0;
			if (t1 < ray_t.max) ray_t.max = t1;
		} else {
			if (t1 > ray_t.min) ray_t.min = t1;
			if (t0 < ray_t.max) ray_t.max = t0;
		}
		if (ray_t.max <= ray_t.min)
			return false;
	}
	return true;
}

void	sort_list(t_object_list *list) {

}

/*
	TODO:
		1. add functions to handle node insertion
		2. implement sorting function for objects that sorts by axis
*/
t_bvh_node	*create_tree(const t_object_list *objects, size_t start, size_t end) {
	t_bvh_node	*tree;
	int			axis;
	size_t		object_span;

	axis = rand_int(0, 2);
	object_span = end - start;

	if (object_span == 1) {
		// copy to the left and right
	} else if (object_span == 2) {
	} else {
		int mid = start + object_span / 2;
		
	}
	tree->box = aabb(left->bounding_box(), right->bounding_box());
	return (tree);
}
