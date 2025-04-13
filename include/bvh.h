#ifndef BVH_H
#define BVH_H

#include "aabb.h"
#include "object.h"
#include "ray.h"
#include <stdbool.h>

typedef struct s_bvh_node
{
	t_aabb box;
	const t_object *objects; // DO NOT FREE THEM
	struct s_bvh_node *left;
	struct s_bvh_node *right;
} t_bvh_node;

typedef bool (*obj_comparator)(const t_object *, const t_object *);

bool box_compare_is_less(const t_object *a, const t_object *b, int axis);
bool box_x_compare_is_less(const t_object *a, const t_object *b);
bool box_y_compare_is_less(const t_object *a, const t_object *b);
bool box_z_compare_is_less(const t_object *a, const t_object *b);
obj_comparator randomize_comparator();

void merge_sort_objects_array(
	t_object **objects, int start, int end, obj_comparator comparator);

t_bvh_node *create_tree(t_object **objects, int start, int end, int depth);

t_color ray_hit_tree(const t_ray *ray, const t_bvh_node *tree, const t_scene *scene);

void print_tree(t_bvh_node *tree);

#endif // BVH_H