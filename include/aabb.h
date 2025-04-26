#ifndef AABB_H
#define AABB_H

#include "vector.h"
#include "interval.h"
#include "color.h"

typedef struct s_scene t_scene;
typedef struct s_ray t_ray;
typedef struct s_sphere t_sphere;
typedef struct s_cylinder t_cylinder;
typedef struct s_object t_object;

typedef struct s_aabb
{
	t_interval interval[3];
	// 	t_color aabb_color;
} t_aabb;

t_aabb create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb create_aabb_from_aabb(const t_aabb *a, const t_aabb *b);
t_aabb *compute_sphere_aabb(t_sphere *sphere);
t_aabb *compute_cylinder_aabb(t_cylinder *cylinder);
bool hit_aabb(const t_aabb *aabb, const t_ray *r);

#endif // AABB_H