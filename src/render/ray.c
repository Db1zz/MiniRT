#include "ray.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

bool	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, &prop->ray_interval, rec))
			return (true);
		objects = objects->next;
	}
	return (false);
}
t_color	ray_send(const t_object_list *objects, const t_ray *ray,
			t_ray_properties *prop, t_hit_record *rec)
{
	if (prop->max_diffusion_depth > 0 && ray_hit(objects, ray, prop, rec))
		return (diffuse_material(objects, prop, rec));
	return (ray_get_background_color(ray));
}

t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop)
{
	t_hit_record		rec;
	t_ray_properties	prop_copy;

	prop_copy = *prop;
	return (ray_send(objects, ray, &prop_copy, &rec));
}
