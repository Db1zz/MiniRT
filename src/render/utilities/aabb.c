#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"
#include "libft.h"

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

t_bvh_node	*init_bvh_node(
	const t_aabb	*box,
	t_object		*objects,
	t_bvh_node		*left,
	t_bvh_node		*right)
{
	t_bvh_node	*bvh_node;

	bvh_node = ft_calloc(1, sizeof(t_bvh_node));
	if (!bvh_node) {
		return (NULL);
	}

	if (box != NULL) {
		bvh_node->box.interval[0] = box->interval[0];
		bvh_node->box.interval[1] = box->interval[1];
		bvh_node->box.interval[2] = box->interval[2];
	}

	bvh_node->left = left;
	bvh_node->right = right;
	bvh_node->objects = objects;
	return (bvh_node);
}

t_bvh_node	*create_tree(t_object **objects, int start, int end)
{
	t_bvh_node	*tree;
	int			object_span;

	object_span = end - start;

	tree = init_bvh_node(NULL, NULL, NULL, NULL);
	if (object_span == 1) {
		tree->objects = objects[start];
	} else if (object_span == 2) {
		tree->left = create_tree(objects, start, end - 1);
		tree->right = create_tree(objects, start + 1, end);
	} else {
		merge_sort_list(objects, start, end, randomize_comparator());
		int	mid = start + object_span / 2;

		tree->left = create_tree(objects, start, mid);
		tree->right = create_tree(objects, mid, end);
	}
	tree->box = create_aabb_from_aabb(&tree->left->box, &tree->right->box);
	return (tree);
}

/*
	TODO:
	1. add traverse tree function.
	2. test create_tree function and all functions that used by this one
*/