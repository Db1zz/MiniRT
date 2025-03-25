/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:14 by gonische          #+#    #+#             */
/*   Updated: 2025/03/25 16:53:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "light.h"
#include "scene.h"
#include "minirt_math.h"

t_ray	create_ray(t_vector origin, t_vector direction, t_color color)
{
	return ((t_ray){origin, direction, color});
}

bool	ray_hit_objects(
	const t_ray *ray,
	const t_object_list *objects,
	t_hit_record *result_rec)
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
		if (ray_hit_gyper(objects, ray, &current_rec))
			found = true;
		if (found)
			*result_rec = get_closest_hit(&current_rec, result_rec);
		objects = objects->next;
	}
	return (found);
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

bool	ray_hit_light(
	const t_ray *light_ray,
	const t_object_list *objects,
	t_hit_record *result_rec)
{
	double	light_intersect;

	light_intersect = vec3_length(light_ray->direction);
	if (ray_hit_objects(light_ray, objects, result_rec))
		return (light_intersect <= result_rec->ray_distance - EPSILON);
	return (true);
}

t_color	ray_send(
	const t_ray *ray,
	const t_scene *scene)
{
	t_hit_record	rec;

	init_hit_record(&rec);

	/*
		Perfomance measure:
		2 objects: 737280 1024 x 720
	*/
	// static long counter;
	// printf("Rays sent: %ld\n", ++counter);

	if (!ray_hit_objects(ray, scene->objects, &rec))
		return (ray_get_background_color(ray));
	return (apply_light(ray, scene, &rec));
	// return (ray_reflect(ray, scene, &rec));
}