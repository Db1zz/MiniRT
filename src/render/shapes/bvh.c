#include "bvh.h"
#include "aabb.h"
#include "minirt_math.h"
#include "interval.h"
#include "libft.h"

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

t_bvh_node *create_tree(t_object **objects, int start, int end)
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
		return (ray_hit_objects(ray, ((const t_object **)&tree->objects), rec));
	else if (hit_aabb(&tree->box, ray, interval))
	{
		left = ray_hit_tree_routine(ray, tree->left, interval, rec);
		t_interval interval_right = create_interval(
			interval->min, left ? rec->ray_distance : interval->max);
		right = ray_hit_tree_routine(ray, tree->right, &interval_right, rec);
	}
	return (left || right);
}

#include "light.h"

t_color ray_hit_tree(const t_ray *ray, const t_bvh_node *tree, const t_scene *scene)
{
	t_interval interval;
	t_hit_record rec;

	interval = create_interval(0, FT_INFINITY);
	init_hit_record(&rec);
	if (!ray_hit_tree_routine(ray, tree, &interval, &rec))
		return (ray_get_background_color(ray));
	return (apply_light(ray, scene, &rec));
}
