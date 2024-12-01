#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "interval.h"
# include "object.h"
# include "scene.h"

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
}	t_ray;

t_ray	create_ray(t_vector origin, t_vector direction);
t_color	get_ray_color(const t_ray *r, const t_hit_record *hit_rec);
t_color	ray_hit(const t_object_list *objects,
			const t_ray *ray, const t_interval *interval);

typedef struct s_hit_record
{
	t_vector	p;
	t_vector	normal;
	double		t;
	bool		front_face;
}	t_hit_record;

#endif	// RAY_H