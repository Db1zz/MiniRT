#include "bvh.h"
#include "aabb.h"
#include "minirt_math.h"
#include "interval.h"
#include "libft.h"
#include "light.h"

#include <assert.h>

static void merge(
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

void merge_sort_objects_array(
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
	merge_sort_objects_array(objects, start, mittel, comparator);
	merge_sort_objects_array(objects, mittel + 1, end, comparator);
	merge(&objects[start], left_size, right_size, comparator);
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

t_bvh_node *create_tree(t_object **objects, int start, int end, int depth)
{
	t_bvh_node *tree;
	int object_span;

	object_span = end - start;
	tree = init_bvh_node(NULL, NULL, NULL, NULL);
	if (object_span == 0)
	{
		tree->objects = objects[start];
		tree->box = *(objects[start]->box);
	}
	else
	{
		merge_sort_objects_array(objects, start, end, randomize_comparator());
		int mid = start + object_span / 2;
		tree->left = create_tree(objects, start, mid, depth + 1);
		tree->right = create_tree(objects, mid + 1, end, depth + 1);
	}
	if (tree->left && tree->right)
		tree->box = create_aabb_from_aabb(&tree->left->box, &tree->right->box);
	else if (tree->left)
		tree->box = tree->left->box;
	else if (tree->right)
		tree->box = tree->right->box;

	// Removeme
	// tree->box.aabb_color = clr_mult(tree->box.aabb_color, 100 - depth * 0.1);
	return (tree);
}

bool ray_hit_tree_routine(
	const t_ray *ray,
	const t_bvh_node *tree,
	t_hit_record *rec,
	t_hit_record *temp)
{
	bool left;
	bool right;

	left = false;
	right = false;
	if (tree->objects)
	{
		if (ray_hit_shape(ray, tree->objects, rec))
		{
			*rec = *get_closest_hit(temp, rec);
			return (true);
		}
		return (false);
	}
	else if (hit_aabb(&tree->box, ray))
	{
		left = ray_hit_tree_routine(ray, tree->left, rec, temp);
		right = ray_hit_tree_routine(ray, tree->right, rec, temp);
	}
	return (left || right);
}

t_color ray_hit_tree(const t_ray *ray, const t_bvh_node *tree, const t_scene *scene)
{
	t_interval interval;
	t_hit_record rec;
	t_hit_record temp;

	init_hit_record(&rec);
	temp = rec;
	if (!ray_hit_tree_routine(ray, tree, &rec, &temp))
		return (ray_get_background_color(ray));
	return (apply_light(ray, scene, &rec));
}
