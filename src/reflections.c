#include "reflections.h"
#include "ray.h"
#include "color.h"
#include "light.h"

static t_vector	reflect(t_vector direction, t_vector surf_normal)
{
	const double	dot_product = vec3_dot(direction, surf_normal);

	return(vec3_sub_vec3(direction, vec3_mult(surf_normal, dot_product * 2)));
}

static t_ray	create_reflection_ray(const t_hit_record *hit_rec)
{
	t_vector	origin;
	t_vector	direction;
	t_ray		reflection_ray;

	origin = hit_record_to_ray_origin(hit_rec);
	direction = reflect(hit_rec->ray_direction, hit_rec->normal);
	reflection_ray = create_ray(origin, direction, hit_rec->color);
	return (reflection_ray);
}

static t_color	blend_reflection(
	t_color object_color,
	t_color reflected_light,
	double	reflection_intensity)
{
	return (clr_add_clr(
				clr_mult(object_color, 1 - reflection_intensity),
				clr_mult(reflected_light, reflection_intensity)));
}

#define REFLECTION_INTENSITY 0.35

t_color	send_reflection_ray(
	const t_object_list		*objects,
	const t_ray				*camera_ray,
	const t_ray_properties	*prop,
	const t_hit_record		*hit_rec)
{
	const t_object_list	*curr_obj = objects;
	t_ray				reflection_ray;
	t_hit_record		reflection_hit_rec;
	t_color				object_light;
	t_color				reflected_light;

	init_hit_record(&reflection_hit_rec);
	while (curr_obj)
	{
		reflection_ray = create_reflection_ray(hit_rec);
		if (ray_hit(objects, &reflection_ray, prop, &reflection_hit_rec))
		{

			object_light = apply_light(curr_obj, camera_ray,
					prop, hit_rec);
			reflected_light = apply_light(curr_obj, &reflection_ray,
					prop, &reflection_hit_rec);
			return (blend_reflection(object_light, reflected_light, REFLECTION_INTENSITY));
		}
		curr_obj = curr_obj->next;
	}
	return (apply_light(objects, camera_ray, prop, hit_rec));
}
