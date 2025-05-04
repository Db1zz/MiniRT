#include "bvh.h"
#include "aabb.h"
#include "minirt_math.h"
#include "interval.h"
#include "libft.h"
#include "light.h"

#include <assert.h>
#include <stdlib.h>

t_bvh_node *init_bvh_node(
	const t_aabb *box,
	t_object *objects,
	t_bvh_node *left,
	t_bvh_node *right)
{
	t_bvh_node	*bvh_node;

	bvh_node = ft_calloc(1, sizeof(t_bvh_node));
	if (!bvh_node)
		return (NULL);
	if (box != NULL)
		bvh_node->box = *box;
	bvh_node->left = left;
	bvh_node->right = right;
	bvh_node->objects = objects;
	return (bvh_node);
}

t_bvh_node *create_tree(t_object **objects, int start, int end, int depth)
{
	t_bvh_node	*tree;
	int			object_span;

	object_span = end - start;
	tree = init_bvh_node(NULL, NULL, NULL, NULL);
	if (object_span == 0)
	{
		tree->objects = objects[start];
		tree->box = objects[start]->box;
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
	return (tree);
}

void	free_bvh_tree(t_bvh_node *tree)
{
	t_bvh_node	*left;
	t_bvh_node	*right;

	if (tree == NULL)
		return ;
	left = tree->left;
	right = tree->right;
	free(tree);
	free_bvh_tree(left);
	free_bvh_tree(right);
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
		if (ray_hit_shape(ray, tree->objects, temp))
		{
			*rec = *get_closest_hit(temp, rec);
			return (true);
		}
		return (false); // Switch to true to see BVHs
	}
	else if (hit_aabb(&tree->box, ray))
	{
		left = ray_hit_tree_routine(ray, tree->left, rec, temp);
		right = ray_hit_tree_routine(ray, tree->right, rec, temp);
	}
	return (left || right);
}

t_color ray_hit_tree(
	const t_ray *ray, const t_bvh_node *tree, const t_scene *scene)
{
	t_hit_record rec;
	t_hit_record temp;

	init_hit_record(&rec);
	temp = rec;
	if (!ray_hit_tree_routine(ray, tree, &rec, &temp))
		return (ray_get_background_color(ray));
	return (apply_light(ray, scene, &rec));
}
