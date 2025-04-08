#ifndef AABB_H
# define AABB_H

# include "vector.h"
# include "interval.h"

typedef struct s_sphere t_sphere;
typedef struct s_object t_object;
typedef bool (*obj_comparator)(const t_object *, const t_object *);

typedef struct s_aabb
{
	t_interval	interval[3];
}	t_aabb;

typedef struct s_bvh_node
{
	t_aabb		box;
	const t_object	*objects; // Note: t_bvh_node wouldn't free any of these objects, these objects belong to t_scene structure.
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
}	t_bvh_node;

t_bvh_node	*create_tree(t_object **objects, int start, int end);
t_aabb		create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb		*compute_sphere_aabb(t_sphere *sphere);

#endif  // AABB_H