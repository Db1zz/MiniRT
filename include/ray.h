#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "object.h"

#define REFLECTION_MAX_DEPTH 100

/*
	Typedefs
*/
typedef struct s_scene t_scene;
typedef struct s_light t_light;
typedef struct s_bvh_node t_bvh_node ;
typedef struct s_ray
{
	t_vector origin;
	t_vector direction;
	t_color color;
	double length;
} t_ray;

typedef struct s_hit_record
{
	t_vector intersection_p;
	t_vector normal;
	t_color color;
	t_vector ray_direction;
	t_object_type obj_type;
	double ray_distance;
	bool front_face;
} t_hit_record;

typedef bool (*ray_hit_shape_funp)(const t_ray *ray,
								   const t_object *shape,
								   t_hit_record *rec);

/*
	Functions
*/
t_ray create_ray(
	t_vector origin,
	t_vector direction,
	t_color color,
	double length);

t_ray create_light_ray(
	const t_hit_record *shape_rec,
	const t_light *light);

t_color ray_get_background_color(const t_ray *ray);

bool ray_hit_shape(
	const t_ray *ray,
	const t_object *shape,
	t_hit_record *result_rec);

bool ray_hit_multiple_shapes(
	const t_ray *ray,
	const t_object **shapes,
	t_hit_record *result_rec);

bool ray_hit_light(
	const t_ray *light_ray,
	const t_bvh_node *tree,
	t_hit_record *result_rec);

bool ray_hit_tree_routine(
	const t_ray *ray,
	const t_bvh_node *tree,
	t_hit_record *rec,
	t_hit_record *temp);

t_color ray_reflect(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *camera_hit_rec);

bool ray_hit_sphere(
	const t_ray *ray,
	const t_object *sphere_object,
	t_hit_record *rec);

bool ray_hit_plane(
	const t_ray *ray,
	const t_object *plane_object,
	t_hit_record *rec);

bool ray_hit_cylinder(
	const t_ray *ray,
	const t_object *cylinder_object,
	t_hit_record *rec);

bool ray_hit_gyper(
	const t_ray *ray,
	const t_object *gyper,
	t_hit_record *rec);

t_vector get_ray_direction(
	t_vector origin,
	t_vector endpoint);

void init_hit_record(t_hit_record *rec);

t_hit_record *get_closest_hit(
	t_hit_record *first,
	t_hit_record *second);

t_vector hit_record_to_ray_origin(const t_hit_record *rec);
#endif // RAY_H
