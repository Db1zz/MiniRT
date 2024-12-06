#include "ray.h"
#include "light.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

bool	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *result_rec)
{
	t_hit_record	current_rec;
	bool			found;

	found = false;
	init_hit_record(&current_rec);
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, &prop->ray_interval, &current_rec))
			found = true;
		else if (ray_hit_plane(objects, ray, &current_rec))
			found = true;
		if (found)
			*result_rec = get_closest_hit(&current_rec, result_rec);
		objects = objects->next;
	}
	return (found);
}

t_color	process_ray_hit(const t_object_list *objects,
			const t_ray_properties *prop, const t_hit_record *rec)
{
	t_color	ray_color;
	double	light_intensity;
	
	if (prop->light)
	{
		light_intensity = send_shadow_ray(objects, prop, rec);
		ray_color = clr_mult(rec->color, light_intensity);
	}
	if (prop->amb_lighting)
		ray_color = apply_ambient_light(prop->amb_lighting, &ray_color);
	return (ray_color);
}

t_color	ray_send(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	if (prop->max_diffusion_depth > 0 && ray_hit(objects, ray, prop, rec))
		return (process_ray_hit(objects, prop, rec));
	return (ray_get_background_color(ray));
}

t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop)
{
	t_hit_record		rec;
	t_ray_properties	prop_copy;

	prop_copy = *prop;
	init_hit_record(&rec);
	return (ray_send(objects, ray, &prop_copy, &rec));
}
