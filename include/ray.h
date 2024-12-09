#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "interval.h"
# include "object.h"

/*
	Typedefs
*/

typedef struct	s_ray_properties
{
	int				max_diffusion_depth;
	t_interval		ray_interval;
	t_object_list	*light;
	t_object_list	*amb_lighting;
}	t_ray_properties;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
}	t_ray;

typedef struct s_hit_record
{
	t_vector		p;			// Point of itersection
	t_vector		normal;
	double			t;			// ray(𝑡)
	bool			front_face;
	t_color			color;
	t_object_type	obj_type;
}	t_hit_record;

/*
	Functions
*/
t_ray	create_ray(t_vector origin, t_vector direction);

void	ray_hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec);

t_color	ray_get_background_color(const t_ray *ray);

t_color	diffuse_material(const t_object_list *objects,
			t_ray_properties *prop, t_hit_record *rec);

bool	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec);

t_color	ray_send(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec);

t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop);

bool	ray_hit_sphere(const t_object_list *sphere_object, const t_ray *ray,
			const t_interval *interval, t_hit_record *rec);

bool	ray_hit_plane(const t_object_list *plane_object, const t_ray *ray, t_hit_record *rec);

bool	ray_hit_light(const t_object_list *objects, const t_ray *shadow_ray,
			const t_ray_properties *prop, t_hit_record *rec);

/*
    Sets the hit record normal vector.
    NOTE: the parameter `outward_normal` is assumed to have unit length.
*/
void	ray_hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec);

#include "libft.h"

void			init_hit_record(t_hit_record *rec);
t_hit_record	get_closest_hit(const t_hit_record *first,
			const t_hit_record *second);

#endif	// RAY_H
