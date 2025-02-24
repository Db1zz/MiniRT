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
			const t_light *light,
			const t_ray *camera_ray,
			const t_hit_record *hit_rec,
			double specular_reflection_coefficient);

t_color	apply_light(
			const t_ray *camera_ray,
			const t_scene *scene,
			const t_hit_record *shape_rec);

double	get_diffuse_intensity(
			const t_light *light_source,
			const t_hit_record *shape_rec);

#endif	// LIGHT_H
