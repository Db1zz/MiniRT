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
	int			max_diffusion_depth;
	t_interval	ray_interval;
}	t_ray_properties;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
}	t_ray;

typedef struct s_hit_record
{
	t_vector	p;
	t_vector	normal;
	double		t;
	bool		front_face;
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
			t_ray_properties *prop, t_hit_record *rec);

t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop);

bool	ray_hit_sphere(const t_object_list *sphere_object, const t_ray *ray,
			const t_interval *interval, t_hit_record *rec);

/*
    Sets the hit record normal vector.
    NOTE: the parameter `outward_normal` is assumed to have unit length.
*/
void	ray_hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec);

#endif	// RAY_H
