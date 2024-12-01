#include "ray.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

void	ray_hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec3_mult(*outward_normal, -1);
}

t_color	get_ray_color(const t_ray *r, const t_hit_record *hit_rec)
{
	t_vector		direction;
	t_ray			ray;
	t_vector		color_vec;
	t_hit_record	rec;
	double			a;

	if (hit_rec != NULL)
	{
		direction = vec3_random_on_hemisphere(&hit_rec->normal);
		ray = create_ray(hit_rec->p, direction);
		return (clr_mult(ray.color, 0.5));
	}
	a = 0.5 * (r->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
					vec3_mult((t_vector){1.0, 1.0, 1.0}, 1.0 - a),
					vec3_mult((t_vector){0.5, 0.7, 1}, a)), 255);
	return ((t_color){});
}

t_color	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_interval *interval, t_hit_record *rec)
{
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, interval, &rec))
			return (get_ray_color(ray, &rec));
		objects = objects->next;
	}
	return (get_ray_color(ray, NULL));
}
