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
	t_vector	vector;
	double	ratio;
	t_color	color;
}	t_light;

t_color	apply_ambient_light(const t_object_list *amb_object, const t_color *color);

t_color	send_shadow_ray(const t_object_list *objects,
			const t_ray_properties *prop, const t_hit_record *shape_rec);

#endif	// LIGHT_H
