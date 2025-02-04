#include "ray.h"
#include "light.h"
#include "scene.h"

t_ray	create_ray(t_vector origin, t_vector direction, t_color color)
{
	return ((t_ray){origin, direction, color});
}

bool	ray_hit_objects(
	const t_ray			*ray,
	const t_object_list	*objects,
	t_hit_record		*result_rec)
{
	t_hit_record	current_rec;
	bool			found;

	found = false;
	init_hit_record(&current_rec);
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, &current_rec))
			found = true;
		else if (ray_hit_plane(objects, ray, &current_rec))
			found = true;
		else if (ray_hit_cylinder(objects, ray, &current_rec))
			found = true;
		if (found) {
			printf("%p, %p\n", result_rec, &current_rec);
			*result_rec = get_closest_hit(&current_rec, result_rec);
		}
		objects = objects->next;
	}
	return (found);
}

bool	ray_hit_light(
	const t_ray			*light_ray,
	const t_object_list	*objects,
	t_hit_record		*result_rec)
{
	const double	EPSILON = 1e-4;	
	double			light_intersect;

	light_intersect = vec3_length(light_ray->direction);
	if (ray_hit_objects(light_ray, objects, result_rec))
		return (light_intersect <= result_rec->ray_distance - EPSILON);
	return (true);
}

t_color	ray_routine(
	const t_ray		*ray,
	const t_scene	*scene,
	t_hit_record	*rec)
{
	if (!ray_hit_objects(ray, scene->objects, rec))
		return (ray_get_background_color(ray));
	return (ray_reflect(ray, scene, rec));
	// return (rec->color);
}

#include <stdio.h>

t_color	ray_send(
	const t_ray		*ray,
	const t_scene	*scene)
{
	t_hit_record	rec;
	
	init_hit_record(&rec);
	return (ray_routine(ray, scene, &rec));
}
