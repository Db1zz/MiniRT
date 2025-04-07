#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"

#include <assert.h>

void	merge(
	t_object		**objects_start,
	int				left_size,
	int				right_size,
	obj_comparator	comparator);

float	interval_clamp(const t_interval *interval, float x) {
	if (x > interval->max) {
		return interval->max;
	} else if (x < interval->min) {
		return interval->min;
	}
	return (x);
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

// TODO: fix this shit
// Now, I keep all objects in an array of objects instead linked list.
// This approach increases BVH speed, and it's more simple to write code for this.
void	merge_sort_list(
	t_object		**objects,
	int				start,
	int				end,
	obj_comparator	comparator)
{
	int	mittel;

	if (end - start <= 0) {
		return ;
	}

	mittel = start + (end - start) / 2;
	merge_sort_list(objects, start, mittel, comparator);
	merge_sort_list(objects, mittel, end, comparator);
	merge(&objects[start], mittel - start, end - mittel, comparator);
}


void	merge(
	t_object		**objects_start,
	int				left_size,
	int				right_size,
	obj_comparator	comparator)
{
	const int sorting_size = right_size + left_size;
	const int j = right_size;
	int buffer[left_size + right_size];
	int	i;

	i = 0;
	while (i < left_size && i < right_size) {
		if (comparator(objects_start[i], objects_start[i + left_size])) {
			buffer[i] = objects_start[i];
		} else {
			buffer[i] = objects_start[i];
		}
		++i;
	}
	while (i < left_size) {
		buffer[i] = objects_start[i];
		++i;
	}
	while (i < right_size) {
		buffer[i] = objects_start[i + left_size];
		++i;
	}
	i = 0;
	while (i < sorting_size) {
		objects_start[i] = buffer[i];
		++i;
	}
}

/*
	int axis:
	0 == x
	1 == y
	2 == z
*/
bool	box_compare_is_less(const t_object *a, const t_object *b, int axis) {
	return (a->box.interval[axis].min < b->box.interval[axis].min);
}

bool	box_x_compare_is_less(const t_object *a, const t_object *b) {
	return (box_compare(a, b, 0));
}

bool	box_y_compare_is_less(const t_object *a, const t_object *b) {
	return (box_compare(a, b, 1));
}

bool	box_z_compare_is_less(const t_object *a, const t_object *b) {
	return (box_compare(a, b, 2));
}

obj_comparator	randomize_comparator() {
	static const obj_comparator comparator_array[3] = {
		box_x_compare_is_less,
		box_y_compare_is_less,
		box_z_compare_is_less
	};

	return (comparator_array[rand_int(0, 2)]);
}

/*
	Current Problems:

	1. Мы используем линкед лист, и нам нужно сортироввать какой-то определнный участок.
	2. Каждый раз при рекурсивном вызове create_tree мы двигаем поинтер от 0 до start
*/
t_bvh_node	*create_tree(const t_object *objects, size_t start, size_t end)
{
	t_bvh_node	*tree;
	size_t		object_span;

	object_span = end - start;

	if (object_span == 1) {
		// copy to the left and right
	} else if (object_span == 2) {
		// copy 3
	} else {
		int	mid = start + object_span / 2;
		t_object	*temp;

		// sort objects from start to end by random axis
		temp = merge_sort_list(objects, object_span, randomize_comparator());
		tree->left = create_tree(temp, start, mid);
		tree->right = create_tree(get_node(temp, mid), mid, end);
	}
	// Create a box that will cover all objects by using interval expansion
	// tree->box = aabb(left->bounding_box(), right->bounding_box()); // TODO
	return (tree);
}
