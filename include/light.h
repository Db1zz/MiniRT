#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "color.h"
# include "ray.h"

# define RATIO_MIN 0
# define RATIO_MAX 1

typedef struct s_amb_lighting
{
	double	ratio;
	t_color	color;
}	t_amb_lighting;

typedef struct s_light
{
	t_vector	pos;
	double		ratio;
	t_color		color;
}	t_light;

double	calculate_specular_light(
	const t_light		*light,
	const t_ray			*camera_ray,
	const t_hit_record	*hit_rec,
	double				specular_reflection_coefficient);

t_color	get_diffuse_light(
	const t_object_list		*objects,
	const t_ray_properties	*prop,
	const t_hit_record		*shape_rec);

t_color	get_specular_light(
	const t_ray_properties	*prop,
	const t_hit_record		*hit_rec,
	const t_ray				*camera_ray);

t_color	get_ambient_light(
	const t_object_list	*amb_object,
	const t_color		*color);

t_color	apply_light(
	const t_object_list		*objects,
	const t_ray				*camera_ray,
	const t_ray_properties	*prop,
	const t_hit_record		*rec);

t_ray	calculate_create_shadow_ray(
			const t_hit_record *shape_rec, const t_light *light);

bool	ray_hit_light(const t_object_list *objects, const t_ray *shadow_ray,
			const t_ray_properties *prop, t_hit_record *rec);

double	get_diffuse_intensity(const t_light *light_source,
			const t_hit_record *shape_rec);

#endif	// LIGHT_H
