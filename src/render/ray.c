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
	t_vector	u_vec;
	t_vector	color_vec;
	double		a;

	if (hit_rec != NULL)
	{
		u_vec = vec3_add_vec3(r->origin, vec3_mult(r->direction, hit_rec->t));
		u_vec = vec3_sub_vec3(u_vec, (t_vector){0, 0, -1});
		u_vec = vec3_normalize(u_vec);
		color_vec = vec3_mult(vec3_mult(vec3_add(u_vec, 1), 0.5), 255);
		return ((t_color){color_vec.x, color_vec.y, color_vec.z});
	}
	u_vec = r->direction;
	a = 0.5 * (u_vec.y + 1.0);
	t_vector res = vec3_mult(vec3_add_vec3(
			vec3_mult((t_vector){1.0, 1.0, 1.0}, 1.0 - a),
			vec3_mult((t_vector){0.5, 0.7, 1}, a)), 255);
	return ((t_color){res.x, res.y, res.z});
}

t_color	ray_hit(const t_object_list *objects,
			const t_ray *ray, const t_interval *interval)
{
	t_hit_record	rec;

	while (objects)
	{
		if (ray_hit_sphere(objects, ray, interval, &rec))
			return (get_ray_color(ray, &rec));
		objects = objects->next;
	}
	return (get_ray_color(ray, NULL));
}
