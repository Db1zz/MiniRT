#include "ray.h"
#include "minirt_math.h"
#include "vector.h"
#include "light.h"
#include "libft.h"

void	init_hit_record(t_hit_record *rec)
{
	ft_memset(rec, 0, sizeof(t_hit_record));
	rec->ray_distance = FT_INFINITY;
}

t_hit_record	get_closest_hit(
	const t_hit_record	*first,
	const t_hit_record	*second)
{
	if (first->ray_distance > second->ray_distance)
		return (*second);
	return (*first);
}

t_vector	hit_record_to_ray_origin(const t_hit_record *rec)
{
  const double	EPSILON = 1e-4;
  t_vector		origin;

	origin = vec3_add_vec3(rec->intersection_p, vec3_mult(rec->normal, EPSILON)); 
	return (origin);
}

t_vector	get_ray_direction(t_vector origin, t_vector endpoint)
{
	return (vec3_normalize(vec3_sub_vec3(endpoint, origin)));
}

t_color	ray_get_background_color(const t_ray *ray)
{
	double		a;
	t_vector	color_vec;

	a = 0.5 * (ray->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
					vec3_mult(create_vector(1.0, 1.0, 1.0), 1.0 - a),
					vec3_mult(create_vector(0.5, 0.7, 1), a)), 255);
	return (create_color(color_vec.x, color_vec.y, color_vec.z));
}

t_ray	create_light_ray(
	const t_hit_record	*shape_rec,
	const t_light		*light)
{
	t_vector	ray_origin;
	t_vector	ray_direction;
	t_ray		light_ray;

	ray_origin = hit_record_to_ray_origin(shape_rec);
	ray_direction = get_ray_direction(ray_origin, light->pos);
	light_ray = create_ray(ray_origin, ray_direction, create_color(0,0,0));
	return (light_ray);
}
