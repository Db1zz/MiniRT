#include "aabb.h"
#include "object.h"
#include "scene.h"
#include "vector.h"

t_aabb	*compute_sphere_aabb(t_sphere *sphere)
{
	t_vector	vec;
	t_aabb		*aabb;
	t_vector	a;
	t_vector	b;

	vec = create_vector(sphere->radius, sphere->radius, sphere->radius);
	a = vec3_sub_vec3(sphere->pos, vec);
	b = vec3_add_vec3(sphere->pos, vec);
	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&a, &b);
	return (aabb);
}

t_aabb	*compute_cylinder_aabb(t_cylinder *cylinder)
{
	t_aabb		*aabb;
	t_vector	top_center;
	t_vector	bottom_center;
	t_vector	min_corner;
	t_vector	max_corner;

	t_vector half_axis = vec3_mult(cylinder->axis, cylinder->height);
	top_center = vec3_add_vec3(cylinder->pos, half_axis);
	bottom_center = cylinder->pos;

	min_corner.x = fmin(top_center.x, bottom_center.x) - cylinder->radius;
	min_corner.y = fmin(top_center.y, bottom_center.y) - cylinder->radius;
	min_corner.z = fmin(top_center.z, bottom_center.z) - cylinder->radius;

	max_corner.x = fmax(top_center.x, bottom_center.x) + cylinder->radius;
	max_corner.y = fmax(top_center.y, bottom_center.y) + cylinder->radius;
	max_corner.z = fmax(top_center.z, bottom_center.z) + cylinder->radius;

	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&min_corner, &max_corner);
	return (aabb);
}

t_aabb	*compute_plane_aabb()
{
	t_aabb		*aabb;
	t_vector	min_corner;
	t_vector	max_corner;

	min_corner = create_vector(-SCENE_RENDER_DISTANCE, -SCENE_RENDER_DISTANCE, -SCENE_RENDER_DISTANCE);
	max_corner = create_vector(SCENE_RENDER_DISTANCE, SCENE_RENDER_DISTANCE, SCENE_RENDER_DISTANCE);

	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&min_corner, &max_corner);
	return (aabb);
}

t_aabb	*compute_hyperboloid_aabb()
{
	t_aabb		*aabb;
	t_vector	min_corner;
	t_vector	max_corner;

	min_corner = create_vector(-SCENE_RENDER_DISTANCE, -SCENE_RENDER_DISTANCE, -SCENE_RENDER_DISTANCE);
	max_corner = create_vector(SCENE_RENDER_DISTANCE, SCENE_RENDER_DISTANCE, SCENE_RENDER_DISTANCE);

	aabb = ft_calloc(1, sizeof(t_aabb));
	*aabb = create_aabb_from_vectors(&min_corner, &max_corner);
	return (aabb);
}