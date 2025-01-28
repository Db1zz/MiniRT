#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "object.h"

# define REFLECTION_MAX_DEPTH 100

/*
	Typedefs
*/

typedef struct s_scene t_scene;
typedef struct s_light t_light;
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
}	t_ray;

typedef struct s_hit_record
{
	t_vector		intersection_p;
	t_vector		normal;
	double			ray_distance;
	bool			front_face;
	t_color			color;
	t_object_type	obj_type;
	t_vector		ray_direction;
}	t_hit_record;

/*
	Functions
*/
t_ray	create_ray(
	t_vector origin,
	t_vector direction,
	t_color color);

t_ray	create_light_ray(
	const t_hit_record	*shape_rec,
	const t_light		*light);

t_color	ray_get_background_color(const t_ray *ray);

t_color	ray_send(
	const t_ray		*ray,
	const t_scene	*scene);

t_color	ray_routine(
	const t_ray		*ray,
	const t_scene	*scene,
	t_hit_record	*rec);

bool	ray_hit_objects(
	const t_ray			*ray,
	const t_object_list	*objects,
	t_hit_record		*result_rec);

bool	ray_hit_light(
	const t_ray			*light_ray,
	const t_object_list	*objects,
	t_hit_record		*result_rec);

t_color	ray_reflect(
	const t_ray			*camera_ray,
	const t_scene		*scene,
	const t_hit_record	*camera_hit_rec);

bool	ray_hit_sphere(
	const t_object_list *sphere_object,
	const t_ray *ray,
	t_hit_record *rec);

bool	ray_hit_plane(
	const t_object_list *plane_object,
	const t_ray *ray,
	t_hit_record *rec);

bool	ray_hit_cylinder(
	const t_object_list *cylinder_object,
	const t_ray *ray,
	t_hit_record *rec);

t_vector	get_ray_direction(
	t_vector origin,
	t_vector endpoint);

void			init_hit_record(t_hit_record *rec);
t_hit_record	get_closest_hit(const t_hit_record *first,
			const t_hit_record *second);
t_vector		hit_record_to_ray_origin(const t_hit_record *rec);
#endif	// RAY_H
