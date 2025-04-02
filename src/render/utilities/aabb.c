#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"

#include <assert.h>

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



t_object_list	*merge_sort_list(
	t_object_list	*list,
	size_t 			size,
	bool			(*comparator)(const t_object_list *, const t_object_list *))
{
	t_object_list	*right;

	if (list == NULL || list->next == NULL)
		return ;

	right = list;
	size_t i = 0;
	const size_t mittel = size / 2;
	while (i < mittel) {
		assert(right && right->next);
		right = right->next;
		++i;
	}
	list = merge_sort_list(list, mittel, comparator);
	right = merge_sort_list(right, size - mittel, comparator);

	t_object_list	*next = NULL;
	t_object_list	*tail = NULL;
	t_object_list	*result = NULL;

	while (list || right)
	{
		if (!right) {
			next = list;
			list = list->next;
		} else if (!list) {
			next = right;
			right = right->next;
		} else if (comparator(list, right) != 0) {
			next = list;
			list = list->next;
		} else {
			next = right;
			right = right->next;
		}
		if (!result) {
			result = next;
		} else {
			tail->next = next;
		}
		tail = next;
	}
	return (result);
}

/*
	int axis:
	0 == x
	1 == y
	2 == z
*/
bool	box_compare(const t_object_list *a, const t_object_list *b, int axis) {
	return (a->box.interval[axis].min < b->box.interval[axis].min);
}

bool	box_x_compare(const t_object_list *a, const t_object_list *b) {
	return (box_compare(a, b, 0));
}

bool	box_y_compare(const t_object_list *a, const t_object_list *b) {
	return (box_compare(a, b, 1));
}

bool	box_z_compare(const t_object_list *a, const t_object_list *b) {
	return (box_compare(a, b, 2));
}

obj_comparator	randomize_comparator() {
	static const obj_comparator comparator_array[3] = {
		box_x_compare,
		box_y_compare,
		box_z_compare
	};

	return (comparator_array[rand_int(0, 2)]);
}

t_bvh_node	*create_tree(const t_object_list *objects, size_t start, size_t end)
{
	t_bvh_node	*tree;
	int			axis;
	size_t		object_span;

	axis = rand_int(0, 2);
	object_span = end - start;

	if (object_span == 1) {
		// copy to the left and right
	} else if (object_span == 2) {
		// copy 3
	} else {
		int mid = start + object_span / 2;
		merge_sort_list(objects, object_span, randomize_comparator());
		// sort objects from start to end by random axis
		// NOTE: This FUNCTION SHOULD BE CALLED RECURSIVELY
		// left = create_tree(objects, start, mid);
		// right = create_tree(objects, mid, end);
	}
	// Create a box that will cover all objects by using interval expansion
	// tree->box = aabb(left->bounding_box(), right->bounding_box()); // TODO
	return (tree);
}
