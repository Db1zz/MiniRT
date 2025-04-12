#ifndef AABB_H
#define AABB_H

#include "vector.h"
#include "interval.h"

typedef struct s_scene t_scene;
typedef struct s_ray t_ray;
typedef struct s_sphere t_sphere;
typedef struct s_object t_object;
typedef bool (*obj_comparator)(const t_object *, const t_object *);

typedef struct s_aabb
{
	t_interval interval[3];
} t_aabb;

typedef struct s_bvh_node
{
	t_aabb box;
	const t_object *objects; // Note: t_bvh_node wouldn't free any of these objects, these objects belong to t_scene structure.
	struct s_bvh_node *left;
	struct s_bvh_node *right;
} t_bvh_node;

void merge_sort_list(
	t_object **objects, int start, int end, obj_comparator comparator);

bool box_compare_is_less(const t_object *a, const t_object *b, int axis);
bool box_x_compare_is_less(const t_object *a, const t_object *b);
bool box_y_compare_is_less(const t_object *a, const t_object *b);
bool box_z_compare_is_less(const t_object *a, const t_object *b);

t_bvh_node *create_tree(t_object **objects, int start, int end);
t_aabb create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb *compute_sphere_aabb(t_sphere *sphere);

t_color ray_hit_tree(const t_ray *ray, const t_bvh_node *tree, const t_scene *scene);

#endif // AABB_H