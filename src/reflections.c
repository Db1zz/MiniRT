#include "reflections.h"
#include "ray.h"
#include "color.h"
#include "light.h"

static t_vector	reflect(t_vector direction, t_vector surf_normal)
{
	const double	dot_product = vec3_dot(direction, surf_normal);

	return(vec3_sub_vec3(direction, vec3_mult(surf_normal, dot_product * 2)));
}

static t_ray	calculate_create_reflection_ray(const t_hit_record *hit_rec)
{
	t_vector	origin;
	t_vector	direction;
	t_ray		reflection_ray;

	origin = hit_record_to_ray_origin(hit_rec);
	direction = reflect(hit_rec->ray_direction, hit_rec->normal);
	reflection_ray = create_ray(origin, direction, hit_rec->color);
	return (reflection_ray);
}

t_color	send_reflection_ray(
	const t_object_list		*objects,
	const t_ray				*camera_ray,
	const t_ray_properties	*prop,
	const t_hit_record		*hit_rec)
{
	const double		R = 0.35; // TODO: move to object's material/texture
	const t_object_list	*curr_obj = objects;
	t_ray				reflection_ray;
	t_hit_record		reflection_hit_rec;
	t_color				ol; // object light
	t_color				rl; // reflection light

	init_hit_record(&reflection_hit_rec);
	while (curr_obj)
	{
		reflection_ray = calculate_create_reflection_ray(hit_rec);
		if (ray_hit(objects, &reflection_ray, prop, &reflection_hit_rec))
		{
			ol = apply_light(curr_obj, camera_ray,
					prop, hit_rec);
			rl = apply_light(curr_obj, &reflection_ray,
					prop, &reflection_hit_rec);
			return (clr_add_clr(clr_mult(ol, 1 - R), clr_mult(rl, R)));
		}
		curr_obj = curr_obj->next;
	}
	return (apply_light(objects, camera_ray, prop, hit_rec));
}
