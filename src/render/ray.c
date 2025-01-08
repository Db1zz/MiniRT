#include "ray.h"
#include "reflections.h"
#include "light.h"

t_ray	create_ray(t_vector origin, t_vector direction, t_color color)
{
	return ((t_ray){origin, direction, color});
}

bool	ray_hit(
	const t_object_list *objects,
	const t_ray *ray,
	const t_ray_properties *prop,
	t_hit_record *result_rec)
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
		else if (ray_hit_cylinder(objects, ray, &current_rec))
			found = true;
		if (found)
			*result_rec = get_closest_hit(&current_rec, result_rec);
		objects = objects->next;
	}
	return (found);
}

#include <stdio.h>

t_color	ray_send(
	const t_object_list		*objects,
	const t_ray				*ray,
	const t_ray_properties	*prop,
	t_hit_record			*rec)
{
	if (ray_hit(objects, ray, prop, rec))
		return (send_reflection_ray(objects, ray, prop, rec));
	// if (ray_hit(objects, ray, prop, rec))
	// 	return (apply_light(objects, ray, prop, rec));
	return (ray_get_background_color(ray));
}

t_color	ray_color(
	const t_object_list		*objects,
	const t_ray				*ray,
	const t_ray_properties	*prop)
{
	t_hit_record		rec;
	t_ray_properties	prop_copy;

	prop_copy = *prop;
	init_hit_record(&rec);
	return (ray_send(objects, ray, &prop_copy, &rec));
}
