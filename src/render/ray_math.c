#include "ray.h"

t_color	ray_get_background_color(const t_ray *ray)
{
	double		a;
	t_vector	color_vec;

	a = 0.5 * (ray->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
					vec3_mult((t_vector){1.0, 1.0, 1.0}, 1.0 - a),
					vec3_mult((t_vector){0.5, 0.7, 1}, a)), 255);
	return ((t_color){color_vec.x, color_vec.y, color_vec.z});	
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

t_color	diffuse_material(const t_object_list *objects,
			t_ray_properties *prop, t_hit_record *rec)
{
	t_ray		new_ray;
	t_vector	ray_direction;
	t_color		final_ray_color;

	ray_direction = vec3_random_on_hemisphere(&rec->normal);
	new_ray = create_ray(rec->p, ray_direction);
	prop->max_diffusion_depth--;
	final_ray_color = ray_send(objects, &new_ray, prop, rec);
	return (clr_mult(final_ray_color, 0.5));
}
