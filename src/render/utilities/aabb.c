#include "aabb.h"
#include "ray.h"
#include "minirt_math.h"
#include "libft.h"

#include <assert.h>

void merge(
	t_object **objects_start,
	int left_size,
	int right_size,
	obj_comparator comparator);

t_aabb create_aabb_from_vectors(const t_vector *a, const t_vector *b)
{
	t_aabb aabb;

	aabb.interval[0] = create_interval(fmin(a->x, b->x), fmax(a->x, b->x));
	aabb.interval[1] = create_interval(fmin(a->y, b->y), fmax(a->y, b->y));
	aabb.interval[2] = create_interval(fmin(a->z, b->z), fmax(a->z, b->z));

	return (aabb);
}

t_aabb create_aabb_from_aabb(const t_aabb *a, const t_aabb *b)
{
	t_aabb aabb;

	for (int axis = 0; axis < 3; ++axis)
	{
		aabb.interval[axis] = interval_expansion(&a->interval[axis], &b->interval[axis]);
	}
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

bool hit_aabb(const t_aabb *aabb, const t_ray *r, t_interval *ray_t)
{
	for (int axis = 0; axis < 3; axis++)
	{
		const t_interval *ax = &aabb->interval[axis];
		const double adinv = 1.0 / ((float *)(&r->direction))[axis];

		float t0 = (ax->min - ((float *)(&r->origin))[axis]) * adinv;
		float t1 = (ax->max - ((float *)(&r->origin))[axis]) * adinv;

		if (t0 < t1)
		{
			if (t0 > ray_t->min)
				ray_t->min = t0;
			if (t1 < ray_t->max)
				ray_t->max = t1;
		}
		else
		{
			if (t1 > ray_t->min)
				ray_t->min = t1;
			if (t0 < ray_t->max)
				ray_t->max = t0;
		}
		if (ray_t->max <= ray_t->min)
			return false;
	}
	return true;
}

void merge_sort_list(
	t_object **objects,
	int start,
	int end,
	obj_comparator comparator)
{
	int mittel;
	int left_size;
	int right_size;

	if (start >= end || end - start == 0)
	{
		return;
	}

	mittel = start + (end - start) / 2;
	left_size = mittel + 1 - start;
	right_size = end - mittel;
	merge_sort_list(objects, start, mittel, comparator);
	merge_sort_list(objects, mittel + 1, end, comparator);
	merge(&objects[start], left_size, right_size, comparator);
}

void merge(
	t_object **objects_start,
	int left_size,
	int right_size,
	obj_comparator comparator)
{
	const int sorting_size = right_size + left_size;
	t_object *buffer[left_size + right_size];
	int i;
	int j;
	int k;

	if (left_size + right_size == 0)
		return;
	i = 0;
	j = 0;
	k = left_size;
	while (j < left_size && k < right_size + left_size)
	{
		if (comparator(objects_start[j], objects_start[k]))
		{
			buffer[i] = objects_start[j++];
		}
		else
		{
			buffer[i] = objects_start[k++];
		}
		++i;
	}

	while (j < left_size)
	{
		buffer[i] = objects_start[j++];
		++i;
	}

	while (k < left_size + right_size)
	{
		buffer[i] = objects_start[k++];
		++i;
	}

	i = 0;
	while (i < sorting_size)
	{
		objects_start[i] = buffer[i];
		++i;
	}
}

bool box_compare_is_less(const t_object *a, const t_object *b, int axis)
{
	return (a->box->interval[axis].min < b->box->interval[axis].min);
}

bool box_x_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 0));
}

bool box_y_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 1));
}

bool box_z_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 2));
}

obj_comparator randomize_comparator()
{
	static const obj_comparator comparator_array[3] = {
		box_x_compare_is_less,
		box_y_compare_is_less,
		box_z_compare_is_less};

	return (comparator_array[rand_int(0, 2)]);
}

t_bvh_node *init_bvh_node(
	const t_aabb *box,
	t_object *objects,
	t_bvh_node *left,
	t_bvh_node *right)
{
	t_bvh_node *bvh_node;

	bvh_node = ft_calloc(1, sizeof(t_bvh_node));
	if (!bvh_node)
	{
		return (NULL);
	}

	if (box != NULL)
	{
		bvh_node->box = *box;
	}

	bvh_node->left = left;
	bvh_node->right = right;
	bvh_node->objects = objects;
	return (bvh_node);
}

t_bvh_node *create_tree(t_object **objects, int start, int end)
{
	t_bvh_node *tree;
	int object_span;
	static int rec_level;

	object_span = end - start;
	tree = init_bvh_node(NULL, NULL, NULL, NULL);
	if (object_span == 0)
	{
		tree->objects = objects[start];
		tree->box = *(objects[start]->box);
	}
	else
	{
		merge_sort_list(objects, start, end, randomize_comparator());
		int mid = start + object_span / 2;

		tree->left = create_tree(objects, start, mid);
		tree->right = create_tree(objects, mid + 1, end);
	}
	if (tree->left && tree->right)
		tree->box = create_aabb_from_aabb(&tree->left->box, &tree->right->box);
	else if (tree->left)
		tree->box = tree->left->box;
	else if (tree->right)
		tree->box = tree->right->box;
	return (tree);
}

bool ray_hit_tree_routine(
	const t_ray *ray, const t_bvh_node *tree, t_interval *interval, t_hit_record *rec)
{
	bool left;
	bool right;

	left = false;
	right = false;
	if (tree->objects && !tree->left && !tree->right)
		return (ray_hit_objects(ray, &tree->objects, rec));
	else if (hit_aabb(&tree->box, ray, interval))
	{
		left = ray_hit_tree(ray, tree->left, rec);
		right = ray_hit_tree(ray, tree->right, rec);
	}
	return (left || right);
}

bool ray_hit_tree(const t_ray *ray, const t_bvh_node *tree, t_hit_record *rec)
{
	t_interval interval;

	interval = create_interval(0, FT_INFINITY);
	return (ray_hit_tree_routine(ray, tree, &interval, rec));
}